#include <functional>

#include "catch.hpp"

#include "math/implementation/LegendreSeries.hpp"

extern int testNumber;
extern std::function<double(double)> f;
extern std::function<double(double)> f_int;
extern std::vector
< math::implementation::LegendreSeries
  < math::implementation::ReferencePolicy, std::vector<double>::iterator > > ils;
extern std::vector< std::function< double(double) > > integralReferences;

SCENARIO(
  "The legendre series integrate function will return an anti-derivative series",
  "[math], [LegendreSeries], [integrate]"){
  GIVEN("an LegendreSeries and a reference function anti-derivative"){
    WHEN("asked to generate an integral series"){
      THEN("the values will match the reference"){
        {
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          for (int i = 0 ; i < 11; ++i){
            auto integralSeries = ils[i].integrate(0, 0);
            double dx = 2.0/100.0;
            double x = -2.0;
            int j = 101;
            double diff = -integralReferences[i](0);
            while (j--){
              REQUIRE( (integralReferences[i](x) + diff) ==
                       Approx(integralSeries->evaluate(x)) );
              x+= dx;
            }
          }
        }
        {
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          for (int i = 0 ; i < 11; ++i){
            auto integralSeries = ils[i].integrate(0, 1);
            double dx = 4.0/100.0;
            double x = -2.0;
            int j = 101;
            double diff = 1 - integralReferences[i](0);
            while (j--){
              REQUIRE( (integralReferences[i](x) + diff) ==
                       Approx(integralSeries->evaluate(x)) );
              x+= dx;
            }
          }
        }
        {
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          for (int i = 0 ; i < 11; ++i){
            auto integralSeries = ils[i].integrate(1, 1);
            double dx = 4.0/100.0;
            double x = -2.0;
            int j = 101;
            double diff = 1 - integralReferences[i](1);
            while (j--){
              REQUIRE( (integralReferences[i](x) + diff) ==
                       Approx(integralSeries->evaluate(x)) );
              x+= dx;
            }
          }
        }
      }
    }
  }
}
