#include "catch.hpp"

#include "math/implementation/BivariateProbabilityDistribution.hpp"

extern int testNumber;

extern std::vector<double> conditions;

extern std::unique_ptr
  < math::implementation::BivariateProbabilityDistribution
  < math::interpolate::linLin, math::interpolate::linLin > > bvpd;

SCENARIO(
  "The upperConditionLimit method returns a value consisent with the conditions"
  " used in construction", 
  "[math], [BivariateProbabilityDistribution], [upperConditionLimit]"){
  GIVEN( "a bivariate distribution" ){
    WHEN( "queried for the upper limit on condition values" ){
      THEN( "the value will match the value used in construction" ){
        LOG(INFO) << "Test " << ++testNumber <<
          ": [upperConditionLimit] No Errors Expected";
        REQUIRE(conditions.back() == bvpd->upperConditionLimit());
      }
    }
  }
}
