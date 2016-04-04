#include <deque>
#include <string>

#include "catch.hpp"

#include "math/interpolate.hpp"

extern int testNumber;

SCENARIO("The logarithmic interpolation function will return a correct result",
         "[math], [interpolate], [logLog]"){
  GIVEN("Some simple logarithmic interpolation problems"){
    WHEN("computed using the logLog function"){
      THEN("the correct value will be returned"){
        std::vector< std::function<double(double)> > functions =
          { [](double x){return 10.0*x;},
            [](double x){return 10.0*pow(x,2);},
            [](double x){return 5.0*pow(x,2);},
            [](double x){return 5.0*pow(x,-1.0);},
            [](double x){return 5.0*pow(x,-2.0);}
          };
        for (auto& f : functions){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [logLog] No Errors Expected";
          REQUIRE(f(1.0) ==
                  Approx( math::interpolate::logLog(1.0,
                                                    1.0, 3.0,
                                                    f(1.0), f(3.0)) ));
          REQUIRE(f(2.0) ==
                  Approx( math::interpolate::logLog(2.0,
                                                    1.0, 3.0,
                                                    f(1.0), f(3.0)) ));
          REQUIRE(f(3.0) ==
                  Approx( math::interpolate::logLog(3.0,
                                                    1.0, 3.0,
                                                    f(1.0), f(3.0)) ));
        }
      }
    }
  }
  GIVEN("a boundary that is less than zero"){
    WHEN("passed to logarithmic interpolation"){
      THEN("the routine falls back to linear interpolation"){
        auto f = [](const double x){return x;};
        REQUIRE(f(0) == Approx( math::interpolate::logLog(0.0,
                                                          -1.0, 1.0,
                                                          f(-1.0), f(1.0)) ));
      }
    }
  }
}
