#define CATCH_CONFIG_RUNNER

#include <cmath>
#include <functional>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTable.hpp"

namespace {

template<typename T>

T clone(const T& t){return t;}

auto F = []( const double x ){ return x < 5 ? pow(x, 2.0) : x + 20.0; };

}

int testNumber = 0;

std::vector<double> x00 = {1.0, 2.0, 3.0, 4.0, 5.0};
std::vector<double> x01 = {5.0, 6.0, 7.0, 8.0, 9.0};

std::vector<double> y00{ F(x00[0]), F(x00[1]), F(x00[2]), F(x00[3]), F(x00[4]) };
std::vector<double> y01{ F(x01[0]), F(x01[1]), F(x01[2]), F(x01[3]), F(x01[4]) };
            
std::function< double(double) > f = F;

std::unique_ptr< math::implementation::CompositeInterpolationTable > cit;

int main( int argc, const char* argv[] ){

  std::vector< std::unique_ptr< math::API::InterpolationTable > > irv;
  
  irv.push_back( std::make_unique
                 < math::implementation::DataOwningInterpolationTable
                 < math::interpolate::logLog > >
                 ( clone(x00), clone(y00), false ) );
    
  irv.push_back( std::make_unique
                 < math::implementation::DataOwningInterpolationTable
                  < math::interpolate::linLin > >
                 ( clone(x01), clone(y01), false )  );

  cit = std::make_unique
        < math::implementation::CompositeInterpolationTable >
        ( std::move(irv) );
  
  LOG(INFO) << "";
  LOG(INFO) << "CompositeInterpolationTable Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "CompositeInterpolationTable Tests Complete!";
  return result;
}
