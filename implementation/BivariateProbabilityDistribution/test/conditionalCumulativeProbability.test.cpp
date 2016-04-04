#include "catch.hpp"

#include "math/implementation/BivariateProbabilityDistribution.hpp"

extern int testNumber;
extern std::unique_ptr
  < math::implementation::BivariateProbabilityDistribution
  < math::interpolate::linLin, math::interpolate::linLin > > bvpd;

SCENARIO(
  "The conditional cumulative probability will return a value that matches the"
  "composed CDF", 
  "[math], [implementation],"
  "[BivariateProbabilityDistribution], [conditionalCumulativeProbability]"){
  GIVEN( "valid conditions" ){
    LOG(INFO) << "Test " << ++testNumber << 
      ": [conditionalCumulativeProbability] No Errors Expected";
    WHEN( "the condition falls on a boundary" ){
    std::vector<double> conditions = bvpd->conditions;

      THEN( "the return value will match the reference" ){
        std::vector<double> events = {-1.0, -0.5, 0.0, 0.5, 1.0};
        for( size_t i = 0; i < conditions.size(); i++ ){
          double condition = conditions[i];
          auto& distribution = bvpd->conditionedProbabilityDistributions[i];

          for( double x : events ){
            REQUIRE( 
                distribution->cumulativeProbability(x) == 
                bvpd->conditionalCumulativeProbability(x, condition) );
          }
        }
      }
    }
    WHEN( "the conditions are not on a boundary" ){
      REQUIRE( 0.75     == bvpd->conditionalCumulativeProbability(0.5, 0.5) );
      REQUIRE( 1.25     == bvpd->conditionalCumulativeProbability(1.5, 0.5) );
      REQUIRE( 1.75     == bvpd->conditionalCumulativeProbability(2.5, 0.5) );

      REQUIRE( 0.84375  == bvpd->conditionalCumulativeProbability(0.5, 1.5) );
      REQUIRE( 1.0      == bvpd->conditionalCumulativeProbability(1.0, 1.5) );
      REQUIRE( 1.09375  == bvpd->conditionalCumulativeProbability(1.5, 1.5) );

      REQUIRE( 0.796875 == bvpd->conditionalCumulativeProbability(0.5, 1.75) );
      REQUIRE( 1.0      == bvpd->conditionalCumulativeProbability(1.0, 1.75) );
      REQUIRE( 1.171875 == bvpd->conditionalCumulativeProbability(1.5, 1.75) );

    }
  }   // GIVEN

  GIVEN( "invalid conditions" ){
    LOG(INFO) << "Test " <<
      ++testNumber << ": [conditionalCumulativeProbability] Errors Expected";
    std::vector<double> conditions = {2.1};
    GIVEN( "valid events" ){
      std::vector<double> events = {-1.0, -0.5, 0.0, 0.5, 1.0};
      THEN( "Excptions will be thrown" ){
        for( double e : events ){
          for ( double c : conditions ){
            REQUIRE_THROWS( bvpd->conditionalCumulativeProbability(e,c) );
          }
        }
      }
    }
  }   // GIVEN
}   // SCENARIO
