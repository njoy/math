#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "math/interpolate.hpp"
#include "math/implementation/ParametricProbabilityDistribution.hpp"
#include "math/implementation/SplicedProbabilityDistribution.hpp"

namespace {
auto pdf0 = [](double x){return 0.5*x + 0.5;};
auto cdf0 = [](double x){return 0.25*std::pow(x,2) + 0.5 * x + 0.25;};
std::function<double(double)> PDF0_ = pdf0;
std::function<double(double)> CDF0_ = cdf0;

math::implementation::ParametricProbabilityDistribution
< std::function<double(double)>, std::function<double(double)> >
probabilityDistribution0
( std::move(PDF0_), std::move(CDF0_) );

auto pdf1 = [](double x){return exp(x) / ( exp(1.0) - exp(-1.0) );};

auto cdf1 = [](double x){
  return ( exp(x) - exp(-1.0) ) / ( exp(1.0) - exp(-1.0) );
};

std::function<double(double)> PDF1_ = pdf1;
std::function<double(double)> CDF1_ = cdf1;

math::implementation::ParametricProbabilityDistribution
< std::function<double(double)>, std::function<double(double)> >
probabilityDistribution1
( std::move(PDF1_), std::move(CDF1_) );

std::array<double, 2> associatedConditions = {{0.0, 1.0}};

auto pdfRef  = [](double x){
  return 0.5 * ( pdf0(x) +  pdf1(x) );
};

auto cdfRef  = [](double x){
  return 0.5 * ( cdf0(x) +  cdf1(x) );
};

}

math::implementation::SplicedProbabilityDistribution
< math::interpolate::linLin, math::interpolate::linLin >
splicedDistribution( 0.5,
                     &probabilityDistribution0,
                     &probabilityDistribution1,
                     associatedConditions);

std::function<double(double)> PDFRef = pdfRef;
std::function<double(double)> CDFRef = cdfRef;

int testNumber = 0;

int main( int argc, const char* argv[]){
  LOG(INFO) << "SplicedProbabilityDistribution Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "SplicedProbabilityDistribution Tests Complete!";
  return result;
}

typedef math::implementation::SplicedProbabilityDistribution
                        < math::interpolate::linLin, math::interpolate::linLin >
spliced;

SCENARIO("Illegal condition combinations will cause the ctor to throw",
         "[math], [SplicedProbabilityDistribution], [ctor]"){
  GIVEN("Two (valid) probability distributions and an out-of-order"
        " specified conditions"){
    
    std::array<double, 2> conditions = {{0.50, 0.25}};
    
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( spliced ( 0.375,
                                  &probabilityDistribution0,
                                  &probabilityDistribution1,
                                  conditions, false ) );
      }   
    }
  }
  GIVEN("a queried condition outside the range of the specified conditions"){

    double condition = 0.75;
    std::array<double, 2> conditions = {{0.25, 0.50}};

    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( spliced ( condition,
                                  &probabilityDistribution0,
                                  &probabilityDistribution1,
                                  conditions, false ) );

      }   
    }
  }
}
