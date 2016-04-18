#include <vector>

#include "catch.hpp"

#include "math/implementation.hpp"

namespace mi = math::implementation; 

extern int testNumber;
extern std::vector<double> x;
extern math::implementation::InterpolationTable
< math::interpolate::linLin, mi::TransferPolicy, std::vector<double> >
ownedTable;

SCENARIO("The interpolation tables's xMin functions correctly",
         "[math], [InterpolationTable], [xMin]"){
  GIVEN("An InterpolationTable and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the minimum x-value"){
      THEN("the returned value will return the first value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMin] No Errors Expected";
        REQUIRE( x.front() == ownedTable.xMin() );
      }
    }
  }
}
