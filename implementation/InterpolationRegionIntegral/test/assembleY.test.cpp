#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationRegionIntegral.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> y;
extern std::vector<double> Y;
extern math::implementation::IteratorInterpolationRegion
<std::vector<double>::iterator, math::interpolate::linLin>
liir;

SCENARIO("The interpolation region integral's assembleY functions correctly",
         "[math], [InterpolationRegionIntegral], [assembleY]"){
  GIVEN("An InterpolationRegionIntegral and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the the integral grid"){
      THEN("the returned value will return be equal to the reference vector"){
        typedef
          math::implementation::InterpolationRegionIntegral
          <std::vector<double>::iterator, math::interpolate::linLin>
          linLinIntegral;
        LOG(INFO) << "Test " << ++testNumber
                  << ": [assembleY] No Errors Expected";
        auto grid = linLinIntegral::assembleY(x.begin(), y.begin(), 5, 0.0);
        for (int i = 0; i < 5; ++i){
          REQUIRE(Y[i] == Approx(grid[i]));
        }
      }
    }
  }
}
