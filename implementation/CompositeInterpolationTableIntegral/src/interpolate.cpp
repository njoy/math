#include "math/implementation/CompositeInterpolationTableIntegral.hpp"

double
math::implementation::CompositeInterpolationTableIntegral::interpolate
( const double x ) const {
  const auto it =
    std::lower_bound
    ( this->subtableBoundaries.begin(), this->subtableBoundaries.end(), x );
  if (it == this->subtableBoundaries.end() ){
    LOG(ERROR) <<
      "Queried independent value outside the bounds of the interpolation region";
    LOG(INFO) << "Queried value: " << x;
    LOG(INFO) << "Interpolation range upper boundary: " <<
      this->subtables.back()->xMax();
    throw std::exception();
  }
  const auto& subtable =
    this->subtables[it - this->subtableBoundaries.begin()];
  return subtable->interpolate(x);
}
