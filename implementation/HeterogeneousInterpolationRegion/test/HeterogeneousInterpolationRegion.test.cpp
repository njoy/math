#define CATCH_CONFIG_RUNNER

#include <cmath>
#include <functional>

#include "catch.hpp"

#include "math/implementation/HeterogeneousInterpolationRegion.hpp"

int testNumber = 0;
std::vector<double> x0 {1.0, 2.0, 3.0, 4.0, 5.0};
std::vector<double> x1 {5.0, 6.0, 7.0, 8.0, 9.0};
std::function<double(double)> f = [](const double x){
  return x < 5 ?  pow(x, 2.0) : x + 20.0;
};
std::vector<double> y0_ {f(x0[0]), f(x0[1]), f(x0[2]), f(x0[3]), f(x0[4])}; // cmath apparently uses the symbol y0 symbol

std::vector<double> y1_ {f(x1[0]), f(x1[1]), f(x1[2]), f(x1[3]), f(x1[4])};
std::unique_ptr<math::API::InterpolationRegion> hir;

int main( int argc, const char* argv[] ){
  {
    std::vector<std::unique_ptr<math::API::InterpolationRegion> >
      irv;
    std::vector<double> x0Clone = x0;
    std::vector<double> x1Clone = x1;
    std::vector<double> y0Clone = y0_;
    std::vector<double> y1Clone = y1_;
    
    std::unique_ptr<math::API::InterpolationRegion>
      ir0( new math::implementation::VectorInterpolationRegion
           <math::interpolate::logLog>(
             std::move(x0Clone), std::move(y0Clone), false) );
    
    std::unique_ptr<math::API::InterpolationRegion>
      ir1( new math::implementation::VectorInterpolationRegion
           <math::interpolate::linLin>(
             std::move(x1Clone), std::move(y1Clone), false) );

    irv.push_back(std::move(ir0));
    irv.push_back(std::move(ir1));
    hir = std::make_unique
      <math::implementation::HeterogeneousInterpolationRegion>(std::move(irv));
  }
  LOG(INFO) << "";
  LOG(INFO) << "HeterogeneousInterpolationRegion Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "HeterogeneousInterpolationRegion Tests Complete!";
  return result;
}
