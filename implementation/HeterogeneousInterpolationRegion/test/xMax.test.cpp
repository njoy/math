#include <vector>

#include "catch.hpp"

#include "math/API/InterpolationRegion.hpp"

extern int testNumber;
extern std::vector<double> x1;
extern std::unique_ptr<math::API::InterpolationRegion> hir;

SCENARIO("The heterogeneous interpolation region's xMax functions correctly",
         "[math], [HeterogeneousInterpolationRegion], [xMax]"){
  GIVEN("An HeterogeneousInterpolationRegion and "
        "the vector of independent variable values used in its construction"){    
    WHEN("queried for the maximum x-value"){
      THEN("the returned value will return the last value of the vector"){
        LOG(INFO) << "Test " << ++testNumber << ": [xMax] No Errors Expected";
        REQUIRE(x1.back() == hir->xMax());
      }
    }
  }
}
