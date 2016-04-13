#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationTableIntegral.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> y;

extern math::implementation::InterpolationTableIntegral
< std::vector<double>::iterator, math::interpolate::linLin > iti;

SCENARIO("The interpolation table integral's dyGrid functions correctly",
         "[math], [InterpolationTableIntegral], [dyGrid]"){
  GIVEN("An InterpolationTableIntegral and "
        "the vector of dependent variable values used in its construction"){    
    WHEN("queried for the dyGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [dyGrid] No Errors Expected";
        auto grid = iti.dyGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   y.begin(), y.end()));
      }
    }
  }
}

SCENARIO("The constant interpolation region integral's dyGrid functions correctly",
         "[math], [InterpolationTableIntegral], [dyGrid]"){
  GIVEN("An InterpolationTableIntegral and "
        "the vector of independent variable values used in its construction"){    
    const auto& citi = iti;
    WHEN("queried for the dyGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [dyGrid] No Errors Expected";
        auto grid = citi.dyGrid()[0];
        REQUIRE(true == std::equal(grid.begin(), grid.end(),
                                   y.begin(), y.end()));
      }
    }
  }
}
