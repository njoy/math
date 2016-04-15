#include <iterator>

#include "math/implementation/CompositeInterpolationTableIntegral.hpp"

std::vector< utility::View<const double> >
math::implementation::CompositeInterpolationTableIntegral::yGrid() const {
  std::vector< utility::View<const double> > grid;
  grid.reserve( this->subtables.size() );
  for ( auto& subtablePointer : this->subtables ){
    const auto& subtable = *subtablePointer; 
    auto subgrid = subtable.yGrid();
    auto moveIt = std::make_move_iterator( subgrid.begin() );
    auto moveEnd = std::make_move_iterator( subgrid.end() );
    grid.insert( grid.end(), moveIt, moveEnd );
  }
  return grid;
}

std::vector< utility::View< double> >
math::implementation::CompositeInterpolationTableIntegral::yGrid() {
  std::vector< utility::View< double> > grid;
  grid.reserve( this->subtables.size() );
  for ( auto& subtablePointer : this->subtables){
    auto subgrid = subtablePointer->yGrid();
    auto moveIt = std::make_move_iterator( subgrid.begin() );
    auto moveEnd = std::make_move_iterator( subgrid.end() );
    grid.insert( grid.end(), moveIt, moveEnd );
  }
  return grid;
}
