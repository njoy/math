#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationTableIntegral.hpp"

extern int testNumber;
extern std::vector<double> x;
extern math::implementation::InterpolationTableIntegral
< std::vector<double>::iterator, math::interpolate::linLin > iti;

SCENARIO("The interpolation table integral's xMin functions correctly",
         "[math], [InterpolationTableIntegral], [xMin]"){
  GIVEN("An InterpolationTableIntegral and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the minimum x-value"){
      THEN("the returned value will return the first value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMin] No Errors Expected";
        REQUIRE( x.front() == iti.xMin() );
      }
    }
  }
}
