#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTable.hpp"

extern int testNumber;

extern std::unique_ptr<math::implementation::CompositeInterpolationTable> cit;

extern std::vector
< std::unique_ptr< math::API::InterpolationTableIntegral > > referenceIntegrals;

SCENARIO("The composite interpolation table's integral functions correctly",
         "[math], [CompositeInterpolationTable], [integral]"){
  GIVEN("An CompositeInterpolationTable and "
        "the vector of integral tables generated from it's components"){    
    WHEN("queried for their xGrid and yGrids"){
      THEN("the stored values will be equal"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integral] No Errors Expected";
        auto integralTable = cit->integral(0);
        auto xGrids = integralTable->xGrid();
        auto xGrid = xGrids.begin();
        auto yGrids = integralTable->yGrid();
        auto yGrid = yGrids.begin();
        for (auto& referenceIntegral : referenceIntegrals){
          auto refXGrids = referenceIntegral->xGrid();
          auto& refXGrid = refXGrids[0];
          REQUIRE(true == std::equal(refXGrid.begin(), refXGrid.end(),
                                     xGrid->begin(), xGrid->end()));
          auto refYGrids = referenceIntegral->yGrid();
          auto& refYGrid = refYGrids[0];
          REQUIRE(true == std::equal(refYGrid.begin(), refYGrid.end(),
                                     yGrid->begin(), yGrid->end()));
          ++xGrid;
          ++yGrid;
        }
      }
    }
  }
}
