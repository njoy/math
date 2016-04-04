#include <functional>

#include "catch.hpp"

#include "math/implementation/IteratorTaylorSeries.hpp"

extern int testNumber;
extern std::function<double(double)> f;
extern math::implementation::IteratorTaylorSeries<std::vector<double>::iterator>
its;
extern math::API::SeriesExpansion& ser;

SCENARIO(
  "The iterator taylor series evaluation function will return the correct value",
  "[math], [IteratorTaylorSeries], [eval]"){
  GIVEN("an IteratorTaylorSeries and a reference function"){
    WHEN("queried for a function value"){
      THEN("the values will match"){
        double dx = 4.0/100.0;
        double x = -2.0;
        int i = 101;
        LOG(INFO) << "Test " << ++testNumber << ": [eval] No Errors Expected";
        while (i--){
          REQUIRE( its.eval(x) == Approx(f(x)) );
          REQUIRE( its(x) == Approx(f(x)) );
          REQUIRE( ser.eval(x) == Approx(f(x)) );
          REQUIRE( ser(x) == Approx(f(x)) );
          x+= dx;
        }
      }
    }
  }
}
