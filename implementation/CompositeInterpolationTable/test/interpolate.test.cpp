#include <vector>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTable.hpp"

extern int testNumber;
extern std::vector<double> x00;
extern std::vector<double> x01;
extern std::vector<double> y00;
extern std::vector<double> y11;
extern std::function<double(double)> f;
extern std::unique_ptr<math::implementation::CompositeInterpolationTable> cit;

SCENARIO("The composite interpolation table's interpolate functions correctly",
         "[math], [CompositeInterpolationTable], [interpolate]"){
  GIVEN("An CompositeInterpolationTable and "
        "the vectors of the independent variable and "
        "dependent variable values used in its construction"){    
    WHEN("when interpolation is requested within the dependent variable range"){
      THEN("the returned value will match the generating function "){
        LOG(INFO) << "Test " << ++testNumber << ": [interpolate] No Errors Expected";
        for (auto xVal : x00){
          REQUIRE(f(xVal) == Approx(cit->interpolate(xVal)));
        }
        for (auto xVal : x01){
          REQUIRE(f(xVal) == Approx(cit->interpolate(xVal)));
        }
        LOG(INFO) << "Test " << ++testNumber
                  << ": [interpolate] No Errors Expected";
        double xVal;
        for ( auto it = x00.begin() + 1, end = x00.end(); it != end; ++it ){
          xVal = 0.5 * ( it[0] + it[-1] );
          REQUIRE( f(xVal) == Approx(cit->interpolate(xVal)) );
        }
        for ( auto it = x01.begin() + 1, end = x01.end(); it != end; ++it ){
          xVal = 0.5 * ( it[0] + it[-1] );
          REQUIRE( f(xVal) == Approx(cit->interpolate(xVal)) );
        }
        REQUIRE_THROWS( cit->interpolate(10) );
      }
    }
  }
}
