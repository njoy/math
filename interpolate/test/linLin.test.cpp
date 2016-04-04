#include "catch.hpp"

#include "math/interpolate.hpp"

extern int testNumber;

SCENARIO("The linear interpolation function will return a correct result",
         "[math], [interpolate], [linLin]"){
  GIVEN("Some simple linear interpolation problems"){
    WHEN("computed using the linLin function"){
      THEN("the correct value will be returned"){
        LOG(INFO) << "Test " << ++testNumber << ": [linLin] No Errors Expected";
        REQUIRE(0.5 == Approx( math::interpolate::linLin(0.5,
                                                         0.0, 1.0,
                                                         0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber << ": [linLin] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::linLin(0.5,
                                                         0.5, 1.0,
                                                         0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber << ": [linLin] No Errors Expected";
        REQUIRE(1.0 == Approx( math::interpolate::linLin(1.0,
                                                         0.0, 1.0,
                                                         0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber << ": [linLin] No Errors Expected";
        REQUIRE(0.5 == Approx( math::interpolate::linLin(0.5,
                                                         0.0, 1.0,
                                                         1.0, 0.0) ));
        LOG(INFO) << "Test " << ++testNumber << ": [linLin] No Errors Expected";
        REQUIRE(0.5 == Approx( math::interpolate::linLin(1.5,
                                                         1.0, 2.0,
                                                         0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber << ": [linLin] No Errors Expected";
        REQUIRE(0.25 == Approx( math::interpolate::linLin(0.5,
                                                          0.0, 1.0,
                                                          0.0, 0.5) ));
        LOG(INFO) << "Test " << ++testNumber << ": [linLin] No Errors Expected";
        REQUIRE(15.0 == Approx( math::interpolate::linLin(0.5,
                                                          0.0, 1.0,
                                                          10.0, 20.0) ));
        
      }
    }
  }
}
