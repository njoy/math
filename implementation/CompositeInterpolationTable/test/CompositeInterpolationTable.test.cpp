#define CATCH_CONFIG_RUNNER

#include <cmath>
#include <functional>

#include "catch.hpp"

#include "math/implementation/CompositeInterpolationTable.hpp"

namespace {

template<typename T>
T clone(const T t){return t;}

auto F = []( const double x ){ return x < 5 ? pow(x, 2.0) : x + 20.0; };

}

int testNumber = 0;

std::vector<double> x00 = {1.0, 2.0, 3.0, 4.0, 5.0};
std::vector<double> x01 = {5.0, 6.0, 7.0, 8.0, 9.0};

std::vector<double> y00{ F(x00[0]), F(x00[1]), F(x00[2]), F(x00[3]), F(x00[4]) };
std::vector<double> y01{ F(x01[0]), F(x01[1]), F(x01[2]), F(x01[3]), F(x01[4]) };
            
std::function< double(double) > f = F;

std::vector
< std::unique_ptr< math::API::InterpolationTableIntegral > > referenceIntegrals;

std::unique_ptr< math::implementation::CompositeInterpolationTable > cit;

int main( int argc, const char* argv[] ){

  std::vector< std::unique_ptr< math::API::InterpolationTable > > irv;

  double boundaryCondition = 0;
  
  irv.push_back( std::make_unique
                 < math::implementation::DataReferencingInterpolationTable
                 < std::vector<double>::iterator, math::interpolate::logLog > >
                 ( x00.begin(), x00.end(), y00.begin(), y00.end(), false ) );

  auto temp = irv.back()->integral(boundaryCondition);
  referenceIntegrals.push_back( std::move(temp) );
  boundaryCondition =
    referenceIntegrals.back()->interpolate( referenceIntegrals.back()->xMax() ); 
        
  irv.push_back( std::make_unique
                 < math::implementation::DataReferencingInterpolationTable
                 < std::vector<double>::iterator, math::interpolate::linLin > >
                 ( x01.begin(), x01.end(), y01.begin(), y01.end(), false )  );

  temp = irv.back()->integral(boundaryCondition);
  referenceIntegrals.push_back( std::move(temp) );
  boundaryCondition =
    referenceIntegrals.back()->interpolate( referenceIntegrals.back()->xMax() );
  
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

SCENARIO("Gaps in the x-grid will cause the ctor to throw"){
  GIVEN("An overlapping pair of x-grids"){
    std::vector<double> x010 = {4.0, 5.0, 6.0, 7.0, 8.0};
    std::vector< std::unique_ptr< math::API::InterpolationTable > > irv0;
    
    double boundaryCondition = 0;
    
    irv0.push_back( std::make_unique
                   < math::implementation::DataReferencingInterpolationTable
                   < std::vector<double>::iterator, math::interpolate::logLog > >
                   ( x00.begin(), x00.end(), y00.begin(), y00.end(), false ) );
    
    auto temp = irv0.back()->integral(boundaryCondition);
    boundaryCondition = temp->interpolate( temp->xMax() ); 
    
    irv0.push_back( std::make_unique
                   < math::implementation::DataReferencingInterpolationTable
                   < std::vector<double>::iterator, math::interpolate::linLin > >
                   ( x010.begin(), x010.end(), y01.begin(), y01.end(), false ) );
    
    temp = irv0.back()->integral(boundaryCondition);
    boundaryCondition = temp->interpolate( temp->xMax() ); 
    WHEN("used to construct a composite interpolation table"){
      THEN("the ctor will throw"){
        REQUIRE_THROWS( math::implementation::CompositeInterpolationTable( std::move(irv0) ) );
      }
    }
  }

  GIVEN("An pair of x-grids with a gap"){
    std::vector<double> x011 = {6.0, 7.0, 8.0, 9.0, 10.0};

    std::vector< std::unique_ptr< math::API::InterpolationTable > > irv1;
    
    double boundaryCondition = 0;

    irv1.push_back( std::make_unique
                    < math::implementation::DataReferencingInterpolationTable
                    < std::vector<double>::iterator, math::interpolate::logLog > >
                    ( x011.begin(), x011.end(), y00.begin(), y00.end(), false ) );

    
    auto temp = irv1.back()->integral(boundaryCondition);
    boundaryCondition = temp->interpolate( temp->xMax() ); 
    irv1.push_back( std::make_unique
                   < math::implementation::DataReferencingInterpolationTable
                   < std::vector<double>::iterator, math::interpolate::linLin > >
                   ( x011.begin(), x011.end(), y01.begin(), y01.end(), false ) );
    
    temp = irv1.back()->integral(boundaryCondition);
    boundaryCondition = temp->interpolate( temp->xMax() ); 
    WHEN("used to construct a composite interpolation table"){
      THEN("the ctor will throw"){
        REQUIRE_THROWS( math::implementation::CompositeInterpolationTable( std::move(irv1) ) );
      }
    }
  }
}
