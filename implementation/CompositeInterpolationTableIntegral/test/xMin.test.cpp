#include <vector>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTable.hpp"

extern int testNumber;
extern std::vector<double> x00;
extern std::unique_ptr<math::implementation::CompositeInterpolationTable> cit;

SCENARIO("The composite interpolation table integral's xMin functions correctly",
         "[math], [CompositeInterpolationTable], [xMin]"){
  GIVEN("An CompositeInterpolationTable and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the minimum x-value"){
      THEN("the returned value will return the first value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMin] No Errors Expected";
        REQUIRE(x00.front() == cit->xMin());
      }
    }
  }
}
