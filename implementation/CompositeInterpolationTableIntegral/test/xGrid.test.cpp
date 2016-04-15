#include <vector>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTableIntegral.hpp"

extern int testNumber;
extern std::vector<double> x00;
extern std::vector<double> x01;
extern std::unique_ptr
< math::implementation::CompositeInterpolationTableIntegral > cit;

SCENARIO("The composite interpolation table integral's xGrid functions correctly",
         "[math], [CompositeInterpolationTableIntegral], [xGrid]"){
  GIVEN("An CompositeInterpolationTableIntegral and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the xGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xGrid] No Errors Expected";
        auto grids = cit->xGrid();
        REQUIRE(true == std::equal(grids[0].begin(), grids[0].end(),
                                   x00.begin(), x00.end()));
        REQUIRE(true == std::equal(grids[1].begin(), grids[1].end(),
                                   x01.begin(), x01.end()));
        const auto& ccit = cit;
        auto cGrids = ccit->xGrid();
        REQUIRE(true == std::equal(cGrids[0].begin(), cGrids[0].end(),
                                   x00.begin(), x00.end()));
        REQUIRE(true == std::equal(cGrids[1].begin(), cGrids[1].end(),
                                   x01.begin(), x01.end()));   
      }
    }
  }
}
