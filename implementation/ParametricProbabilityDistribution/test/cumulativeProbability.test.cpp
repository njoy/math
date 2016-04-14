#include "catch.hpp"

#include "math/implementation/ParametricProbabilityDistribution.hpp"

extern int testNumber;
extern std::function<double(double)> CDF;

extern math::implementation::ParametricProbabilityDistribution
< std::function<double(double)>, std::function<double(double)> >
probabilityDistribution;

SCENARIO("The parametric probability distribution implementation's cumulative"
         " probability method will return a value that matches the composed CDF",
         "[math], [ParametricProbabilityDistribution], [cumulativeProbability]"){
  GIVEN("a probability distribution"){
    WHEN("queried for a cumulative probability"){
      THEN("the value returned will match the composed CDF"){
        std::vector<double> X = {-1.0, 0.0, 1.0};
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        for (auto x : X){         
          REQUIRE(probabilityDistribution.cumulativeProbability(x) == CDF(x));
        }
      }
    }
  }
}
