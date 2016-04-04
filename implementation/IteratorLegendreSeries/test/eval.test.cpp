#include <functional>

#include "catch.hpp"

#include "math/implementation/IteratorLegendreSeries.hpp"

extern int testNumber;
extern std::vector
<math::implementation::IteratorLegendreSeries
 < std::vector<double>::iterator  > > ils;
extern std::vector< std::function< double(double) > > evalReferences;

SCENARIO(
  "The iterator legendre series evaluation function will return the correct value",
  "[math], [IteratorLegendreSeries], [eval]"){
  GIVEN("an IteratorLegendreSeries and a reference function"){
    WHEN("queried for a function value"){
      THEN("the values will match"){
        double dx = 2.0/100.0;
        double x;
        int i;
        for (std::size_t j = 0; j < ils.size(); ++j){
          i = 101;
          x = -1.0;
          LOG(INFO) << "Test " << ++testNumber
                    << ": [eval] No Errors Expected";
          while (i--){
            REQUIRE( ils[j].eval(x) == Approx(evalReferences[j](x)) );
            REQUIRE( ils[j](x) == Approx(evalReferences[j](x)) );
            x+= dx;
          }
        }
      }
    }
  }
}

SCENARIO(
  "The iterator legendre series evaluation function will evaluate efficiently",
  "[math], [IteratorLegendreSeries], [eval], [benchmark], [hide]"){
  GIVEN("an IteratorLegendreSeries"){
    WHEN("queried for a function value"){
      double result;
      THEN("the values will match the reference"){
        std::vector<double> coef;
        coef.resize(65, 0);
        coef.back() = 1;
        math::implementation::IteratorLegendreSeries< std::vector<double>::iterator  >
          bench(coef.begin(), coef.end());
        result = bench(0.5);
        REQUIRE(
          result ==
          Approx(-0.07557123070468212702762938777250239575129629779440353356));
      }
      LOG(INFO) << "P_64(0.5) = " << result;
    }
  }
}
