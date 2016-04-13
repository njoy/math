#include <vector>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTable.hpp"

extern int testNumber;
extern std::vector<double> x01;
extern std::unique_ptr<math::implementation::CompositeInterpolationTable> cit;

SCENARIO("The composite interpolation table's xMax functions correctly",
         "[math], [CompositeInterpolationTable], [xMax]"){
  GIVEN("An CompositeInterpolationTable and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the maximum x-value"){
      THEN("the returned value will return the last value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMax] No Errors Expected";
        REQUIRE(x01.back() == cit->xMax());
      }
    }
  }
}
