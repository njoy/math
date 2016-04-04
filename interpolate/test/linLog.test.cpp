#include "catch.hpp"

#include "math/interpolate.hpp"

extern int testNumber;

SCENARIO("The linear-logarithmic interpolation function"
         " will return a correct result",
         "[math], [interpolate], [linLog]"){
  GIVEN("Some simple linear-logarithmic interpolation problems"){
    std::vector<double> X = {1E-5, 1E-2, 1, 10, 10000, 35000};
    auto f1 = [](double x){ return 13.2 * log(3.2*x);};
    auto f2 = [](double x){ return -5.6 * log(2.4*x);};
    WHEN("computed using the linLog function"){
      THEN("the correct value will be returned"){
        for (auto xit = X.begin() + 1, end = X.end();
             xit != end;
             ++xit){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [linLog] No Errors Expected";
          REQUIRE( f1(xit[-1]) ==
                   Approx( math::interpolate::linLog(xit[-1],
                                                     xit[-1], xit[0],
                                                     f1(xit[-1]), f1(xit[0]))));
          REQUIRE( f1(xit[0]) ==
                   Approx( math::interpolate::linLog(xit[0],
                                                     xit[-1], xit[0],
                                                     f1(xit[-1]), f1(xit[0]))));
          REQUIRE( f1((xit[-1] + xit[0]) * 0.5) ==
                   Approx( math::interpolate::linLog((xit[-1] + xit[0]) * 0.5,
                                                     xit[-1], xit[0],
                                                     f1(xit[-1]), f1(xit[0]))));
          LOG(INFO) << "Test " << ++testNumber
                    << ": [linLog] No Errors Expected";
          REQUIRE( f2(xit[-1]) ==
                   Approx( math::interpolate::linLog(xit[-1],
                                                     xit[-1], xit[0],
                                                     f2(xit[-1]), f2(xit[0]))));
          REQUIRE( f2(xit[0]) ==
                   Approx( math::interpolate::linLog(xit[0],
                                                     xit[-1], xit[0],
                                                     f2(xit[-1]), f2(xit[0]))));
          REQUIRE( f2((xit[-1] + xit[0]) * 0.5) ==
                   Approx( math::interpolate::linLog((xit[-1] + xit[0]) * 0.5,
                                                     xit[-1], xit[0],
                                                     f2(xit[-1]), f2(xit[0]))));
        }
      }
    }
  }
}
