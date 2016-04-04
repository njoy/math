#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationRegionIntegral.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> y;
extern math::implementation::InterpolationRegionIntegral
<std::vector<double>::iterator, math::interpolate::linLin>
liir;

SCENARIO("The interpolation region integral's xGrid functions correctly",
         "[math], [InterpolationRegionIntegral], [xGrid]"){
  GIVEN("An InterpolationRegionIntegral and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the xGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xGrid] No Errors Expected";
        auto grid = liir.xGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   x.begin(), x.end()));
      }
    }
  }
}

SCENARIO(
  "The constant interpolation region integral's xGrid functions correctly",
  "[math], [InterpolationRegionIntegral], [xGrid]"){
  GIVEN("An InterpolationRegionIntegral and "
        "the vector of independent variable values used in its construction"){ 
    const math::implementation::InterpolationRegionIntegral
      <std::vector<double>::iterator, math::interpolate::linLin>
      cliir(x.begin(), x.end(), y.begin(), y.end(), false);
    WHEN("queried for the xGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xGrid] No Errors Expected";
        auto grid = cliir.xGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   x.begin(), x.end()));
      }
    }
  }
}
