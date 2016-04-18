#include <vector>

#include "catch.hpp"

#include "math/API/InterpolationTableIntegral.hpp"
#include "math/implementation.hpp"

namespace mi = math::implementation; 

extern int testNumber;
extern std::vector<double> x;
extern std::vector<double> Y;
extern std::function<double(double)> F;
extern math::implementation::InterpolationTable
< math::interpolate::linLin, mi::TransferPolicy, std::vector<double> >
ownedTable;

SCENARIO("The interpolation table's integral functions correctly",
         "[math], [InterpolationTable], [integral]"){
  GIVEN("An InterpolationTable and "
        "the vector of independent variable values used in its construction"){
    WHEN("queried for the integral grid"){
      THEN("the returned value will return be equal to the vector"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integral] No Errors Expected";
        auto gridPointer = ownedTable.integral(0);
        auto& grid = *gridPointer;
        for (auto xVal : x){
          REQUIRE( F(xVal) == grid.interpolate(xVal) );
          REQUIRE( F(xVal) == grid(xVal) );
        }
      }
    }
  }
}
