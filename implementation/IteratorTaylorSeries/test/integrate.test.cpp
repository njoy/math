#include <functional>

#include "catch.hpp"

#include "math/implementation/IteratorTaylorSeries.hpp"

extern int testNumber;
extern std::function<double(double)> f;
extern std::function<double(double)> f_int;
extern math::implementation::IteratorTaylorSeries<std::vector<double>::iterator>
its;

SCENARIO(
  "The iterator taylor series integrate function will return an anti-derivative"
  " series's",
  "[math], [IteratorTaylorSeries], [integrate]"){
  GIVEN("an IteratorTaylorSeries and a reference function anti-derivative"){
    WHEN("asked to generate an integral series"){
      THEN("the values will match the reference"){
        {
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          auto integralSeries =
            math::implementation::VectorTaylorSeries(its.integrate(0, 0));
          double dx = 4.0/100.0;
          double x = -2.0;
          int i = 101;
          while (i--){
            REQUIRE( f_int(x) == Approx(integralSeries(x)) );
            x+= dx;
          }
        }
        {
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          auto integralSeries =
            math::implementation::VectorTaylorSeries(its.integrate(0, 1));
          double dx = 4.0/100.0;
          double x = -2.0;
          int i = 101;
          while (i--){
            REQUIRE( (f_int(x) + 1.0)== Approx(integralSeries(x)) );
            x+= dx;
          }
        }
        {
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          auto integralSeries =
            math::implementation::VectorTaylorSeries(its.integrate(1, 1));
          double dx = 4.0/100.0;
          double x = -2.0;
          int i = 101;
          double adjustment = 1.0 - f_int(1.0);
          while (i--){
            REQUIRE( (f_int(x) + adjustment)== Approx(integralSeries(x)) );
            x+= dx;
          }
        }
      }
    }
  }
}
