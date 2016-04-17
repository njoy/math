#include "catch.hpp"

#include "math/implementation/ParametricProbabilityDistribution.hpp"
#include "math/implementation/ProbDistLeftInterval.hpp"

extern int testNumber;
extern std::function<double(double)> PDF;

extern math::implementation::ProbDistLeftInterval
< math::implementation::ParametricProbabilityDistribution
< std::function<double(double)>, std::function<double(double)> > >
probabilityDistribution;

SCENARIO("The ProbDistLeftInterval implementation's cumulative"
         " probability method will throw appropriately ",
         "[math], [ProbDistLeftInterval], [cumulativeProbability]"){
  GIVEN("a probability distribution"){
    WHEN("queried for a cumulative probability"){
      THEN("will throw if value left of boundary"){
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        REQUIRE(probabilityDistribution.cumulativeProbability(-1.1) == 0.0);
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        REQUIRE(
          probabilityDistribution.cumulativeProbability(-1.0) == PDF(-1.0));
      }
    }
  }
}
