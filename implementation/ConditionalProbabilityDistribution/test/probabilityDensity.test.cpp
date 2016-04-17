#include "catch.hpp"

#include "math/implementation/ConditionalProbabilityDistribution.hpp"

extern int testNumber;

extern std::vector<double> conditions;

extern std::function<double(double)> pdf0;
extern std::function<double(double)> pdf1;
extern std::function<double(double)> pdf2;

extern std::unique_ptr
  < math::implementation::ConditionalProbabilityDistribution
  < math::interpolate::linLin, math::interpolate::linLin > > bvpd;

SCENARIO(
  "The probability density will return a value that matches the composed PDF", 
  "[math], [ConditionalProbabilityDistribution], [probabilityDensity]"){
  GIVEN( "valid conditions" ){
    WHEN( "the condition falls on a boundary" ){
      THEN( "the return value will match the reference" ){
        LOG(INFO) << "Test " << ++testNumber <<
          ": [probabilityDensity] No Errors Expected";
        std::vector<double> events = {-1.0, -0.5, 0.0, 0.5, 1.0};
        double condition = conditions[0];
        for( auto event : events ){
          REQUIRE( pdf0(event) == Approx( bvpd->probabilityDensity
                                          ( event, condition ) ) );
        }
        condition = conditions[1];
        for( auto event : events ){
          REQUIRE( pdf1(event) == Approx( bvpd->probabilityDensity
                                          ( event, condition ) ) );
        }
        condition = conditions[2];
        for( auto event : events ){
          REQUIRE( pdf2(event) == Approx( bvpd->probabilityDensity
                                          ( event, condition ) ) );
        }
      }
    }

    WHEN( "the conditions are not on a boundary" ){
      std::vector<double> events = {-1.0, -0.5, 0.0, 0.5, 1.0};
      double condition = 0.5 * ( conditions[0] + conditions[1] );
      for( auto event : events ){
        auto reference = 0.5 * ( pdf0(event) + pdf1(event) );
        REQUIRE( reference == Approx( bvpd->probabilityDensity
                                      ( event, condition) ) );
      }
      condition = 0.5 * ( conditions[1] + conditions[2] );
      for( auto event : events ){
        auto reference = 0.5 * ( pdf1(event) + pdf2(event) );
        REQUIRE( reference == Approx( bvpd->probabilityDensity
                                      ( event, condition) ) );
      }
      condition = 0.25 * ( conditions[1] + 3 * conditions[2] );
      for( auto event : events ){
        auto reference = 0.25 * ( pdf1(event) + 3 * pdf2(event) );
        REQUIRE( reference == Approx( bvpd->probabilityDensity
                                      ( event, condition) ) );
      }
    }      
  }   // GIVEN

  GIVEN( "invalid conditions" ){
    LOG(INFO) << "Test " << ++testNumber
              << ": [probabilityDensity] Errors Expected";
    std::vector<double> conditions = {-0.00001, 2.1};
    GIVEN( "valid events" ){
      THEN( "exceptions will be thrown" ){
        for ( double c : conditions ){
          REQUIRE_THROWS( bvpd->probabilityDensity(0.0, c) );
        }
      }
    }
  } // GIVEN---invalid conditions
}   // SCENARIO

