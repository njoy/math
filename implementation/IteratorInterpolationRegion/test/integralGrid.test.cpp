/*
#include <vector>

#include "catch.hpp"

#include "math/implementation/IteratorInterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> Y;
extern math::implementation::IteratorInterpolationRegion
<std::vector<double>::iterator, math::interpolate::linLin>
liir;

SCENARIO("The iterator interpolation region's integralGrid functions correctly",
         "[math], [IteratorInterpolationRegion], [integralGrid]"){
  GIVEN("An IteratorInterpolationRegion and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the integralGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralGrid] No Errors Expected";
        auto grid = liir.integralGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   Y.begin(), Y.end()));
      }
    }
  }
}
*/
