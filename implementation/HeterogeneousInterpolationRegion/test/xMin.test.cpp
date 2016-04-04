#include <vector>

#include "catch.hpp"

#include "math/API/InterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x0;
extern std::unique_ptr<math::API::InterpolationRegion> hir;

SCENARIO("The heterogeneous interpolation region's xMin functions correctly",
         "[math], [HeterogeneousInterpolationRegion], [xMin]"){
  GIVEN("An HeterogeneousInterpolationRegion and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the minimum x-value"){
      THEN("the returned value will return the first value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMin] No Errors Expected";
        REQUIRE(x0.front() == hir->xMin());
      }
    }
  }
}
