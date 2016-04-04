#define CATCH_CONFIG_RUNNER

#include <cmath>
#include <functional>

#include "catch.hpp"

#include "math/implementation/VectorSeries.hpp"

int testNumber = 0;

/* A vector of Legendre polynomials 
 * i.e. p[0] -> P_0(x), p[1] -> P_1(x), etc */ 
std::vector< std::function< double(double) > >
p = {
  [](const double){return 1;},
  [](const double x){return x;},
  [](const double x){return 1.5 * pow(x,2) -
                     0.5;},
  [](const double x){return 2.5 * pow(x,3) -
                     1.5*x;},
  [](const double x){return 4.375 * pow(x,4) -
                     3.75 * pow(x,2) +
                     0.375;},
  [](const double x){return 7.875 * pow(x,5) -
                     8.75 * pow(x,3) +
                     1.875 * x;},
  [](const double x){return 14.4375 * pow(x,6) -
                     19.6875 * pow(x,4) +
                     6.5625 * pow(x,2) -
                     0.3125;}
};

/* A vector of Legendre polynomials integrals 
 * i.e. P[0] -> \int P_0(x) dx, P[1] -> \int P_1(x) dx, etc */ 
std::vector< std::function< double(double) > >
P = {
  [](const double x){return x;},
  [](const double x){return 0.5 * pow(x,2);},
  [](const double x){return 0.5 * (pow(x,3) - x);},
  [](const double x){return 0.5 * (1.25 * pow(x,4) -
                                   1.5*pow(x,2));},
  [](const double x){return 1.0/8.0 * (7 * pow(x,5) -
                                       10 * pow(x,3) +
                                       3* x);},
  [](const double x){return 1.0/8.0 *(10.5 * pow(x,6) -
                                      17.5 * pow(x,4) +
                                      7.5 * pow(x,2));},
  [](const double x){return 1.0/16.0 * (33 * pow(x,7) -
                                        63 * pow(x,5) +
                                        35 * pow(x,3) -
                                        5 * x);}
};

/* A vector of Legendre polynomials derivatives 
 * i.e. P[0] -> dP_0(x)/dx , P[1] -> dP_1(x)/dx, etc */ 
std::vector< std::function< double(double) > >
dp = {
  [](const double){return 0;},
  [](const double){return 1;},
  [](const double x){return 3.0 * x;},
  [](const double x){return 7.5 * pow(x,2) -
                     1.5;},
  [](const double x){return 17.5 * pow(x,3) -
                     7.5 * x;},
  [](const double x){return 39.375 * pow(x,4) -
                     26.25 * pow(x,2) +
                     1.875;},
  [](const double x){return 86.625 * pow(x,5) -
                     78.75 * pow(x,3) +
                     13.125 * x;}
};

std::vector< std::vector< double > >
coefficients = {{1.0},                                   // 1
                {0.0, 1.0},                              // 2
                {0.0, 0.0, 1.0},                         // 3
                {1.0, 0.0, 0.0, 0.0},                    // 4
                {0.0, 0.0, 0.0, 0.0},                    // 5
                {0.0, 0.0, 0.0, 1.0},                    // 6
                {0.5, 0.5, 0.5, 0.5},                    // 7
                {0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0},     // 8
                {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0},     // 9
                {10.0, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0},    // 10
                {0.5, 1.3, 1.7, 2.4, 0.77, 1.05, 4.62}}; // 11

