#include <numeric>

#include "math/implementation/SplicedProbabilityDistribution.hpp"

namespace mi = math::implementation;

mi::SplicedProbabilityDistribution::SplicedProbabilityDistribution
( const math::API::ProbabilityDistribution& pd0,
  const math::API::ProbabilityDistribution& pd1,
  const std::array<double, 2>& pdfWeights,
  const std::array<double, 2>& cdfWeights ) :
  pd0(pd0),
  pd1(pd1),
  pdfWeights(pdfWeights),
  cdfWeights(cdfWeights) {
  if ( std::abs(1.0 - std::accumulate(this->pdfWeights.begin(),
                                      this->pdfWeights.end(),
                                      0.0) ) > 1E-7 ){
    LOG(ERROR) <<
      "Weights of component probability density functions do not sum to unity";
    LOG(INFO) << "Error while constructing spliced probability distribution";
    throw std::exception();
  }
  if ( std::abs(1.0 - std::accumulate(this->cdfWeights.begin(),
                                      this->cdfWeights.end(),
                                      0.0) ) > 1E-7 ){
    LOG(ERROR) <<
      "Weights of component cumulative probability functions do not sum to unity";
    LOG(INFO) << "Error while constructing spliced probability distribution";
    throw std::exception();
  }
}
