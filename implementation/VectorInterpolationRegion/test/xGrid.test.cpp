#include <vector>

#include "catch.hpp"

#include "math/implementation/VectorInterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> y;
extern math::implementation::VectorInterpolationRegion<math::interpolate::linLin>
lvir;

SCENARIO("The vector interpolation region's xGrid functions correctly",
         "[math], [VectorInterpolationRegion], [xGrid]"){
  GIVEN("An VectorInterpolationRegion and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the xGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xGrid] No Errors Expected";
        auto grid = lvir.xGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   x.begin(), x.end()));
      }
    }
  }
}

SCENARIO("The constant vector interpolation region's xGrid functions correctly",
         "[math], [VectorInterpolationRegion], [xGrid]"){
  GIVEN("An VectorInterpolationRegion and "
        "the vector of independent variable values used in its construction"){
    std::vector<double> xClone = x;
    std::vector<double> yClone = y;
    const math::implementation::VectorInterpolationRegion<math::interpolate::linLin>
      clvir(std::move(xClone), std::move(yClone), false);
    WHEN("queried for the xGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xGrid] No Errors Expected";
        auto grid = clvir.xGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   x.begin(), x.end()));
      }
    }
  }
}
