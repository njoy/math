#include <functional>

#include "catch.hpp"

#include "math/implementation/TaylorSeries.hpp"

extern int testNumber;
extern std::function<double(double)> f;

extern math::implementation::DataReferencingTaylorSeries
< std::vector<double>::iterator > its;
extern math::API::SeriesExpansion& ser;

SCENARIO(
  "The taylor series evaluateuation function will return the correct value",
  "[math], [TaylorSeries], [evaluate]"){
  GIVEN("an TaylorSeries and a reference function"){
    WHEN("queried for a function value"){
      THEN("the values will match"){
        double dx = 4.0/100.0;
        double x = -2.0;
        int i = 101;
        LOG(INFO) << "Test " << ++testNumber << ": [evaluate] No Errors Expected";
        while (i--){
          REQUIRE( its.evaluate(x) == Approx(f(x)) );
          REQUIRE( its(x) == Approx(f(x)) );
          REQUIRE( ser.evaluate(x) == Approx(f(x)) );
          REQUIRE( ser(x) == Approx(f(x)) );
          x+= dx;
        }
      }
    }
  }
}
