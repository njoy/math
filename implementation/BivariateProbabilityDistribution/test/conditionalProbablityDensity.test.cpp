#include "catch.hpp"

#include "math/implementation/BivariateProbabilityDistribution.hpp"

extern int testNumber;
extern std::unique_ptr
  < math::implementation::BivariateProbabilityDistribution
  < math::interpolate::linLin, math::interpolate::linLin > > bvpd;

SCENARIO(
  "The probability density will return a value that matches the composed PDF", 
  "[math], [implementation],"
  "[BivariateProbabilityDistribution], [conditionalProbabilityDensity]"){
  GIVEN( "valid conditions" ){
    LOG(INFO) << "Test " <<
      ++testNumber << ": [conditionalProbabilityDensity] No Errors Expected";
    WHEN( "the condition falls on a boundary" ){
      std::vector<double> conditions = bvpd->conditions;

      THEN( "the return value will match the reference" ){
        std::vector<double> events = {-1.0, -0.5, 0.0, 0.5, 1.0};
        for( size_t i = 0; i < conditions.size(); i++ ){
          double condition = conditions[i];
          auto& distribution = bvpd->conditionedProbabilityDistributions[i];

          for( double x : events ){
            REQUIRE( 
                distribution->probabilityDensity(x) == 
                bvpd->conditionalProbabilityDensity(x, condition) );
          }
        }
      }
    }
    WHEN( "the conditions are not on a boundary" ){
      /* This is not a good testing function. The first to conditioned
       * distributions always add up to be 1. */
      REQUIRE( 0.5    == bvpd->conditionalProbabilityDensity(0.5, 0.5) );
      REQUIRE( 0.5    == bvpd->conditionalProbabilityDensity(1.5, 0.5) );
      REQUIRE( 0.5    == bvpd->conditionalProbabilityDensity(2.5, 0.5) );

      REQUIRE( 0.375  == bvpd->conditionalProbabilityDensity(0.5, 1.5) );
      REQUIRE( 0.25   == bvpd->conditionalProbabilityDensity(1.0, 1.5) );
      REQUIRE( 0.125  == bvpd->conditionalProbabilityDensity(1.5, 1.5) );

      REQUIRE( 0.4375 == bvpd->conditionalProbabilityDensity(0.5, 1.75) );
      REQUIRE( 0.375  == bvpd->conditionalProbabilityDensity(1.0, 1.75) );
      REQUIRE( 0.3125 == bvpd->conditionalProbabilityDensity(1.5, 1.75) );

    }
  }   // GIVEN

  GIVEN( "invalid conditions" ){
    LOG(INFO) << "Test " <<
      ++testNumber << ": [conditionalProbabilityDensity] Errors Expected";
    std::vector<double> conditions = {2.1};
    GIVEN( "valid events" ){
      std::vector<double> events = {-1.0, -0.5, 0.0, 0.5, 1.0};
      THEN( "Excptions will be thrown" ){
        for( double e : events ){
          LOG(INFO) << "event: " << e;
          for ( double c : conditions ){
            LOG(INFO) << "Condition: " << c;
            REQUIRE_THROWS( bvpd->conditionalProbabilityDensity(e,c) );
          }
        }
      }
    }
  } // GIVEN---invalid conditions
}   // SCENARIO

