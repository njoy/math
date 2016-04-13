#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationTableIntegral.hpp"

extern int testNumber;

SCENARIO("The interpolation table integral's assembleYGrid functions correctly",
         "[math], [InterpolationTableIntegral], [assembleYGrid]"){
  GIVEN("An InterpolationRegionIntegral and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the the integral grid"){
      THEN("the returned value will return be equal to the reference vector"){
        using linLinIntegral = 
          math::implementation::InterpolationTableIntegral
          < std::vector<double>::iterator, math::interpolate::linLin >;
        LOG(INFO) << "Test " << ++testNumber
                  << ": [assembleY] No Errors Expected";
        std::vector<double> x {0.0, 1.0, 2.0, 3.0, 4.0};
        std::vector<double> y {5.0, 7.0, 9.0, 11.0, 13.0};
        std::vector<double> Y {0.0, 6.0, 14.0, 24.0, 36.0};
        auto grid = linLinIntegral::assembleYGrid(x.begin(), y.begin(), 5, 0.0);
        for (int i = 0; i < 5; ++i){
          REQUIRE( Y[i] == Approx(grid[i]) );
        }
      }
    }
  }
}
