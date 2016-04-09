#include "catch.hpp"

#include "math/implementation/BivariateProbabilityDistribution.hpp"

extern int testNumber;

extern std::vector<double> conditions;

extern std::function<double(double)> cdf0;
extern std::function<double(double)> cdf1;
extern std::function<double(double)> cdf2;

extern std::unique_ptr
  < math::implementation::BivariateProbabilityDistribution
  < math::interpolate::linLin, math::interpolate::linLin > > bvpd;

SCENARIO(
  "The conditional cumulative probability will return a value that matches the"
  "composed CDF", 
  "[math], [BivariateProbabilityDistribution],"
  " [conditionalCumulativeProbability]"){
  GIVEN( "valid conditions" ){
    WHEN( "the condition falls on a boundary" ){
      THEN( "the return value will match the reference" ){
        LOG(INFO) << "Test " << ++testNumber << 
          ": [conditionalCumulativeProbability] No Errors Expected";
        std::vector<double> events = {-1.0, -0.5, 0.0, 0.5, 1.0};
        double condition = conditions[0];
        for( auto event : events ){
          REQUIRE( cdf0(event) == Approx( bvpd->conditionalCumulativeProbability
                                          ( event, condition ) ) );
        }
        condition = conditions[1];
        for( auto event : events ){
          REQUIRE( cdf1(event) == Approx( bvpd->conditionalCumulativeProbability
                                      ( event, condition ) ) );
        }
        condition = conditions[2];
        for( auto event : events ){
          REQUIRE( cdf2(event) == Approx( bvpd->conditionalCumulativeProbability
                                      ( event, condition ) ) );
        }
      }
    }
    
    WHEN( "the conditions are not on a boundary" ){
      std::vector<double> events = {-1.0, -0.5, 0.0, 0.5, 1.0};
      double condition = 0.5 * ( conditions[0] + conditions[1] );
      for( auto event : events ){
        auto reference = 0.5 * ( cdf0(event) + cdf1(event) );
        REQUIRE( reference == Approx( bvpd->conditionalCumulativeProbability
                                      ( event, condition) ) );
      }
      condition = 0.5 * ( conditions[1] + conditions[2] );
      for( auto event : events ){
        auto reference = 0.5 * ( cdf1(event) + cdf2(event) );
        REQUIRE( reference == Approx( bvpd->conditionalCumulativeProbability
                                      ( event, condition) ) );
      }
      condition = 0.25 * ( conditions[1] + 3 * conditions[2] );
      for( auto event : events ){
        auto reference = 0.25 * ( cdf1(event) + 3 * cdf2(event) );
        REQUIRE( reference == Approx( bvpd->conditionalCumulativeProbability
                                      ( event, condition) ) );
      }
    }
  }   // GIVEN

  GIVEN( "invalid conditions" ){
    LOG(INFO) << "Test " << ++testNumber
              << ": [conditionalCumulativeProbability] Errors Expected";
    std::vector<double> conditions = {-0.00001, 2.1};
    GIVEN( "valid events" ){
      THEN( "exceptions will be thrown" ){
        for ( double c : conditions ){
          REQUIRE_THROWS( bvpd->conditionalCumulativeProbability(0.0, c) );
        }
      }
    }
  }   // GIVEN
}   // SCENARIO
