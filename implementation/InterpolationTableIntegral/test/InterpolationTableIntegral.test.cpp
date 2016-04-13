#define CATCH_CONFIG_RUNNER

#include <functional>

#include "catch.hpp"

#include "math/implementation/InterpolationTableIntegral.hpp"

int testNumber = 0;

std::vector<double> x  = {0.0, 1.0, 2.0, 3.0, 4.0};
std::vector<double> y  = {5.0, 7.0, 9.0, 11.0, 13.0};
std::vector<double> Y  = {0.0, 6.0, 14.0, 24.0, 36.0};


math::implementation::InterpolationTableIntegral
 < std::vector<double>::iterator, math::interpolate::linLin >
iti(x.begin(), x.end(), y.begin(), y.end(), 0, false);

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "InterpolationTableIntegral Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "InterpolationTableIntegral Tests Complete!";
  return result;
}

SCENARIO("The ctor will throw for invalid grids",
         "[math], [InterpolationTableIntegral], [ctor]"){
  using interpRegion =
    math::implementation::InterpolationTableIntegral
    <std::vector<double>::iterator, math::interpolate::linLin>;
  GIVEN("grids with mismatched lengths"){
    std::vector<double> x0 = { 1.0, 2.0, 3.0 };
    std::vector<double> y0 = { 1.0, 2.0, 3.0, 4.0 };
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( interpRegion
                        (x0.begin(), x0.end(), y0.begin(), y0.end(), 0, false) );
      }
    }
  }
  
  GIVEN("an out of order x grid"){
    std::vector<double> x0 = { 1.0, 3.0, 2.0 };
    std::vector<double> y0 = { 1.0, 2.0, 3.0 };
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber << ": [ctor] Errors Expected";
        REQUIRE_THROWS( interpRegion
                        (x0.begin(), x0.end(), y0.begin(), y0.end(), 0, false) );
      }
    }
  }
}
