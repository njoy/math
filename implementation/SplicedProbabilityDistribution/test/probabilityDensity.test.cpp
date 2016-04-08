#include "catch.hpp"

#include "math/interpolate.hpp"
#include "math/implementation/SplicedProbabilityDistribution.hpp"

extern int testNumber;
extern std::function<double(double)> PDFRef;

extern math::implementation::SplicedProbabilityDistribution
< math::interpolate::linLin, math::interpolate::linLin >
splicedDistribution;

SCENARIO("The spliced probability distribution implementation's probability"
         " density method will return a value that matches the composed PDF",
         "[math], [SplicedProbabilityDistribution], [probabilityDensity]"){
  GIVEN("a spliced probability distribution"){
    WHEN("queried for a probability density"){
      THEN("the value returned will match the reference PDF"){
        std::vector<double> X = {-1.0, 0.0, 1.0};
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] No Errors Expected";
        for (auto x : X){         
          REQUIRE( PDFRef(x) == splicedDistribution.probabilityDensity(x));
        }
      }
    }
  }
}
