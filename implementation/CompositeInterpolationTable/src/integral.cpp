#include "math/implementation/CompositeInterpolationTable.hpp"

math::implementation::CompositeInterpolationTableIntegral
math::implementation::CompositeInterpolationTable::integral_
( const double y0 ) const {
  std::vector< std::unique_ptr< math::API::InterpolationTableIntegral > > grid;
  grid.reserve( this->subtables.size() );
  auto boundaryCondition = y0;
  for (auto& subtablePointer : this->subtables ){
    grid.push_back( subtablePointer->integral( boundaryCondition ) );
    auto& tail = *(grid.back());
    boundaryCondition = tail( tail.xMax() );
  }
  return math::implementation::CompositeInterpolationTableIntegral
    ( std::move(grid) );
}
