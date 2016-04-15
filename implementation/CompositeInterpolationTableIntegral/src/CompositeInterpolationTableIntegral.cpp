#include "math/implementation/CompositeInterpolationTableIntegral.hpp"

using namespace math::implementation;

CompositeInterpolationTableIntegral::CompositeInterpolationTableIntegral
( std::vector< std::unique_ptr<math::API::InterpolationTableIntegral> >&& subtables,
  const double boundaryTolerance ) :
  subtables( std::move(subtables) ),
  subtableBoundaries
  ( CompositeInterpolationTableIntegral::buildBoundaries(this->subtables) ){

  auto hasGap =
    [boundaryTolerance]
    ( const std::unique_ptr< math::API::InterpolationTableIntegral >& lhs,
      const std::unique_ptr< math::API::InterpolationTableIntegral >& rhs ){
    const double boundaryError =
    std::abs(lhs->xMax() - rhs->xMin())/lhs->xMax();
    return (boundaryTolerance < boundaryError); };
  
  const auto subtableIterator =
    std::adjacent_find( this->subtables.begin(), this->subtables.end(), hasGap );
  
  if ( subtableIterator != this->subtables.end() ){
    LOG(ERROR) << "Region boundary error exceeded tolerance";
    LOG(INFO) << "Relative error tolerance: " << boundaryTolerance;
    LOG(INFO) << "Left-hand region upper limit: "
              << (subtableIterator[0])->xMax();
    LOG(INFO) << "Right-hand region lower limit: "
              << (subtableIterator[1])->xMin();
    LOG(INFO) << "Error relative to right-hand region lower limit: " <<
      std::abs((subtableIterator[0])->xMax() - (subtableIterator[1])->xMin()) /
      (subtableIterator[1])->xMin();
    LOG(INFO) << "Error constructing composite interpolation table integral";
    throw std::exception();
  }
}
