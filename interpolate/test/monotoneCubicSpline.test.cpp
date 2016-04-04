#include <algorithm>

#include "catch.hpp"

#include "math/interpolate.hpp"

extern int testNumber;

SCENARIO("The monotone cubic spline will not violate monotonicity of a function"
         " that has a boundary derivative to average derivative ratio greater" 
         " than 3",
         "[math], [interpolate], [monotoneCubicSpline]"){
  GIVEN("a function a cubic hermite spline would represent poorly"){
    auto f = [](const double x){
      return std::pow((x - 2.0), 4);
    };
    auto F = [](const double x){
      return
      0.2 * std::pow(x, 5) - 2.0 * std::pow(x, 4) +
      8.0 * std::pow(x, 3) - 16.0 * std::pow(x, 2) + 16.0 * x;
    };
    WHEN("evaluated using the monotone cubic spline"){
      const double f0 = f(0.0), f4 = f(4.0);
      const double F0 = F(0.0), F4 = F(4.0);
      int evaluations = 10001;
      std::vector<double> y;
      y.reserve(evaluations);
      double x = 0.0;
      double dx = 4.0 / 10000.0;
      while (evaluations--){
        y.push_back
          (math::interpolate::monotoneCubicSpline(x, 0.0, 4.0, F0, F4, f0, f4));
        x += dx;
      }
      THEN("the monotonicity property will be preserved"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [monotoneCubicSpline] No Errors Expected";
        REQUIRE(std::is_sorted(y.begin(), y.end()));
      }
    }
  }
}
