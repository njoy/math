#include <vector>

#include "catch.hpp"

#include "math/implementation/VectorInterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> y;
extern math::implementation::VectorInterpolationRegion<math::interpolate::linLin>
lvir;

SCENARIO("The vector interpolation region's yGrid functions correctly",
         "[math], [VectorInterpolationRegion], [yGrid]"){
  GIVEN("An VectorInterpolationRegion and "
        "the vector of dependent variable values used in its construction"){    
    WHEN("queried for the yGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [yGrid] No Errors Expected";
        auto grid = lvir.yGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   y.begin(), y.end()));
      }
    }
  }
}

SCENARIO("The constant vector interpolation region's yGrid functions correctly",
         "[math], [VectorInterpolationRegion], [yGrid]"){
  GIVEN("An VectorInterpolationRegion and "
        "the vector of dependent variable values used in its construction"){
    std::vector<double> xClone = x;
    std::vector<double> yClone = y;
    const math::implementation::VectorInterpolationRegion<math::interpolate::linLin>
      clvir(std::move(xClone), std::move(yClone), false);
    WHEN("queried for the yGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [yGrid] No Errors Expected";
        auto grid = clvir.yGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   y.begin(), y.end()));
      }
    }
  }
}
