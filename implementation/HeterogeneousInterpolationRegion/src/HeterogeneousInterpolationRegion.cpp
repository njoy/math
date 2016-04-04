#include "math/implementation/HeterogeneousInterpolationRegion.hpp"

math::implementation::HeterogeneousInterpolationRegion::HeterogeneousInterpolationRegion
( std::vector< std::unique_ptr<math::API::InterpolationRegion> >&& subregions,
  const double boundaryTolerance ) :
  subregions(std::move(subregions)),
  subregionUpperBounds(math::implementation::HeterogeneousInterpolationRegion::buildBoundaries(this->subregions)){
  const auto it =
    std::adjacent_find( this->subregions.begin(),
                        this->subregions.end(),
                        [boundaryTolerance](
                          const std::unique_ptr<math::API::InterpolationRegion>& lhs,
                          const std::unique_ptr<math::API::InterpolationRegion>& rhs){
                          const double boundaryError =
                          std::abs(lhs->xMax() - rhs->xMin())/lhs->xMax();
                          return (boundaryTolerance < boundaryError);});
  if (it != this->subregions.end()){
    LOG(ERROR) << "Region boundary error exceeded tolerance";
    LOG(INFO) << "Relative error tolerance: " << boundaryTolerance;
    LOG(INFO) << "Left-hand region upper limit: " << (it[0])->xMax();
    LOG(INFO) << "Right-hand region lower limit: " << (it[1])->xMin();
    LOG(INFO) << "Error relative to right-hand region lower limit: " <<
      std::abs((it[0])->xMax() - (it[1])->xMin())/(it[1])->xMin();
    throw std::exception();
  }    
}
