#include "catch.hpp"

#include "math/interpolate.hpp"
#include "math/implementation/SplicedProbabilityDistribution.hpp"

extern int testNumber;
extern std::function<double(double)> CDFRef;

extern math::implementation::SplicedProbabilityDistribution
< math::interpolate::linLin, math::interpolate::linLin >
splicedDistribution;

SCENARIO("The spliced probability distribution implementation's cumulative"
         " probability method will return a value that matches the composed CDF",
         "[math], [SplicedProbabilityDistribution], [cumulativeProbability]"){
  GIVEN("a spliced probability distribution"){
    WHEN("queried for a cumulative probability"){
      THEN("the value returned will match the reference CDF"){
        std::vector<double> X = {-1.0, 0.0, 1.0};
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        for (auto x : X){         
          REQUIRE( CDFRef(x) == splicedDistribution.cumulativeProbability(x));
        }
      }
    }
  }
}
