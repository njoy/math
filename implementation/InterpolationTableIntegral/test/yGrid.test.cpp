#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationTableIntegral.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> y;

extern math::implementation::InterpolationTableIntegral
< std::vector<double>::iterator, math::interpolate::linLin > iti;

SCENARIO("The interpolation table integral's yGrid functions correctly",
         "[math], [InterpolationTableIntegral], [yGrid]"){
  GIVEN("An InterpolationTableIntegral and "
        "the vector of dependent variable values used in its construction"){    
    WHEN("queried for the yGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [yGrid] No Errors Expected";
        std::vector<double> Y {0.0, 6.0, 14.0, 24.0, 36.0};
        auto grid = iti.yGrid()[0];
        for (std::size_t i = 0; i < grid.size(); ++i){
          REQUIRE(Y[i] == Approx(grid[i]));
        }
        REQUIRE(Y.size() == grid.size());
      }
    }
  }
}

SCENARIO("The constant interpolation region integral's yGrid functions correctly",
         "[math], [InterpolationTableIntegral], [yGrid]"){
  GIVEN("An InterpolationTableIntegral and "
        "the vector of independent variable values used in its construction"){    
    const auto& citi = iti;
    WHEN("queried for the yGrid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [yGrid] No Errors Expected";
        std::vector<double> Y {0.0, 6.0, 14.0, 24.0, 36.0};
        auto grid = citi.yGrid()[0];
        for (std::size_t i = 0; i < grid.size(); ++i){
          REQUIRE(Y[i] == Approx(grid[i]));
        }
        REQUIRE(Y.size() == grid.size());
      }
    }
  }
}
