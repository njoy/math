#include <vector>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTableIntegral.hpp"

extern int testNumber;
extern std::vector<double> x00;
extern std::vector<double> x01;
extern std::vector<double> y00;
extern std::vector<double> y11;
extern std::function<double(double)> f_;
extern std::unique_ptr
< math::implementation::CompositeInterpolationTableIntegral > cit;

SCENARIO("The composite interpolation table integral's interpolate functions correctly",
         "[math], [CompositeInterpolationTableIntegral], [interpolate]"){
  GIVEN("An CompositeInterpolationTableIntegral and "
        "the vectors of the independent variable and "
        "dependent variable values used in its construction"){    
    WHEN("when interpolation is requested within the dependent variable range"){
      THEN("the returned value will match the generating function "){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [interpolate] No Errors Expected";
        for (auto xVal : x00){
          REQUIRE(f_(xVal) == Approx(cit->interpolate(xVal)));
        }
        for (auto xVal : x01){
          REQUIRE(f_(xVal) == Approx(cit->interpolate(xVal)));
        }
      }
    }
  }
}
