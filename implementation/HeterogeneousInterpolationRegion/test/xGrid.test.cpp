#include <vector>

#include "catch.hpp"

#include "math/API/InterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x0;
extern std::vector<double> x1;
extern std::unique_ptr<math::API::InterpolationRegion> hir;

SCENARIO("The iterator interpolation region's xGrid functions correctly",
         "[math], [HeterogeneousInterpolationRegion], [xGrid]"){
  GIVEN("An HeterogeneousInterpolationRegion and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the xGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xGrid] No Errors Expected";
        auto grids = hir->xGrid();
        REQUIRE(true == std::equal(grids[0].begin(), grids[0].end(),
                                   x0.begin(), x0.end()));
        REQUIRE(true == std::equal(grids[1].begin(), grids[1].end(),
                                   x1.begin(), x1.end()));
   
      }
    }
  }
}
