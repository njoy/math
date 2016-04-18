#include <vector>

#include "catch.hpp"

#include "math/implementation.hpp"

namespace mi = math::implementation; 

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> y;
extern math::implementation::InterpolationTable
< math::interpolate::linLin, mi::TransferPolicy, std::vector<double> >
ownedTable;

SCENARIO("The interpolation table's yGrid functions correctly",
         "[math], [InterpolationTable], [yGrid]"){
  GIVEN("An InterpolationTable and "
        "the vector of dependent variable values used in its construction"){    
    WHEN("queried for the yGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [yGrid] No Errors Expected";
        auto grid = ownedTable.yGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   y.begin(), y.end()));
      }
    }
  }
}

SCENARIO("The constant interpolation table's yGrid functions correctly",
         "[math], [InterpolationTable], [yGrid]"){
  GIVEN("An InterpolationTable and "
        "the vector of independent variable values used in its construction"){    
    const auto& constOwnedTable = ownedTable; 
    WHEN("queried for the yGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [yGrid] No Errors Expected";
        auto grid = constOwnedTable.yGrid()[0];
        REQUIRE(true == std::equal( grid.begin(), grid.end(),
                                    y.begin(), y.end() ));
      }
    }
  }
}
