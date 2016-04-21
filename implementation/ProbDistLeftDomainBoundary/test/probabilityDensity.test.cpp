#include "catch.hpp"

#include "math/implementation/ParametricProbabilityDistribution.hpp"
#include "math/implementation/ProbDistLeftDomainBoundary.hpp"

extern int testNumber;
extern std::function<double(double)> PDF;

extern math::implementation::ProbDistLeftDomainBoundary
< math::implementation::ParametricProbabilityDistribution
< std::function<double(double)>, std::function<double(double)> > >
probabilityDistribution;

SCENARIO("The ProbDistLeftDomainBoundary implementation's probability "
         " density method will throw appropriately ",
         "[math], [ProbDistLeftDomainBoundary], [probabilityDensity]"){
  GIVEN("a probability distribution"){
    WHEN("queried for a probability density"){
      THEN("will throw if value left of boundary"){
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] Errors Expected";
        REQUIRE_THROWS(probabilityDistribution.probabilityDensity(-1.1));
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] No Errors Expected";
        REQUIRE(probabilityDistribution.probabilityDensity(-1.0) == PDF(-1.0));
      }
    }
  }
}
