#include <vector>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTableIntegral.hpp"

extern int testNumber;
extern std::vector<double> y00;
extern std::vector<double> y01;
extern std::unique_ptr
< math::implementation::CompositeInterpolationTableIntegral > cit;

SCENARIO("The composite interpolation table integral's yGrid functions correctly",
         "[math], [CompositeInterpolationTableIntegral], [yGrid]"){
  GIVEN("An CompositeInterpolationTableIntegral and "
        "the vector of dependent variable values used in its construction"){    
    WHEN("queried for the yGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [yGrid] No Errors Expected";
        const auto& ccit = cit; 
        auto grids = cit->yGrid();
        auto cGrids = ccit->yGrid();
        REQUIRE(grids[0].size() == y00.size());
        REQUIRE(cGrids[0].size() == y00.size());
        auto gridIt = grids[0].begin();
        auto cGridIt = cGrids[0].begin();
        for (auto y : y00){
          REQUIRE( y == Approx(*gridIt) );
          REQUIRE( y == Approx(*cGridIt) );
          ++gridIt;
          ++cGridIt;
        }
        REQUIRE(grids[1].size() == y01.size());
        REQUIRE(cGrids[1].size() == y01.size());
        gridIt = grids[1].begin();
        cGridIt = cGrids[1].begin();
        for (auto y : y01){
          REQUIRE( y == Approx(*gridIt) );
          REQUIRE( y == Approx(*cGridIt) );
          ++cGridIt;
          ++gridIt;
        }
      }
    }
  }
}
