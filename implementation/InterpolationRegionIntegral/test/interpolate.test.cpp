#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationRegionIntegral.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::function<double(double)> F;
extern math::implementation::InterpolationRegionIntegral
<std::vector<double>::iterator, math::interpolate::linLin>
liir;

SCENARIO("The iterator interpolation region's interpolate functions correctly",
         "[math], [InterpolationRegionIntegral], [interpolate]"){
  GIVEN("An InterpolationRegionIntegral and "
        "the vectors of the independent variable and "
        "dependent variable values used in its construction"){    
    WHEN("when interpolation is requested within the dependent variable range"){
      THEN("the returned value will match the generating function "){
        LOG(INFO) << "Test " << ++testNumber << ": [interpolate] No Errors Expected";
        for (auto xVal : x){
          REQUIRE(F(xVal) == liir.interpolate(xVal));
        }
        LOG(INFO) << "Test " << ++testNumber << ": [interpolate] No Errors Expected";
        double xVal;
        for (auto it = x.begin()+1, end = x.end();
             it != end;
             it++){
          xVal = (it[0] + it[-1])/2.0;
          REQUIRE(F(xVal) == liir.interpolate(xVal));
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
