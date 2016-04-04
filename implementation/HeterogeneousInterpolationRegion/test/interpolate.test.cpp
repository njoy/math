#include <vector>

#include "catch.hpp"

#include "math/implementation/HeterogeneousInterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x0;
extern std::vector<double> x1;
extern std::vector<double> y0_;
extern std::vector<double> y1_;
extern std::function<double(double)> f;
extern std::unique_ptr<math::API::InterpolationRegion> hir;

SCENARIO("The iterator interpolation region's interpolate functions correctly",
         "[math], [HeterogeneousInterpolationRegion], [interpolate]"){
  GIVEN("An HeterogeneousInterpolationRegion and "
        "the vectors of the independent variable and "
        "dependent variable values used in its construction"){    
    WHEN("when interpolation is requested within the dependent variable range"){
      THEN("the returned value will match the generating function "){
        LOG(INFO) << "Test " << ++testNumber << ": [interpolate] No Errors Expected";
        for (auto xVal : x0){
          REQUIRE(f(xVal) == Approx(hir->interpolate(xVal)));
        }
        for (auto xVal : x1){
          REQUIRE(f(xVal) == Approx(hir->interpolate(xVal)));
        }
        LOG(INFO) << "Test " << ++testNumber << ": [interpolate] No Errors Expected";
        double xVal;
        for (auto it = x0.begin()+1, end = x0.end();
             it != end;
             it++){
          xVal = (it[0] + it[-1])/2.0;
          REQUIRE(f(xVal) == Approx(hir->interpolate(xVal)));
        }
        for (auto it = x1.begin()+1, end = x1.end();
             it != end;
             it++){
          xVal = (it[0] + it[-1])/2.0;
          REQUIRE(f(xVal) == Approx(hir->interpolate(xVal)));
        }
      }
    }
/* We haven't decided how to handle out of bounds requests */
    /*
    WHEN("when interpolation is requested outside the dependent variable range"){
      THEN(" "){
      }
    }
    */
  }
}
