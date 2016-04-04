#include <vector>

#include "catch.hpp"

#include "math/implementation/VectorInterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> y;
extern std::function<double(double)> f;
extern math::implementation::VectorInterpolationRegion<math::interpolate::linLin>
lvir;

SCENARIO("The vector interpolation region's interpolate functions correctly",
         "[math], [VectorInterpolationRegion], [interpolate]"){
  GIVEN("An VectorInterpolationRegion and "
        "the vectors of the independent variable and "
        "dependent variable values used in its construction"){    
    WHEN("when interpolation is requested within the dependent variable range"){
      THEN("the returned value will match the generating function "){
        LOG(INFO) << "Test " << ++testNumber << ": [interpolate] No Errors Expected";
        for (auto xVal : x){
          REQUIRE(f(xVal) == lvir.interpolate(xVal));
        }
        LOG(INFO) << "Test " << ++testNumber << ": [interpolate] No Errors Expected";
        double xVal;
        for (auto it = x.begin()+1, end = x.end();
             it != end;
             it++){
          xVal = (it[0] + it[-1])/2.0;
          REQUIRE(f(xVal) == lvir.interpolate(xVal));
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
