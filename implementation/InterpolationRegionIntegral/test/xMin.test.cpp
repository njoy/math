#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationRegionIntegral.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::unique_ptr
< math::implementation::InterpolationRegionIntegral
  <std::vector<double>::iterator, math::interpolate::linLin> >
liir;

SCENARIO("The interpolation region integral's xMin functions correctly",
         "[math], [InterpolationRegionIntegral], [xMin]"){
  GIVEN("An InterpolationRegionIntegral and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the minimum x-value"){
      THEN("the returned value will return the first value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMin] No Errors Expected";
        REQUIRE(x.front() == liir->xMin());
      }
    }
  }
}
