#include <vector>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTableIntegral.hpp"

extern int testNumber;
extern std::vector<double> dy00;
extern std::vector<double> dy01;
extern std::unique_ptr
< math::implementation::CompositeInterpolationTableIntegral > cit;

SCENARIO("The composite interpolation table integral's dyGrid functions correctly",
         "[math], [CompositeInterpolationTableIntegral], [dyGrid]"){
  GIVEN("An CompositeInterpolationTableIntegral and "
        "the vector of dependent variable values used in its construction"){    
    WHEN("queried for the dyGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [dyGrid] No Errors Expected";
        auto grids = cit->dyGrid();
        REQUIRE(true == std::equal(grids[0].begin(), grids[0].end(),
                                   dy00.begin(), dy00.end()));
        REQUIRE(true == std::equal(grids[1].begin(), grids[1].end(),
                                   dy01.begin(), dy01.end()));
        const auto& ccit = *cit;
        auto cGrids = ccit.dyGrid();
        REQUIRE(true == std::equal(cGrids[0].begin(), cGrids[0].end(),
                                   dy00.begin(), dy00.end()));
        REQUIRE(true == std::equal(cGrids[1].begin(), cGrids[1].end(),
                                   dy01.begin(), dy01.end()));   
   
      }
    }
  }
}
