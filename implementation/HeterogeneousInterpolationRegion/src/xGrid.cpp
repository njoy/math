#include "math/implementation/HeterogeneousInterpolationRegion.hpp"

std::vector< utility::View<const double> >
math::implementation::HeterogeneousInterpolationRegion::xGrid() const {
  std::vector< utility::View<const double> > grid;
  grid.reserve(this->subregions.size());
  for (auto& subregionPtr : this->subregions){
    const math::API::InterpolationRegion* ptr = subregionPtr.get(); 
    std::vector< utility::View<const double> > subGrid = ptr->xGrid();
    grid.insert(grid.end(), subGrid.begin(), subGrid.end() );
  }
  return grid;
}

std::vector< utility::View<double> >
math::implementation::HeterogeneousInterpolationRegion::xGrid() {
  std::vector< utility::View< double> > grid;
  grid.reserve(this->subregions.size());
  for (auto& subregionPtr : this->subregions){
    auto subGrid = subregionPtr->xGrid();
    grid.insert(grid.end(), subGrid.begin(), subGrid.end() );
  }
  return grid;
}
