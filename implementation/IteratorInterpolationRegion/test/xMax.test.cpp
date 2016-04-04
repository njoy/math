#include <vector>

#include "catch.hpp"

#include "math/implementation/IteratorInterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x;
extern math::implementation::IteratorInterpolationRegion
<std::vector<double>::iterator, math::interpolate::linLin>
liir;

SCENARIO("The iterator interpolation region's xMax functions correctly",
         "[math], [IteratorInterpolationRegion], [xMax]"){
  GIVEN("An IteratorInterpolationRegion and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the maximum x-value"){
      THEN("the returned value will return the last value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMax] No Errors Expected";
        REQUIRE(x.back() == liir.xMax());
      }
    }
  }
}
