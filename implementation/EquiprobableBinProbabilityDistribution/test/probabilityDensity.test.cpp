#include <array>

#include "catch.hpp"

#include "math/implementation/EquiprobableBinProbabilityDistribution.hpp"

extern int testNumber;
extern std::array<double, 33> v;

extern math::implementation::DataReferencingEquiprobableBinProbabilityDistribution
< std::array< double, 33 >::iterator > epbpd;

extern math::API::ProbabilityDistribution& pd;

SCENARIO("The probabilityDensity method will return the correct value",
         "[math], "
         "[EquiprobableBinProbabilityDistribution], [probabilityDensity]"){
  GIVEN("event values within bin boundaries"){
    WHEN("the event falls on within a bin"){
      THEN
        ("the product of the returned value and the bin width will be constant"){
        std::array<double, 33> binPDFvalues; 
        for (int i = 0; i < 32; ++i) { 
          binPDFvalues[i] = epbpd.probabilityDensity(0.5*(v[i] + v[i+1]));
        }
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] No Errors Expected";
        for (int i = 0; i < 32; ++i) {
          REQUIRE( 1.0 / 32.0 == Approx(binPDFvalues[i] * (v[i+1] - v[i])));
        }
        for (int i = 0; i < 32; ++i) {
          binPDFvalues[i] = pd.probabilityDensity(0.5*(v[i] + v[i+1]));
        }
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] No Errors Expected";
        for (int i = 0; i < 32; ++i) {
          REQUIRE( 1.0 / 32.0 == Approx(binPDFvalues[i] * (v[i+1] - v[i])));
        }
      }
    }
    
    WHEN("the event falls on a bin boundary"){
      THEN("the value  will be the average of the adjacent bins"){
        std::array<double, 33> binPDFvalues;
        for (int i = 0; i < 32; ++i) { 
          binPDFvalues[i] = epbpd.probabilityDensity(0.5*(v[i] + v[i+1]));
        }
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] No Errors Expected";
        REQUIRE( binPDFvalues[0] ==
                   Approx(epbpd.probabilityDensity(v[0])));
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] No Errors Expected";
        for (int i = 1; i < 32; ++i){
          REQUIRE( (binPDFvalues[i-1] + binPDFvalues[i]) / 2.0 ==
                   Approx(epbpd.probabilityDensity(v[i])));
        }
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] NO Errors Expected";
        REQUIRE( binPDFvalues[31] ==
                 Approx(epbpd.probabilityDensity(v[32])));
        for (int i = 0; i < 32; ++i) {
          binPDFvalues[i] = pd.probabilityDensity((v[i] + v[i+1])/2.0);
        }
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] No Errors Expected";
        REQUIRE( binPDFvalues[0] ==
                   Approx(pd.probabilityDensity(v[0])));
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] No Errors Expected";
        for (int i = 1; i < 32; ++i){
          REQUIRE( (binPDFvalues[i-1] + binPDFvalues[i]) / 2.0 ==
                   Approx(pd.probabilityDensity(v[i])));
        }
        LOG(INFO) << "Test " <<
          ++testNumber << ": [probabilityDensity] NO Errors Expected";
        REQUIRE( binPDFvalues[31] ==
                 Approx(pd.probabilityDensity(v[32])));
      }
    }
  }

  GIVEN("events outside the bin boundaries"){
        const std::vector<double> mus = {-1.000001, 1.0000001};
    WHEN("passed to the probabilityDensity method"){
      THEN("the method will return 0"){
        for (auto mu : mus){
          LOG(INFO) << "Test " <<
            ++testNumber << ": [probabilityDensity] No Errors Expected";
          REQUIRE(epbpd.probabilityDensity(mu) == 0);
          LOG(INFO) << "Test " <<
            ++testNumber << ": [probabilityDensity] No Errors Expected";
          REQUIRE(pd.probabilityDensity(mu) == 0);
        }
      }
    }
  }
}
