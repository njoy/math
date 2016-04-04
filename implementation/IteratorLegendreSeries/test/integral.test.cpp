#include <functional>

#include "catch.hpp"

#include "math/implementation/IteratorLegendreSeries.hpp"

extern int testNumber;
extern std::vector
<math::implementation::IteratorLegendreSeries
 < std::vector<double>::iterator  > > ils;
extern std::vector< std::function< double(double) > > integralReferences;

SCENARIO(
  "The iterator legendre series integral function"
  " will return the correct value",
  "[math], [IteratorLegendreSeries], [integral]"){
  GIVEN("an IteratorLegendreSeries and a reference function"){
    WHEN("queried for a function integral value"){
      THEN("the values will match"){
        double dx = 2.0/100.0;
        double x;
        int i;
        for (std::size_t j = 0; j < ils.size(); ++j){
          i = 100;
          x = -1.0;
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integral] No Errors Expected";
          while (i--){
            REQUIRE( ils[j].integral(x, x + dx)  ==
                     Approx((integralReferences[j](x + dx) -
                             integralReferences[j](x)) ));
            x+= dx;
          }
        }
      }
    }
  }
}
