#define CATCH_CONFIG_RUNNER

#include <cmath>
#include <functional>

#include "catch.hpp"

#include "math/implementation/ProbabilityDistribution.hpp"

namespace {
auto pdf = [](double x){return 0.5*x + 0.5;};
auto cdf = [](double x){return 0.25*std::pow(x,2) + 0.5 * x + 0.25;};
std::function<double(double)> PDF_ = pdf;
std::function<double(double)> CDF_ = cdf;
}

int testNumber = 0;

std::function<double(double)> PDF = pdf;
std::function<double(double)> CDF = cdf;

math::implementation::ProbabilityDistribution
< std::function<double(double)>, std::function<double(double)> >
probabilityDistribution
( std::move(PDF_), std::move(CDF_) );

int main( int argc, const char* argv[]){
  LOG(INFO) << "ProbabilityDistribution Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "ProbabilityDistribution Tests Complete!";
  return result;
}
