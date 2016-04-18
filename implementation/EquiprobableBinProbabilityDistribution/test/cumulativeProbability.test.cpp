#include <array>

#include "catch.hpp"

#include "math/implementation/EquiprobableBinProbabilityDistribution.hpp"

extern int testNumber;
extern std::array<double, 33> v;

extern math::implementation::DataReferencingEquiprobableBinProbabilityDistribution
< std::array< double, 33 >::iterator > epbpd;

extern math::API::ProbabilityDistribution& pd;

SCENARIO("The cumulativeProbability method will return the correct value",
         "[math], [EquiprobableBinProbabilityDistribution], [cumulativeProbability]"){
  GIVEN("event values within bin boundaries"){
    std::array<double, 33> binCDFvalues;
    for (int i = 0; i < 33; ++i) {
      binCDFvalues[i] = i * 1.0 / (32.0);
    }
    WHEN("passed to the cumulativeProbability method"){
      THEN("if the value is on a bin boundary, "
           "the value will be the correct multiple of the bin probability"){
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        for (int i = 0; i < 33; ++i){
          REQUIRE( binCDFvalues[i] ==
                   Approx(epbpd.cumulativeProbability(v[i])));
        }
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        for (int i = 0; i < 33; ++i){
          REQUIRE( binCDFvalues[i] ==
                   Approx(pd.cumulativeProbability(v[i])));
        }
      }
      THEN("if the value lies within a bin, the value will be correct"){
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        for (int i = 0; i < 32; ++i) {
          REQUIRE( binCDFvalues[i] + 0.5 / (32.0) ==
                   Approx(epbpd.cumulativeProbability((v[i+1] + v[i])/2.0)));
        }
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        for (int i = 0; i < 32; ++i) {
          REQUIRE( binCDFvalues[i] + 0.5 / (32.0) ==
                   Approx(pd.cumulativeProbability((v[i+1] + v[i])/2.0)));
        }
      }
    }
  }
  GIVEN("event values outside the bin values"){
    WHEN("passed to the cumulativeProbability method"){
      THEN("will return zero or one as appropriate"){
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        REQUIRE(epbpd.cumulativeProbability(-1.1) == Approx(0));
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        REQUIRE(epbpd.cumulativeProbability(1.1) == Approx(1));

        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        REQUIRE(pd.cumulativeProbability(-1.1) == Approx(0));
        LOG(INFO) << "Test " <<
          ++testNumber << ": [cumulativeProbability] No Errors Expected";
        REQUIRE(pd.cumulativeProbability(1.1) == Approx(1));
      }
    }
  }
}
