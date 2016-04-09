#define CATCH_CONFIG_RUNNER

#include <cmath>
#include <functional>

#include "catch.hpp"

#include "math/interpolate.hpp"
#include "math/implementation/ProbabilityDistribution.hpp"
#include "math/implementation/BivariateProbabilityDistribution.hpp"

namespace ma = math::API;
namespace mi = math::implementation;

namespace{  
  /* considering a domain spanning from -1 to 1 */  
  auto pdf0_ = [](double x){return 0.5 * x + 0.5;};
  auto pdf1_ = [](double x){return -0.5 * x + 0.5;};
  auto pdf2_ = [](double){return 0.5;};
  
  auto cdf0_ = [](double x){return 0.25*std::pow(x,2) + 0.5 * x + 0.25;};
  auto cdf1_ = [](double x){return -0.25*std::pow(x,2) + 0.5 * x + 0.75;};
  auto cdf2_ = [](double x){return 0.5 * x + 0.5;};

  template< typename T > T clone(const T& t){return t;}
}

int testNumber = 0;

std::vector<double> conditions = {0.0, 1.0, 2.0};

std::function<double(double)> pdf0 = pdf0_;
std::function<double(double)> pdf1 = pdf1_;
std::function<double(double)> pdf2 = pdf2_;
std::function<double(double)> cdf0 = cdf0_;  
std::function<double(double)> cdf1 = cdf1_;  
std::function<double(double)> cdf2 = cdf2_;  

std::unique_ptr
< math::implementation::BivariateProbabilityDistribution
< math::interpolate::linLin, math::interpolate::linLin > >
bvpd;

int main( int argc, const char* argv[] ){
  std::function<double(double)> pdf0 = pdf0_;
  std::function<double(double)> cdf0 = cdf0_;  
  std::unique_ptr<ma::ProbabilityDistribution> probDist0 =
    std::make_unique
    < mi::ProbabilityDistribution
      < std::function<double(double)>, std::function<double(double) > > >
    ( std::move(pdf0), std::move(cdf0) );

  std::function<double(double)> pdf1 = pdf1_;
  std::function<double(double)> cdf1 = cdf1_;  
  std::unique_ptr<ma::ProbabilityDistribution> probDist1 =
    std::make_unique
    < mi::ProbabilityDistribution
      < std::function<double(double)>, std::function<double(double) > > >
    ( std::move(pdf1), std::move(cdf1) );

  std::function<double(double)> pdf2 = pdf2_;
  std::function<double(double)> cdf2 = cdf2_;  
  std::unique_ptr<ma::ProbabilityDistribution> probDist2 =
    std::make_unique
    < mi::ProbabilityDistribution
      < std::function<double(double)>, std::function<double(double) > > >
    ( std::move(pdf2), std::move(cdf2) );

  std::vector< std::unique_ptr< ma::ProbabilityDistribution > >
    conditionedProbDist;
  
  conditionedProbDist.push_back(std::move(probDist0));
  conditionedProbDist.push_back(std::move(probDist1));
  conditionedProbDist.push_back(std::move(probDist2));

  bvpd = std::make_unique
    < math::implementation::BivariateProbabilityDistribution
      < math::interpolate::linLin, math::interpolate::linLin > >
    ( clone(conditions), std::move(conditionedProbDist) );
  
  LOG(INFO) << "";
  LOG(INFO) << "BivariateProbabilityDistribution Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "BivariateProbabilityDistribution Tests Complete!";
  return result;
}

typedef
math::implementation::BivariateProbabilityDistribution
< math::interpolate::linLin,
  math::interpolate::linLin >
bvpdll;

