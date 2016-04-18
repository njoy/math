#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationTableIntegral.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> y;

extern math::implementation::InterpolationTableIntegral
< std::vector<double>::iterator, math::interpolate::linLin > iti;

SCENARIO("The interpolation table integral's xGrid functions correctly",
         "[math], [InterpolationTableIntegral], [xGrid]"){
  GIVEN("An InterpolationTableIntegral and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the xGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xGrid] No Errors Expected";
        auto grid = iti.xGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   x.begin(), x.end()));
      }
    }
  }
}

SCENARIO(
  "The constant interpolation region integral's xGrid functions correctly",
  "[math], [InterpolationTableIntegral], [xGrid]"){
  GIVEN("An InterpolationTableIntegral and "
        "the vector of independent variable values used in its construction"){ 
    const auto& citi = iti;
    WHEN("queried for the xGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xGrid] No Errors Expected";
        auto grid = citi.xGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   x.begin(), x.end()));
      }
    }
  }
}
