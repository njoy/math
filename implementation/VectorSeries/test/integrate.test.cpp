#include <functional>

#include "catch.hpp"

#include "math/implementation/VectorSeries.hpp"

extern int testNumber;
extern std::function<double(double)> f;
extern std::function<double(double)> f_int;
extern std::vector
< math::implementation::VectorLegendreSeries > ils;
extern std::vector< std::function< double(double) > > integralReferences;

SCENARIO(
  "The vector legendre series's integrate function will return a sequence of" 
  " coeffcients describing the legendre series form of the integral of the"
  " vector series",
  "[math], [VectorSeries], [integrate]"){
  GIVEN("an VectorLegendreSeries describing a reference function and the"
        " reference function's anti-derivative"){
    WHEN("the VectorLegendreSeries is queried for an integral series"){
      THEN("evaluations of the VectorLegendreSeries constructed from the"
           " coefficients returned form the integrte method will match the" 
           " evaluations of the reference anti-derivative"){
        {
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          for (int i = 0 ; i < 11; ++i){
            auto integralSeries =
              math::implementation::VectorLegendreSeries(ils[i].integrate(0, 0));
            double dx = 2.0/100.0;
            double x = -2.0;
            int j = 101;
            double diff = -integralReferences[i](0);
            while (j--){
              REQUIRE( (integralReferences[i](x) + diff) ==
                       Approx(integralSeries(x)) );
              x+= dx;
            }
          }
        }
        {
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          for (int i = 0 ; i < 11; ++i){
            auto integralSeries =
              math::implementation::VectorLegendreSeries(ils[i].integrate(0, 1));
            double dx = 4.0/100.0;
            double x = -2.0;
            int j = 101;
            double diff = 1 - integralReferences[i](0);
            while (j--){
              REQUIRE( (integralReferences[i](x) + diff) ==
                       Approx(integralSeries(x)) );
              x+= dx;
            }
          }
        }
        {
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          for (int i = 0 ; i < 11; ++i){
            auto integralSeries =
              math::implementation::VectorLegendreSeries(ils[i].integrate(1, 1));
            double dx = 4.0/100.0;
            double x = -2.0;
            int j = 101;
            double diff = 1 - integralReferences[i](1);
            while (j--){
              REQUIRE( (integralReferences[i](x) + diff) ==
                       Approx(integralSeries(x)) );
              x+= dx;
            }
          }
        }
      }
    }
  }
}
