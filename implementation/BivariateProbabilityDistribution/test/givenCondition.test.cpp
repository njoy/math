#include "catch.hpp"

#include "math/implementation/BivariateProbabilityDistribution.hpp"

extern int testNumber;

extern std::vector<double> conditions;

extern std::unique_ptr
  < math::implementation::BivariateProbabilityDistribution
  < math::interpolate::linLin, math::interpolate::linLin > > bvpd;

SCENARIO(
  "The givenConditional method returns the a probability distribution consistant"
  " with the bivariate distribution", 
  "[math], [BivariateProbabilityDistribution], [givenCondition]"){
  GIVEN( "a conditioned probability distribution" ){
    WHEN( "the condition falls on a boundary" ){
      THEN( "the probability density values will be consistent" ){
        LOG(INFO) << "Test " << ++testNumber <<
          ": [conditionalProbabilityDensity] No Errors Expected";
        std::vector<double> events = {-1.0, -0.5, 0.0, 0.5, 1.0};

        for( auto condition : conditions ){
          auto probabilityDistributionPointer =
            bvpd->givenCondition( condition );
          auto& probabilityDistribution = *probabilityDistributionPointer;
          for( auto event : events ){
            REQUIRE( probabilityDistribution.probabilityDensity(event) ==
                     Approx( bvpd->conditionalProbabilityDensity( event, condition ) ) );
          }
        }
      }
    }

    WHEN( "the conditions are not on a boundary" ){
      THEN( "the probability density values will be consistent" ){
        LOG(INFO) << "Test " << ++testNumber <<
          ": [conditionalProbabilityDensity] No Errors Expected";
        
        for( auto conditionsIter = conditions.begin() + 1, end = conditions.end();
             conditionsIter != end;
             ++conditionsIter ){
          auto condition = 0.5*(conditionsIter[0] + conditionsIter[-1]);
          auto probabilityDistributionPointer =
            bvpd->givenCondition( condition );
          auto& probabilityDistribution = *probabilityDistributionPointer;
          std::vector<double> events = {-1.0, -0.5, 0.0, 0.5, 1.0};
          for( auto event : events ){
            REQUIRE( probabilityDistribution.probabilityDensity(event) ==
                     Approx( bvpd->conditionalProbabilityDensity( event, condition ) ) );
          }
        }
      }
    }
  }   // GIVEN

  GIVEN( "invalid conditions" ){
    LOG(INFO) << "Test " << ++testNumber
              << ": [conditionalProbabilityDensity] Errors Expected";
    std::vector<double> conditions = {-0.00001, 2.1};
    GIVEN( "valid events" ){
      THEN( "exceptions will be thrown" ){
        for ( double c : conditions ){
          REQUIRE_THROWS( bvpd->givenCondition( c ) );
        }
      }
    }
  } // GIVEN---invalid conditions
}   // SCENARIO

