#include <vector>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTable.hpp"

extern int testNumber;
extern std::vector<double> y00;
extern std::vector<double> y01;
extern std::unique_ptr<math::implementation::CompositeInterpolationTable> cit;

SCENARIO("The composite interpolation table's yGrid functions correctly",
         "[math], [CompositeInterpolationTable], [yGrid]"){
  GIVEN("An CompositeInterpolationTable and "
        "the vector of dependent variable values used in its construction"){    
    WHEN("queried for the yGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [yGrid] No Errors Expected";
        auto grids = cit->yGrid();
        REQUIRE(true == std::equal(grids[0].begin(), grids[0].end(),
                                   y00.begin(), y00.end()));
        REQUIRE(true == std::equal(grids[1].begin(), grids[1].end(),
                                   y01.begin(), y01.end()));
   
      }
    }
  }
}
