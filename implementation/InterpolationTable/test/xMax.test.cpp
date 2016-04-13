#include <vector>

#include "catch.hpp"

#include "math/implementation.hpp"

namespace mi = math::implementation; 

extern int testNumber;
extern std::vector<double> x;
extern math::implementation::InterpolationTable
< math::interpolate::linLin, mi::TransferPolicy, std::vector<double> >
ownedTable;

SCENARIO("The interpolation Table's xMax functions correctly",
         "[math], [InterpolationTable], [xMax]"){
  GIVEN("An InterpolationTable and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the maximum x-value"){
      THEN("the returned value will return the last value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMax] No Errors Expected";
        REQUIRE( x.back() == ownedTable.xMax() );
      }
    }
  }
}
