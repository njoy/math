#include <functional>

#include "catch.hpp"

#include "math/implementation/IteratorLegendreSeries.hpp"

extern int testNumber;
extern std::vector
<math::implementation::IteratorLegendreSeries
 < std::vector<double>::iterator  > > ils;
extern std::vector< std::function< double(double) > > diffReferences;

SCENARIO(
  "The iterator legendre series derivative function"
  " will return the correct value",
  "[math], [IteratorLegendreSeries], [derivative]"){
  GIVEN("an IteratorLegendreSeries and a reference function"){
    WHEN("queried for a function derivative value"){
      THEN("the values will match"){
        double dx = 2.0/100.0;
        double x;
        int i;
        for (std::size_t j = 0; j < ils.size(); ++j){
          i = 101;
          x = -1.0;
          LOG(INFO) << "Test " << ++testNumber
                    << ": [derivative] No Errors Expected";
          while (i--){
            REQUIRE( ils[j].derivative(x) == Approx(diffReferences[j](x)) );
            x+= dx;
          }
        }
      }
    }
  }
}

SCENARIO(
  "The iterator legendre series derivative function will evaluate efficiently",
  "[math], [IteratorLegendreSeries], [benchmark], [hide]"){
  GIVEN("an IteratorLegendreSeries"){
    WHEN("queried for a function value"){
      double result;
      THEN("the values will match the reference"){
        std::vector<double> coef;
        coef.resize(65, 0);
        coef.back() = 1;
        math::implementation::IteratorLegendreSeries
          < std::vector<double>::iterator  >
          bench(coef.begin(), coef.end());
        result = bench.derivative(0.5);
        REQUIRE( result == Approx(-5.6416));
      }
      LOG(INFO) << "dP_64/dx(0.5) = " << result;
    }
  }
}
