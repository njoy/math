#include "math/implementation/HeterogeneousInterpolationRegion.hpp"

std::vector< utility::View<const double> >
math::implementation::HeterogeneousInterpolationRegion::yGrid() const {
  std::vector< utility::View<const double> > grid;
  grid.reserve(this->subregions.size());
  for (const auto& subregionPtr : this->subregions){
    const math::API::InterpolationRegion* ptr = subregionPtr.get(); 
    std::vector<  utility::View<const double> > subGrid = ptr->yGrid();
    grid.insert(grid.end(), subGrid.begin(), subGrid.end() );
  }
  return grid;
}

std::vector< utility::View< double> >
math::implementation::HeterogeneousInterpolationRegion::yGrid() {
  std::vector< utility::View< double> > grid;
  grid.reserve(this->subregions.size());
  for  (auto& subregionPtr : this->subregions){
    auto subGrid = subregionPtr->yGrid();
    grid.insert(grid.end(), subGrid.begin(), subGrid.end() );
  }
  return grid;
}