SCENARIO("Invalid specified variate sequences will cause the constructor to"
         " throw"){
  GIVEN("a specified variate vector longer than the vector of conditioned"
        " probability distributions"){
    std::vector<double> specifiedVariates = {5.0E-7, 1.0E-3, 1.0, 10.0};
    std::vector< std::unique_ptr< ma::ProbabilityDistribution > > pds;

    std::function<double(double)> pdf0 = [](double x){return 0.5 * x + 0.5;};
    std::function<double(double)> pdf1 = [](double x){return -0.5 * x + 0.5;};
    std::function<double(double)> pdf2 = [](double){return 0.5;};
  
    std::function<double(double)> cdf0 =
      [](double x){return 0.25*std::pow(x,2) + 0.5 * x + 0.25;};
    std::function<double(double)> cdf1 =
      [](double x){return -0.25*std::pow(x,2) + 0.5 * x + 0.75;};
    std::function<double(double)> cdf2 =
      [](double x){return 0.5 * x + 0.5;};
    
    std::unique_ptr<ma::ProbabilityDistribution> probDist0 =
      std::make_unique
      < mi::ProbabilityDistribution
        < std::function<double(double)>, std::function<double(double) > > >
      ( std::move(pdf0), std::move(cdf0) );
    
    std::unique_ptr<ma::ProbabilityDistribution> probDist1 =
      std::make_unique
      < mi::ProbabilityDistribution
        < std::function<double(double)>, std::function<double(double) > > >
      ( std::move(pdf1), std::move(cdf1) );
    
    std::unique_ptr<ma::ProbabilityDistribution> probDist2 =
      std::make_unique
      < mi::ProbabilityDistribution
        < std::function<double(double)>, std::function<double(double) > > >
      ( std::move(pdf2), std::move(cdf2) );
    
    pds.reserve(3);
    pds.push_back(std::move(probDist0));
    pds.push_back(std::move(probDist1));
    pds.push_back(std::move(probDist2));
    WHEN("passed to the constructor"){
      THEN("the constructor will throw"){
        LOG(INFO) << "Test " <<
          ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( bvpdll(std::move( specifiedVariates ),
                               std::move( pds ),
                               false));
      }
    }
  }
  GIVEN("a specified variate vector longer than the vector of conditioned"
        " probability distributions"){
    std::vector<double> specifiedVariates = {5.0E-7, 1.0E-3};
    std::vector< std::unique_ptr< ma::ProbabilityDistribution > > pds;

    std::function<double(double)> pdf0 = [](double x){return 0.5 * x + 0.5;};
    std::function<double(double)> pdf1 = [](double x){return -0.5 * x + 0.5;};
    std::function<double(double)> pdf2 = [](double){return 0.5;};
  
    std::function<double(double)> cdf0 =
      [](double x){return 0.25*std::pow(x,2) + 0.5 * x + 0.25;};
    std::function<double(double)> cdf1 =
      [](double x){return -0.25*std::pow(x,2) + 0.5 * x + 0.75;};
    std::function<double(double)> cdf2 =
      [](double x){return 0.5 * x + 0.5;};
    
    std::unique_ptr<ma::ProbabilityDistribution> probDist0 =
      std::make_unique
      < mi::ProbabilityDistribution
        < std::function<double(double)>, std::function<double(double) > > >
      ( std::move(pdf0), std::move(cdf0) );
    
    std::unique_ptr<ma::ProbabilityDistribution> probDist1 =
      std::make_unique
      < mi::ProbabilityDistribution
        < std::function<double(double)>, std::function<double(double) > > >
      ( std::move(pdf1), std::move(cdf1) );
    
    std::unique_ptr<ma::ProbabilityDistribution> probDist2 =
      std::make_unique
      < mi::ProbabilityDistribution
        < std::function<double(double)>, std::function<double(double) > > >
      ( std::move(pdf2), std::move(cdf2) );
    
    pds.reserve(3);
    pds.push_back(std::move(probDist0));
    pds.push_back(std::move(probDist1));
    pds.push_back(std::move(probDist2));
    WHEN("passed to the constructor"){
      THEN("the constructor will throw"){
        LOG(INFO) << "Test " <<
          ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( bvpdll(std::move( specifiedVariates ),
                               std::move( pds ),
                               false));
      }
    }
  }
  GIVEN("an out-of-order specified variate vector "){
    std::vector<double> specifiedVariates = {5.0E-7, 1.0E-3, 9.99E-4};
    std::vector< std::unique_ptr< ma::ProbabilityDistribution > > pds;
    
    std::function<double(double)> pdf0 = [](double x){return 0.5 * x + 0.5;};
    std::function<double(double)> pdf1 = [](double x){return -0.5 * x + 0.5;};
    std::function<double(double)> pdf2 = [](double){return 0.5;};
  
    std::function<double(double)> cdf0 =
      [](double x){return 0.25*std::pow(x,2) + 0.5 * x + 0.25;};
    std::function<double(double)> cdf1 =
      [](double x){return -0.25*std::pow(x,2) + 0.5 * x + 0.75;};
    std::function<double(double)> cdf2 =
      [](double x){return 0.5 * x + 0.5;};
    
    std::unique_ptr<ma::ProbabilityDistribution> probDist0 =
      std::make_unique
      < mi::ProbabilityDistribution
        < std::function<double(double)>, std::function<double(double) > > >
      ( std::move(pdf0), std::move(cdf0) );
    
    std::unique_ptr<ma::ProbabilityDistribution> probDist1 =
      std::make_unique
      < mi::ProbabilityDistribution
        < std::function<double(double)>, std::function<double(double) > > >
      ( std::move(pdf1), std::move(cdf1) );
    
    std::unique_ptr<ma::ProbabilityDistribution> probDist2 =
      std::make_unique
      < mi::ProbabilityDistribution
        < std::function<double(double)>, std::function<double(double) > > >
      ( std::move(pdf2), std::move(cdf2) );
    
    pds.reserve(3);
    pds.push_back(std::move(probDist0));
    pds.push_back(std::move(probDist1));
    pds.push_back(std::move(probDist2));
    WHEN("passed to the constructor"){
      THEN("the constructor will throw"){
        LOG(INFO) << "Test " <<
          ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( bvpdll(std::move( specifiedVariates ),
                               std::move( pds ),
                               false));
      }
    }
  }
}