std::vector< std::function< double(double) > > 
evalReferences = {
  [](const double x){return
                     coefficients[0][0] * p[0](x);},
  [](const double x){return
                     coefficients[1][0] * p[0](x) +
                     coefficients[1][1] * p[1](x);},
  [](const double x){return
                     coefficients[2][0] * p[0](x) +
                     coefficients[2][1] * p[1](x) +
                     coefficients[2][2] * p[2](x);},
  [](const double x){return
                     coefficients[3][0] * p[0](x) +
                     coefficients[3][1] * p[1](x) +
                     coefficients[3][2] * p[2](x) +
                     coefficients[3][3] * p[3](x);},
  [](const double x){return
                     coefficients[4][0] * p[0](x) +
                     coefficients[4][1] * p[1](x) +
                     coefficients[4][2] * p[2](x) +
                     coefficients[4][3] * p[3](x);},
  [](const double x){return
                     coefficients[5][0] * p[0](x) +
                     coefficients[5][1] * p[1](x) +
                     coefficients[5][2] * p[2](x) +
                     coefficients[5][3] * p[3](x);},
  [](const double x){return
                     coefficients[6][0] * p[0](x) +
                     coefficients[6][1] * p[1](x) +
                     coefficients[6][2] * p[2](x) +
                     coefficients[6][3] * p[3](x);},
  [](const double x){return
                     coefficients[7][0] * p[0](x) +
                     coefficients[7][1] * p[1](x) +
                     coefficients[7][2] * p[2](x) +
                     coefficients[7][3] * p[3](x) +
                     coefficients[7][4] * p[4](x) +
                     coefficients[7][5] * p[5](x) +
                     coefficients[7][6] * p[6](x);},
  [](const double x){return
                     coefficients[8][0] * p[0](x) +
                     coefficients[8][1] * p[1](x) +
                     coefficients[8][2] * p[2](x) +
                     coefficients[8][3] * p[3](x) +
                     coefficients[8][4] * p[4](x) +
                     coefficients[8][5] * p[5](x) +
                     coefficients[8][6] * p[6](x);},
  [](const double x){return
                     coefficients[9][0] * p[0](x) +
                     coefficients[9][1] * p[1](x) +
                     coefficients[9][2] * p[2](x) +
                     coefficients[9][3] * p[3](x) +
                     coefficients[9][4] * p[4](x) +
                     coefficients[9][5] * p[5](x) +
                     coefficients[9][6] * p[6](x);},
  [](const double x){return
                     coefficients[10][0] * p[0](x) +
                     coefficients[10][1] * p[1](x) +
                     coefficients[10][2] * p[2](x) +
                     coefficients[10][3] * p[3](x) +
                     coefficients[10][4] * p[4](x) +
                     coefficients[10][5] * p[5](x) +
                     coefficients[10][6] * p[6](x);}
};

std::vector< std::function< double(double) > > 
diffReferences = {
  [](const double x){return
                     coefficients[0][0] * dp[0](x);},
  [](const double x){return
                     coefficients[1][0] * dp[0](x) +
                     coefficients[1][1] * dp[1](x);},
  [](const double x){return
                     coefficients[2][0] * dp[0](x) +
                     coefficients[2][1] * dp[1](x) +
                     coefficients[2][2] * dp[2](x);},
  [](const double x){return
                     coefficients[3][0] * dp[0](x) +
                     coefficients[3][1] * dp[1](x) +
                     coefficients[3][2] * dp[2](x) +
                     coefficients[3][3] * dp[3](x);},
  [](const double x){return
                     coefficients[4][0] * dp[0](x) +
                     coefficients[4][1] * dp[1](x) +
                     coefficients[4][2] * dp[2](x) +
                     coefficients[4][3] * dp[3](x);},
  [](const double x){return
                     coefficients[5][0] * dp[0](x) +
                     coefficients[5][1] * dp[1](x) +
                     coefficients[5][2] * dp[2](x) +
                     coefficients[5][3] * dp[3](x);},
  [](const double x){return
                     coefficients[6][0] * dp[0](x) +
                     coefficients[6][1] * dp[1](x) +
                     coefficients[6][2] * dp[2](x) +
                     coefficients[6][3] * dp[3](x);},
  [](const double x){return
                     coefficients[7][0] * dp[0](x) +
                     coefficients[7][1] * dp[1](x) +
                     coefficients[7][2] * dp[2](x) +
                     coefficients[7][3] * dp[3](x) +
                     coefficients[7][4] * dp[4](x) +
                     coefficients[7][5] * dp[5](x) +
                     coefficients[7][6] * dp[6](x);},
  [](const double x){return
                     coefficients[8][0] * dp[0](x) +
                     coefficients[8][1] * dp[1](x) +
                     coefficients[8][2] * dp[2](x) +
                     coefficients[8][3] * dp[3](x) +
                     coefficients[8][4] * dp[4](x) +
                     coefficients[8][5] * dp[5](x) +
                     coefficients[8][6] * dp[6](x);},
  [](const double x){return
                     coefficients[9][0] * dp[0](x) +
                     coefficients[9][1] * dp[1](x) +
                     coefficients[9][2] * dp[2](x) +
                     coefficients[9][3] * dp[3](x) +
                     coefficients[9][4] * dp[4](x) +
                     coefficients[9][5] * dp[5](x) +
                     coefficients[9][6] * dp[6](x);},
  [](const double x){return
                     coefficients[10][0] * dp[0](x) +
                     coefficients[10][1] * dp[1](x) +
                     coefficients[10][2] * dp[2](x) +
                     coefficients[10][3] * dp[3](x) +
                     coefficients[10][4] * dp[4](x) +
                     coefficients[10][5] * dp[5](x) +
                     coefficients[10][6] * dp[6](x);}
};

