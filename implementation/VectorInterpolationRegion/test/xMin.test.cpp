#include <vector>

#include "catch.hpp"

#include "math/implementation/VectorInterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x;
extern math::implementation::VectorInterpolationRegion< math::interpolate::linLin >
lvir;

SCENARIO("The vector interpolation region's xMin functions correctly",
         "[math], [VectorInterpolationRegion], [xMin]"){
  GIVEN("An VectorInterpolationRegion and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the minimum x-value"){
      THEN("the returned value will return the first value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMin] No Errors Expected";
        REQUIRE(x.front() == lvir.xMin());
      }
    }
  }
}
