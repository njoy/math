#define CATCH_CONFIG_RUNNER

#include <functional>

#include "catch.hpp"

#include "math/implementation/InterpolationRegionIntegral.hpp"

int testNumber = 0;

std::vector<double> x  = {0.0, 1.0, 2.0, 3.0, 4.0};
std::vector<double> y  = {5.0, 7.0, 9.0, 11.0, 13.0};
std::vector<double> Y  = {0.0, 6.0, 14.0, 24.0, 36.0};

std::unique_ptr
<math::implementation::InterpolationRegionIntegral
 <std::vector<double>::iterator, math::interpolate::linLin> >
liir;

int main( int argc, const char* argv[] ){
  liir = 
  std::make_unique
    <math::implementation::InterpolationRegionIntegral
     <std::vector<double>::iterator, math::interpolate::linLin> >
    (x.begin(), x.end(), y.begin(), y.end(), false);
  LOG(INFO) << "";
  LOG(INFO) << "InterpolationRegionIntegral Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "InterpolationRegionIntegral Tests Complete!";
  return result;
}

SCENARIO("The ctor will throw for invalid grids",
         "[math], [InterpolationRegionIntegral], [ctor]"){
  typedef math::implementation::InterpolationRegionIntegral
    <std::vector<double>::iterator, math::interpolate::linLin>
    interpRegion;
  GIVEN("grids with mismatched lengths"){
    std::vector<double> x0 = { 1.0, 2.0, 3.0 };
    std::vector<double> y0 = { 1.0, 2.0, 3.0, 4.0 };
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [ctor] Errors Expected";
        REQUIRE_THROWS(
          interpRegion
          (x0.begin(), x0.end(), y0.begin(), y0.end(), false));
      }
    }
  }
  
  GIVEN("an out of order x grid"){
    std::vector<double> x0 = { 1.0, 3.0, 2.0 };
    std::vector<double> y0 = { 1.0, 2.0, 3.0 };
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [ctor] Errors Expected";
        REQUIRE_THROWS(
          interpRegion
          (x0.begin(), x0.end(), y0.begin(), y0.end(), false));
      }
    }
  }
}
