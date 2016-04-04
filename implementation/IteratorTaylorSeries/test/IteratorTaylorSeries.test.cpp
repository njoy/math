#define CATCH_CONFIG_RUNNER

#include <cmath>
#include <functional>

#include "catch.hpp"

#include "math/implementation/IteratorTaylorSeries.hpp"

int testNumber = 0;
std::vector<double> coefficients = {0.5, 2, 0.75, 0.1, 0.01, 0.005};
std::function<double(double)>
f = [](const double x){
  return
  coefficients[0] +
  coefficients[1] * x +
  coefficients[2] * pow(x,2) +
  coefficients[3] * pow(x,3) +
  coefficients[4] * pow(x,4) +
  coefficients[5] * pow(x,5);
};

std::function<double(double)>
f_deriv = [](const double x){
  return
  coefficients[1] +
  2 * coefficients[2] * x +
  3 * coefficients[3] * pow(x,2) +
  4 * coefficients[4] * pow(x,3) +
  5 * coefficients[5] * pow(x,4);
};

std::function<double(double)>
f_int = [](const double x){
  return
  coefficients[0] * x +
  coefficients[1] * pow(x,2) / (2.0) +
  coefficients[2] * pow(x,3) / (3.0) +
  coefficients[3] * pow(x,4) / (4.0) +
  coefficients[4] * pow(x,5) / (5.0) +
  coefficients[5] * pow(x,6) / (6.0);
};

math::implementation::IteratorTaylorSeries<std::vector<double>::iterator>
its(coefficients.begin(), coefficients.end(), false);

math::API::SeriesExpansion& ser = its;

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "IteratorTaylorSeries Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "IteratorTaylorSeries Tests Complete!";
  return result;
}

SCENARIO("The ctor will throw for invalid coefficient ranges",
         "[math], [IteratorTaylorSeries], [ctor]"){
  GIVEN("a zero length range"){
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [ctor] Errors Expected";
        REQUIRE_THROWS(
          math::implementation::IteratorTaylorSeries
          <std::vector<double>::iterator>
          its(coefficients.begin(), coefficients.begin(), false));
      }
    }
  }

  GIVEN("a negative length range"){
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [ctor] Errors Expected";
        REQUIRE_THROWS(
          math::implementation::IteratorTaylorSeries
          <std::vector<double>::iterator>
          its(coefficients.begin(), coefficients.begin() - 1, false));
      }
    }
  }
}
