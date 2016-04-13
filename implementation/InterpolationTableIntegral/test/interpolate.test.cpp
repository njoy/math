#include <vector>

#include "catch.hpp"

#include "math/implementation/InterpolationTableIntegral.hpp"

extern int testNumber;
extern std::vector<double> x;
extern math::implementation::InterpolationTableIntegral
 < std::vector<double>::iterator, math::interpolate::linLin > iti;

SCENARIO("The interpolation table's interpolate functions correctly",
         "[math], [InterpolationTableIntegral], [interpolate]"){
  GIVEN("An InterpolationTableIntegral and"
        " the vectors of the independent variable and "
        " dependent variable values used in its construction"){    
    WHEN("when interpolation is requested within the dependent variable range"){
      THEN("the returned value will match the generating function "){
        auto F = []( const double x ){ return 5.0 * x + pow(x, 2); };
        LOG(INFO) << "Test " << ++testNumber
                  << ": [interpolate] No Errors Expected";
        for (auto xVal : x){
          REQUIRE( F(xVal) == iti.interpolate(xVal) );
          REQUIRE( F(xVal) == iti(xVal) );
        }
        LOG(INFO) << "Test " << ++testNumber
                  << ": [interpolate] No Errors Expected";
        double xVal;
        for (auto it = x.begin()+1, end = x.end(); it != end; it++){
          xVal = 0.5 * ( it[0] + it[-1] );
          REQUIRE( F(xVal) == iti.interpolate(xVal) );
          REQUIRE( F(xVal) == iti(xVal) );
        }
      }
    }
  }
}
