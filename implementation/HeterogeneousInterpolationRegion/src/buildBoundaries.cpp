#include "math/implementation/HeterogeneousInterpolationRegion.hpp"

std::vector<double>
math::implementation::HeterogeneousInterpolationRegion::buildBoundaries(
  const std::vector< std::unique_ptr<math::API::InterpolationRegion> >& subregions ){
  std::vector<double> bounds;
  bounds.reserve(subregions.size());
  for (const auto& subregionPtr : subregions ){
    bounds.push_back(subregionPtr->xMax());
  }
  return bounds;
}
