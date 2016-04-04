#define CATCH_CONFIG_RUNNER

#include <functional>

#include "catch.hpp"

#include "math/implementation/IteratorInterpolationRegion.hpp"

int testNumber = 0;
std::vector<double> x {0, 1.0, 2.0, 3.0, 4.0};
std::function<double(double)> f = [](const double x){return 5.0 + 2.0 * x;};
std::function<double(double)> F =
  [](const double x){return 5.0 * x + pow(x, 2);};
std::vector<double> y {f(x[0]), f(x[1]), f(x[2]), f(x[3]), f(x[4])};
std::vector<double> Y {F(x[0]), F(x[1]), F(x[2]), F(x[3]), F(x[4])};

math::implementation::IteratorInterpolationRegion
<std::vector<double>::iterator, math::interpolate::linLin>
liir(x.begin(), x.end(), y.begin(), y.end(), false);

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "IteratorInterpolationRegion Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "IteratorInterpolationRegion Tests Complete!";
  return result;
}

SCENARIO("The ctor will throw for invalid grids",
         "[math], [IteratorInterpolationRegion], [ctor]"){
  typedef math::implementation::IteratorInterpolationRegion
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