std::vector< std::function< double(double) > > 
integralReferences = {
  [](const double x){return
                     coefficients[0][0] * P[0](x);},
  [](const double x){return
                     coefficients[1][0] * P[0](x) +
                     coefficients[1][1] * P[1](x);},
  [](const double x){return
                     coefficients[2][0] * P[0](x) +
                     coefficients[2][1] * P[1](x) +
                     coefficients[2][2] * P[2](x);},
  [](const double x){return
                     coefficients[3][0] * P[0](x) +
                     coefficients[3][1] * P[1](x) +
                     coefficients[3][2] * P[2](x) +
                     coefficients[3][3] * P[3](x);},
  [](const double x){return
                     coefficients[4][0] * P[0](x) +
                     coefficients[4][1] * P[1](x) +
                     coefficients[4][2] * P[2](x) +
                     coefficients[4][3] * P[3](x);},
  [](const double x){return
                     coefficients[5][0] * P[0](x) +
                     coefficients[5][1] * P[1](x) +
                     coefficients[5][2] * P[2](x) +
                     coefficients[5][3] * P[3](x);},
  [](const double x){return
                     coefficients[6][0] * P[0](x) +
                     coefficients[6][1] * P[1](x) +
                     coefficients[6][2] * P[2](x) +
                     coefficients[6][3] * P[3](x);},
  [](const double x){return
                     coefficients[7][0] * P[0](x) +
                     coefficients[7][1] * P[1](x) +
                     coefficients[7][2] * P[2](x) +
                     coefficients[7][3] * P[3](x) +
                     coefficients[7][4] * P[4](x) +
                     coefficients[7][5] * P[5](x) +
                     coefficients[7][6] * P[6](x);},
  [](const double x){return
                     coefficients[8][0] * P[0](x) +
                     coefficients[8][1] * P[1](x) +
                     coefficients[8][2] * P[2](x) +
                     coefficients[8][3] * P[3](x) +
                     coefficients[8][4] * P[4](x) +
                     coefficients[8][5] * P[5](x) +
                     coefficients[8][6] * P[6](x);},
  [](const double x){return
                     coefficients[9][0] * P[0](x) +
                     coefficients[9][1] * P[1](x) +
                     coefficients[9][2] * P[2](x) +
                     coefficients[9][3] * P[3](x) +
                     coefficients[9][4] * P[4](x) +
                     coefficients[9][5] * P[5](x) +
                     coefficients[9][6] * P[6](x);},
  [](const double x){return
                     coefficients[10][0] * P[0](x) +
                     coefficients[10][1] * P[1](x) +
                     coefficients[10][2] * P[2](x) +
                     coefficients[10][3] * P[3](x) +
                     coefficients[10][4] * P[4](x) +
                     coefficients[10][5] * P[5](x) +
                     coefficients[10][6] * P[6](x);}
};

namespace {
std::vector<double>
clone(const std::vector<double>& v) {return v;}
}

std::vector< math::implementation::VectorLegendreSeries > ils;

int main( int argc, const char* argv[] ){
  ils.reserve(11);
  ils.push_back( math::implementation::VectorLegendreSeries
                 ( clone(coefficients[0]), false ) );
  ils.push_back( math::implementation::VectorLegendreSeries
                 ( clone(coefficients[1]), false ));
  ils.push_back( math::implementation::VectorLegendreSeries
                 ( clone(coefficients[2]), false ));
  ils.push_back(  math::implementation::VectorLegendreSeries
                  ( clone(coefficients[3]), false ));
  ils.push_back( math::implementation::VectorLegendreSeries
                 ( clone(coefficients[4]), false ));
  ils.push_back( math::implementation::VectorLegendreSeries
                 ( clone(coefficients[5]), false ));
  ils.push_back( math::implementation::VectorLegendreSeries
                 ( clone(coefficients[6]), false ));
  ils.push_back( math::implementation::VectorLegendreSeries
                 ( clone(coefficients[7]), false ));
  ils.push_back( math::implementation::VectorLegendreSeries
                 ( clone(coefficients[8]), false ));
  ils.push_back( math::implementation::VectorLegendreSeries
                 ( clone(coefficients[9]), false ));
  ils.push_back( math::implementation::VectorLegendreSeries
                 ( clone(coefficients[10]), false ));
  LOG(INFO) << "";
  LOG(INFO) << "VectorSeries Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "VectorSeries Tests Complete!";
  return result;
}
