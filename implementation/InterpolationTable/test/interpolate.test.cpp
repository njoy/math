#include <vector>

#include "catch.hpp"

#include "math/implementation.hpp"

extern int testNumber;
extern std::vector<double> x;
extern std::function<double(double)> f;
extern math::implementation::InterpolationTable
< math::interpolate::linLin,
  math::implementation::TransferPolicy,
  std::vector<double> >
ownedTable;

SCENARIO("The interpolation table's interpolate functions correctly",
         "[math], [InterpolationTable], [interpolate]"){
  GIVEN("An InterpolationTable and "
        "the vectors of the independent variable and "
        "dependent variable values used in its construction"){    
    WHEN("when interpolation is requested within the dependent variable range"){
      THEN("the returned value will match the generating function "){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [interpolate] No Errors Expected";
        for (auto xVal : x){
          REQUIRE( f(xVal) == ownedTable.interpolate(xVal) );
          REQUIRE( f(xVal) == ownedTable(xVal) );
        }
        LOG(INFO) << "Test " << ++testNumber
                  << ": [interpolate] No Errors Expected";
        double xVal;
        for (auto it = x.begin() + 1, end = x.end();
             it != end;
             it++ ){
          xVal = 0.5 * ( it[0] + it[-1] );
          REQUIRE( f(xVal) == Approx(ownedTable.interpolate(xVal)) );
          REQUIRE( f(xVal) == Approx(ownedTable(xVal)) );
        }
      }
    }
  }
}
