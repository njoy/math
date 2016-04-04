#include "catch.hpp"

#include "math/implementation/ProbabilityDistribution.hpp"

extern int testNumber;
extern std::function<double(double)> PDF;

extern math::implementation::ProbabilityDistribution
< std::function<double(double)>, std::function<double(double)> >
probabilityDistribution;

SCENARIO("The probability distribution implementation's probability density "
         "method will return a value that matches the composed PDF",
         "[math], [implementation], "
         "[ProbabilityDistribution], [probabilityDensity]"){
  GIVEN("a probability distribution"){
    WHEN("queried for a probability density"){
      THEN("the value returned will match the composed PDF"){
        std::vector<double> X = {-1.0, 0.0, 1.0};
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] No Errors Expected";
        for (auto x : X){         
          REQUIRE(probabilityDistribution.probabilityDensity(x) == PDF(x));
        }
      }
    }
  }
}
