#include <vector>

#include "catch.hpp"

#include "math/implementation/IteratorInterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x;
extern math::implementation::IteratorInterpolationRegion
<std::vector<double>::iterator, math::interpolate::linLin>
liir;

SCENARIO("The iterator interpolation region's xMin functions correctly",
         "[math], [IteratorInterpolationRegion], [xMin]"){
  GIVEN("An IteratorInterpolationRegion and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the minimum x-value"){
      THEN("the returned value will return the first value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMin] No Errors Expected";
        REQUIRE(x.front() == liir.xMin());
      }
    }
  }
}
