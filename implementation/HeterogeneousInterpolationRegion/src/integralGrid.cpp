/*
#include "math/implementation/HeterogeneousInterpolationRegion.hpp"

std::vector< std::vector<double> >
math::implementation::HeterogeneousInterpolationRegion::integralGrid() const {
  std::vector< std::vector<double> > grid;
  grid.reserve(this->subregions.size());
  for (auto& subregionPtr : this->subregions){
    auto subGrid = subregionPtr->integralGrid();
    for (auto& subGridComponent : subGrid){
      grid.push_back( std::move(subGridComponent) );
    }
  }
  return grid;
}

*/
