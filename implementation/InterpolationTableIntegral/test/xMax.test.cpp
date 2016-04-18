#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationTableIntegral.hpp"

extern int testNumber;
extern std::vector<double> x;
extern math::implementation::InterpolationTableIntegral
< std::vector<double>::iterator, math::interpolate::linLin > iti;

SCENARIO("The interpolation table integrals's xMax functions correctly",
         "[math], [InterpolationTableIntegral], [xMax]"){
  GIVEN("An InterpolationTableIntegral and "
        "the vector of independent variable values used in its construction"){ 
    WHEN("queried for the maximum x-value"){
      THEN("the returned value will return the last value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMax] No Errors Expected";
        REQUIRE( x.back() == iti.xMax() );
      }
    }
  }
}
