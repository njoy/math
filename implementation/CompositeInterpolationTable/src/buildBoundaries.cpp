#include "math/implementation/CompositeInterpolationTable.hpp"

std::vector<double>
math::implementation::CompositeInterpolationTable::buildBoundaries
( const std::vector
  < std::unique_ptr<math::API::InterpolationTable> >& subregions ){
  
  std::vector<double> bounds;
  bounds.reserve( subregions.size() );
  for (const auto& subregionPtr : subregions ){
    bounds.push_back(subregionPtr->xMax());
  }
  return bounds;
}
