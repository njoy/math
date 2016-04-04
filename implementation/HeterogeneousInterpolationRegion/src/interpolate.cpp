#include "math/implementation/HeterogeneousInterpolationRegion.hpp"

double
math::implementation::HeterogeneousInterpolationRegion::interpolate
( const double x ) const {
  auto it = std::lower_bound(this->subregionUpperBounds.begin(),
                             this->subregionUpperBounds.end(),
                             x);
  if (it == this->subregionUpperBounds.end() ){
    LOG(ERROR) <<
      "Queried independent value outside the bounds of the  interpolation region";
    LOG(INFO) << "Queried value: " << x;
    LOG(INFO) << "Interpolation range upper boundary: " <<
      this->subregions.back()->xMax();
    throw std::exception();
  }
  const auto& subregion =
    this->subregions[it - this->subregionUpperBounds.begin()];
  return subregion->interpolate(x);
}
