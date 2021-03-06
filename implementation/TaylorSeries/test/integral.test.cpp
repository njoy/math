#include <functional>

#include "catch.hpp"

#include "math/implementation/TaylorSeries.hpp"

extern int testNumber;
extern std::function<double(double)> f_int;

extern math::implementation::DataReferencingTaylorSeries
< std::vector<double>::iterator > its;

extern math::API::SeriesExpansion& ser;

SCENARIO(
  "The taylor series integral function will return the correct value",
  "[math], [TaylorSeries], [integral]"){
  GIVEN("an TaylorSeries and a reference function"){
    WHEN("queried for a function integral value"){
      THEN("the values will match"){
        double dx = 4.0/100.0;
        double x = -2.0;
        int i = 100;
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integral] No Errors Expected";
        while (i--){
          REQUIRE( its.integral(x, x + dx) == Approx(f_int(x + dx) - f_int(x) ));
          REQUIRE( ser.integral(x, x + dx) == Approx(f_int(x + dx) - f_int(x) ));
          x+= dx;
        }
      }
    }
  }
}
