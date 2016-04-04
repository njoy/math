#include <vector>

#include "catch.hpp"

#include "math/API/InterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> y0_;
extern std::vector<double> y1_;
extern std::unique_ptr<math::API::InterpolationRegion> hir;

SCENARIO("The iterator interpolation region's yGrid functions correctly",
         "[math], [HeterogeneousInterpolationRegion], [yGrid]"){
  GIVEN("An HeterogeneousInterpolationRegion and "
        "the vector of dependent variable values used in its construction"){    
    WHEN("queried for the yGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [yGrid] No Errors Expected";
        auto grids = hir->yGrid();
        REQUIRE(true == std::equal(grids[0].begin(), grids[0].end(),
                                   y0_.begin(), y0_.end()));
        REQUIRE(true == std::equal(grids[1].begin(), grids[1].end(),
                                   y1_.begin(), y1_.end()));
   
      }
    }
  }
}
