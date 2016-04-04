#include "math/interpolate.hpp"

namespace {

/**
 * @brief
 * Determines whether correction to boundary derivative values is necessary
 *
 * @param alpha 
 * the ratio of the derivative at the left boundary to the average derivative 
 * over the interval
 * @param beta
 * the ratio of the derivative at the right boundary to the average derivative 
 * over the interval
 *
 * @result A boolean specifying whether, with the provided parameters, a cubic 
 * hermite interpolant will be monotonic
 */
bool
requiresCorrection(const double alpha, const double beta){
  const bool withinInnerSquare = not (alpha > 3 or beta > 3);
  if (withinInnerSquare) return false;
  const double phi = /* parameter name taken from F-C algorithm paper */
    alpha - std::pow(2*alpha + beta - 3.0, 2)/(3.0*(alpha + beta - 2.0));
  const bool withinElipse = ( phi >= 0);
  return not withinElipse;
}

/**
 * @brief
 * Applies a correction factor to boundary derivative values to render the 
 * cubic interpolant monotonic
 *
 * @param alpha 
 * the ratio of the derivative at the left boundary to the average derivative 
 * over the interval
 * @param beta
 * the ratio of the derivative at the right boundary to the average derivative 
 * over the interval
 */
void
correctParameters(double& alpha, double& beta){
  /* Given arbitrary precision, correctionFactor1 would perform the minimum
   * derivative adjustment necessary (assuming equal scaling on alpha and beta)
   * to render a phi parameter value of zero
   */ 
  const double correctionFactor1 =
    3.0 * ( alpha + beta + sqrt( alpha*beta) ) /
    (pow(alpha, 2) + alpha * beta + pow(beta, 2));
  
  /* correctionFactor2 is more conservative. Rather than aim for the outer 
   * boundary, this correction factor adjusts alpha and beta to line along the
   * perimeter of the largest square that can be bounded by the alpha and beta
   * axes alpha + beta < 3 and within the phi elipse for alpha + beta > 3. This
   * correction is conservative but more pronounced impact on the resulting curve
   */ 
  const double correctionFactor2 =
    2.99999 / std::max(std::abs(alpha), std::abs(beta));

  /* In order to preserve as much of the original behavior as possible, the first
   * correction is given much more weight than the second. The second serves to 
   * provide numerical stability
   */
  constexpr double factor1Weight = 0.9999;
  constexpr double factor2Weight = 0.0001;
  const double correctionFactor =
    factor1Weight * correctionFactor1 + factor2Weight * correctionFactor2; 
  alpha *= correctionFactor;
  beta *= correctionFactor;
}

}

/**
 * @param x 
 * the independent variable value at which to calculate the function value
 * @param x1
 * the left independent variable value with known function value
 * @param x2
 * the right independent variable value with known function value
 * @param y1
 * the left known function value
 * @param y2
 * the right known function value
 * @param dy1
 * the left known function derivative value
 * @param dy2
 * the right known function derivative value
 * @details
 * This function computes an interpolation between two reference value using a 
 * modified hermite cubic spline. Interpolation coefficients are computed using 
 * the Fritsch-Carlson algorithm. This algorithm ensures that the monotonicity of
 * the data is preserved (which makes it ideal for providing smooth evaluations 
 * of cumulative probability functions).\n
 * \n
 * In this implementation of the algorithm, first-order continuity is not 
 * preserved. By relaxing this requirement, the minimum necessary modification to
 * the first derivative value may be made for each interval without requiring 
 * non-local information or resorting to multiple passes over the data. This 
 * provides a more accurate interpolant of the data.\n
 * \n
 * For details about the algorithm, please see the original article, available
 * at:
 * http://epubs.siam.org/doi/pdf/10.1137/0717021
 * \n
 * For the purposes of this routine, several assumptions are made:
 * 1. the data is known to be monotonic
 * 2. the alpha and beta parameters ought to be modified uniformly.
 */
double
math::interpolate::monotoneCubicSpline
( const double x,
  // assumed x1 <= x <= x2 and x1 < x2
  const double x1,  const double x2,
  const double y1,  const double y2,
  const double dy1, const double dy2 ){  
  const double changeInY = y2 - y1;
  if ( std::abs(changeInY) < 1E-14 ){ return y1; }
  const double changeInX = x2 - x1;
  const double inverseChangeInX = 1.0/changeInX;
  const double averageSlope = changeInY * inverseChangeInX;
  const double inverseAverageSlope = 1.0/averageSlope;
  double alpha = dy1 * inverseAverageSlope;
  double beta = dy2 * inverseAverageSlope;
  if (requiresCorrection(alpha, beta)){
    correctParameters(alpha, beta);
  }
  const double dx = x - x1;
  return averageSlope * std::pow(inverseChangeInX,2) * (
    (alpha + beta - 2) * std::pow(dx,3) -
    (2.0 * alpha + beta - 3) * changeInX * std::pow(dx,2) +
    alpha * std::pow(changeInX,2) * dx) + y1;

}

