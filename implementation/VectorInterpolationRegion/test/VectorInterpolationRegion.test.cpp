#define CATCH_CONFIG_RUNNER

#include <functional>

#include "catch.hpp"

#include "math/implementation/VectorInterpolationRegion.hpp"

int testNumber = 0;
std::vector<double> x {0, 1.0, 2.0, 3.0, 4.0};
std::vector<double> xClone = x;
std::function<double(double)> f = [](const double x){return 5.0 + 2.0 * x;};
std::vector<double> y {f(x[0]), f(x[1]), f(x[2]), f(x[3]), f(x[4])};
std::vector<double> yClone = y;

math::implementation::VectorInterpolationRegion<math::interpolate::linLin>
lvir(std::move(xClone), std::move(yClone), false);

int main( int argc, char* const argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "VectorInterpolationRegion Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "VectorInterpolationRegion Tests Complete!";
  return result;
}
