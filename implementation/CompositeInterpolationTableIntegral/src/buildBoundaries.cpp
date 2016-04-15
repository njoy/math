#include "math/implementation/CompositeInterpolationTableIntegral.hpp"

std::vector<double>
math::implementation::CompositeInterpolationTableIntegral::buildBoundaries
( const std::vector
  < std::unique_ptr<math::API::InterpolationTableIntegral> >& subregions ){
  
  std::vector<double> bounds;
  bounds.reserve( subregions.size() );
  for (const auto& subregionPtr : subregions ){
    bounds.push_back(subregionPtr->xMax());
  }
  return bounds;
}
