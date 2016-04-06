#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "math/implementation/probabilityDistribution.hpp"
#include "math/implementation/SplicedProbabilityDistribution.hpp"

namespace {
auto pdf0 = [](double x){return 0.5*x + 0.5;};
auto cdf0 = [](double x){return 0.25*std::pow(x,2) + 0.5 * x + 0.25;};
std::function<double(double)> PDF0_ = pdf0;
std::function<double(double)> CDF0_ = cdf0;

math::implementation::ProbabilityDistribution
< std::function<double(double)>, std::function<double(double)> >
probabilityDistribution0
( std::move(PDF0_), std::move(CDF0_) );

auto pdf1 = [](double x){return exp(x) / ( exp(1.0) - exp(-1.0) );};

auto cdf1 = [](double x){
  return ( exp(x) - exp(-1.0) ) / ( exp(1.0) - exp(-1.0) );
};

std::function<double(double)> PDF1_ = pdf1;
std::function<double(double)> CDF1_ = cdf1;

math::implementation::ProbabilityDistribution
< std::function<double(double)>, std::function<double(double)> >
probabilityDistribution1
( std::move(PDF1_), std::move(CDF1_) );

std::array<double, 2> pdfweights = {{0.25, 0.75}};
std::array<double, 2> cdfweights = {{0.50, 0.50}};

auto pdfRef  = [](double x){
  return pdfweights.front() * pdf0(x) + pdfweights.back() * pdf1(x);
};

auto cdfRef  = [](double x){
  return cdfweights.front() * cdf0(x) + cdfweights.back() * cdf1(x);
};

}

math::implementation::SplicedProbabilityDistribution
splicedDistribution( probabilityDistribution0, probabilityDistribution1,
                     pdfweights, cdfweights);

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

SCENARIO("Illegal weight combinations will cause the ctor to throw",
         "[math], [SplicedProbabilityDistribution], [ctor]"){
  GIVEN("Two (valid) probability distributions and (valid) cdfweights"){

    std::array<double, 2> cdfweights = {{0.50, 0.50}};
    
    WHEN("when the pdf weights are greater than 1"){

      std::array<double, 2> pdfweights = {{0.50, 0.51}};
      
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( math::implementation::SplicedProbabilityDistribution
                        ( probabilityDistribution0,
                          probabilityDistribution1,
                          pdfweights, cdfweights ) );
      }   
    }
    WHEN("when the pdf weights are less than 1"){

      std::array<double, 2> pdfweights = {{0.50, 0.49}};
      
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( math::implementation::SplicedProbabilityDistribution
                        ( probabilityDistribution0,
                          probabilityDistribution1,
                          pdfweights, cdfweights ) );
      }     
    }
  }
  GIVEN("Two (valid) probability distributions and (valid) pdfweights"){

    std::array<double, 2> pdfweights = {{0.50, 0.50}};
    
    WHEN("when the cdf weights are greater than 1"){

      std::array<double, 2> cdfweights = {{0.50, 0.51}};
      
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( math::implementation::SplicedProbabilityDistribution
                        ( probabilityDistribution0,
                          probabilityDistribution1,
                          pdfweights, cdfweights ) );
      }   
    }
    WHEN("when the cdf weights are less than 1"){

      std::array<double, 2> cdfweights = {{0.50, 0.49}};
      
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( math::implementation::SplicedProbabilityDistribution
                        ( probabilityDistribution0,
                          probabilityDistribution1,
                          pdfweights, cdfweights ) );
      }
    }
  }
}
