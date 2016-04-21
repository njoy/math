#include "catch.hpp"

#include "math/implementation/ParametricProbabilityDistribution.hpp"
#include "math/implementation/ProbDistRightDomainBoundary.hpp"

extern int testNumber;
extern std::function<double(double)> PDF;

extern math::implementation::ProbDistRightDomainBoundary
< math::implementation::ParametricProbabilityDistribution
< std::function<double(double)>, std::function<double(double)> > >
probabilityDistribution;

SCENARIO("The ProbDistRightDomainBoundary implementation's cumulative"
         " probability method will throw appropriately ",
         "[math], [ProbDistRightDomainBoundary], [cumulativeProbability]"){
  GIVEN("a probability distribution"){
    WHEN("queried for a cumulative probability"){
      THEN("will throw if value right of boundary"){
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] Errors Expected";
        REQUIRE_THROWS(probabilityDistribution.cumulativeProbability(1.1));
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        REQUIRE(probabilityDistribution.cumulativeProbability(1.0) == PDF(1.0));
      }
    }
  }
}
