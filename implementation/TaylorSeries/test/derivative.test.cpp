#include <functional>

#include "catch.hpp"

#include "math/implementation/TaylorSeries.hpp"

extern int testNumber;
extern std::function<double(double)> f_deriv;

extern math::implementation::DataReferencingTaylorSeries
< std::vector<double>::iterator > its;

extern math::API::SeriesExpansion& ser;

SCENARIO(
  "The taylor series derivative function will return the correct value",
  "[math], [TaylorSeries], [derivative]"){
  GIVEN("an TaylorSeries and a reference function"){
    WHEN("queried for a function derivative value"){
      THEN("the values will match"){
        double dx = 4.0/100.0;
        double x = -2.0;
        int i = 101;
                LOG(INFO) << "Test " << ++testNumber
                          << ": [derivative] No Errors Expected";
        while (i--){
          REQUIRE( its.derivative(x) == Approx(f_deriv(x)) );
          REQUIRE( ser.derivative(x) == Approx(f_deriv(x)) );
          x+= dx;
        }
      }
    }
  }
}
