#include "catch.hpp"

#include "math/interpolate.hpp"

extern int testNumber;

SCENARIO("The histogram interpolation function will return a correct result",
         "[math], [interpolate], [histogram]"){
  GIVEN("Some simple interpolation problems"){
    WHEN("computed using the histogram function"){
      THEN("the correct value will be returned"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [histogram] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::histogram(0.5,
                                                            0.0, 1.0,
                                                            0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [histogram] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::histogram(0.5,
                                                            0.5, 1.0,
                                                            0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [histogram] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::histogram(1.0,
                                                            0.0, 1.0,
                                                            0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [histogram] No Errors Expected";
        REQUIRE(1.0 == Approx( math::interpolate::histogram(0.5,
                                                            0.0, 1.0,
                                                            1.0, 0.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [histogram] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::histogram(1.5,
                                                            1.0, 2.0,
                                                            0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [histogram] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::histogram(0.5,
                                                             0.0, 1.0,
                                                             0.0, 0.5) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [histogram] No Errors Expected";
        REQUIRE(10.0 == Approx( math::interpolate::histogram(0.5,
                                                             0.0, 1.0,
                                                             10.0, 20.0) ));
        
      }
    }
  }
}
