#define CATCH_CONFIG_RUNNER

#include <cmath>
#include <functional>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTableIntegral.hpp"

namespace {

template<typename T>

T clone(const T& t){return t;}

auto F = []( const double x ){ return x < 5 ? pow(x, 2.0) : x + 20.0; };
auto F_ = []( const double x ){
  return
  x < 5 ?
  pow(x, 3.0) / 3.0 :
  0.5 * pow(x, 2.0) + 20.0 * x - 70.8 - 1.0/30.0;
};

}

int testNumber = 0;

std::vector<double> x00 = {1.0, 2.0, 3.0, 4.0, 5.0};
std::vector<double> x01 = {5.0, 6.0, 7.0, 8.0, 9.0};

std::vector<double> dy00
{ F(x00[0]), F(x00[1]), F(x00[2]), F(x00[3]), F(x00[4]) };
std::vector<double> dy01
{ F(x01[0]), F(x01[1]), F(x01[2]), F(x01[3]), F(x01[4]) };

std::vector<double> y00
{ F_(x00[0]), F_(x00[1]), F_(x00[2]), F_(x00[3]), F_(x00[4]) };
std::vector<double> y01
{ F_(x01[0]), F_(x01[1]), F_(x01[2]), F_(x01[3]), F_(x01[4]) };
            
std::function< double(double) > f = F;
std::function< double(double) > f_ = F_;

std::unique_ptr< math::implementation::CompositeInterpolationTableIntegral > cit;

int main( int argc, const char* argv[] ){

  std::vector< std::unique_ptr< math::API::InterpolationTableIntegral > > irv;

  auto t0 =
    math::implementation::DataOwningInterpolationTable
    < math::interpolate::logLog >
    ( clone(x00), clone(dy00), false );
  
  irv.push_back( t0.integral( 1.0 / 3.0 ) );

 auto t1 =
   math::implementation::DataOwningInterpolationTable
   < math::interpolate::linLin >
   ( clone(x01), clone(dy01), false );
 
  irv.push_back( t1.integral( 41.66666666667 ) );

  cit = std::make_unique
        < math::implementation::CompositeInterpolationTableIntegral >
        ( std::move(irv) );
  
  LOG(INFO) << "";
  LOG(INFO) << "CompositeInterpolationTableIntegral Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "CompositeInterpolationTableIntegral Tests Complete!";
  return result;
}
