#include "catch.hpp"

#include "math/interpolate.hpp"

extern int testNumber;

/* convenience definitions to cut down on template noise */
inline double
histogramIntegral( const double x,
                   // assumed x1 <= x <= x2
                   const double x1,  const double x2,
                   // assumed x1 < x2
                   const double y1,  const double y2,
                   const double dy1, const double dy2 ){
  return
    math::interpolate::integralInterpolate
    <math::interpolate::histogram>
    (x, x1, x2, y1, y2, dy1, dy2);
}

inline double
linLinIntegral( const double x,
                // assumed x1 <= x <= x2
                const double x1,  const double x2,
                // assumed x1 < x2
                const double y1,  const double y2,
                const double dy1, const double dy2 ){
  return
    math::interpolate::integralInterpolate
    <math::interpolate::linLin>
    (x, x1, x2, y1, y2, dy1, dy2);
}

inline double
logLogIntegral( const double x,
                // assumed x1 <= x <= x2
                const double x1,  const double x2,
                // assumed x1 < x2
                const double y1,  const double y2,
                const double dy1, const double dy2 ){
  return
    math::interpolate::integralInterpolate
    <math::interpolate::logLog>
    (x, x1, x2, y1, y2, dy1, dy2);
}

SCENARIO("IntegralInterpolate applied to the linear interpolation function will return the"
         " correct result",
         "[math], [interpolate], [integralInterpolate], [linLin]"){
  GIVEN("Some simple linear interpolation problems"){
    WHEN("computed using the integralInterpolate<linLin> function"){
      THEN("the correct value will be returned"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralInterpolate] No Errors Expected";
        REQUIRE(0.125 == Approx( math::interpolate::integralInterpolate
                                 < math::interpolate::linLin >( 0.5,
                                                                0.0, 1.0,
                                                                0.0, 0.5,
                                                                0.0, 1.0) ));
        REQUIRE(0.125 ==
                Approx( linLinIntegral( 0.5,
                                                           0.0, 1.0,
                                                           0.0, 0.5,
                                                           0.0, 1.0) ));

        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralInterpolate] No Errors Expected";
        REQUIRE(0.5 == Approx( math::interpolate::integralInterpolate
                                 < math::interpolate::linLin >( 1.0,
                                                                0.0, 1.0,
                                                                0.0, 0.5,
                                                                0.0, 1.0) ));
        
        REQUIRE(0.5 == Approx( linLinIntegral( 1.0,
                                                                  0.0, 1.0,
                                                                  0.0, 0.5,
                                                                  0.0, 1.0) ));
        
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralInterpolate] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::integralInterpolate
                                 < math::interpolate::linLin >( 0.0,
                                                                0.0, 1.0,
                                                                0.0, 0.5,
                                                                0.0, 1.0) ));
        
        REQUIRE(0.0 == Approx( linLinIntegral( 0.0,
                                                                  0.0, 1.0,
                                                                  0.0, 0.5,
                                                                  0.0, 1.0) ));

        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralInterpolate] No Errors Expected";
        REQUIRE(5.625 == Approx( math::interpolate::integralInterpolate
                                 < math::interpolate::linLin >( 0.5,
                                                                0.0, 1.0,
                                                                0.0, 12.5,
                                                                10.0, 15.0) ));
        REQUIRE(5.625 ==
                Approx( linLinIntegral( 0.5,
                                                           0.0, 1.0,
                                                           0.0, 12.5,
                                                           10.0, 15.0) ));
      }
    }
  }
}


SCENARIO("IntegralInterpolate applied to the logarithmic interpolation function"
         " will return the correct result",
         "[math], [interpolate], [integralInterpolate], [logLog]"){
  GIVEN("Some simple logarithmic interpolation problems"){
    WHEN("computed using the integralInterpolate<logLog> function"){
      THEN("the correct value will be returned"){
        auto f = [](const double x){return 7.50 * pow(x,3); };
        auto F = [](const double x){return 1.875 * pow(x,4); };
        std::vector<double> X = {3.75, 3.76, 3.90, 10.0, 11.22};
        double withinInterval;
        double rightBoundary;
        double leftBoundary;
        for(auto it = X.begin() + 1, end = X.end();
            it != end;
            ++it){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integralInterpolate] No Errors Expected";
          rightBoundary = it[0];
          leftBoundary = it[-1];
          withinInterval = (leftBoundary + rightBoundary) * 0.5;
          REQUIRE((F(leftBoundary)) ==
                  Approx( math::interpolate::integralInterpolate
                          < math::interpolate::logLog >( leftBoundary,
                                                         leftBoundary,
                                                         rightBoundary,
                                                         F(it[-1]), F(*it),
                                                         f(it[-1]), f(*it) ) ));
          REQUIRE((F(leftBoundary)) ==
                  Approx( logLogIntegral
                          ( leftBoundary,
                            leftBoundary, rightBoundary,
                            F(it[-1]), F(*it),
                            f(it[-1]), f(*it) ) ));
          
          REQUIRE((F(withinInterval)) ==
                  Approx( math::interpolate::integralInterpolate
                          < math::interpolate::logLog >( withinInterval,
                                                         leftBoundary,
                                                         rightBoundary,
                                                         F(it[-1]), F(*it),
                                                         f(it[-1]), f(*it) ) ));
          REQUIRE((F(withinInterval)) ==
                  Approx( logLogIntegral
                          ( withinInterval,
                            leftBoundary, rightBoundary,
                            F(it[-1]), F(*it),
                            f(it[-1]), f(*it) ) ));

          REQUIRE((F(rightBoundary)) ==
                  Approx( math::interpolate::integralInterpolate
                          < math::interpolate::logLog >( rightBoundary,
                                                         leftBoundary,
                                                         rightBoundary,
                                                         F(it[-1]), F(*it),
                                                         f(it[-1]), f(*it) ) ));
          REQUIRE((F(rightBoundary)) ==
                  Approx( logLogIntegral
                          ( rightBoundary,
                            leftBoundary, rightBoundary,
                            F(it[-1]), F(*it),
                            f(it[-1]), f(*it) ) ));
        }
      }
    }
  }
}

SCENARIO("IntegralInterpolate applied to the histgram interpolation function"
         " will return the correct result",
         "[math], [interpolate], [integralInterpolate], [histogram]"){
  GIVEN("Some simple histogram interpolation problems"){
    WHEN("computed using the integralInterpolate<histogram> function"){
      THEN("the correct value will be returned"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralInterpolate] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::integralInterpolate
                               < math::interpolate::histogram >( 0.0,
                                                                 0.0, 1.0,
                                                                 0.0, 1.0,
                                                                 0.0, 1.0) ));

        REQUIRE(0.0 ==
                Approx( histogramIntegral( 0.0,
                                                              0.0, 1.0,
                                                              0.0, 1.0,
                                                              0.0, 1.0) ));

        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralInterpolate] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::integralInterpolate
                               < math::interpolate::histogram >( 0.5,
                                                                 0.0, 1.0,
                                                                 0.0, 1.0,
                                                                 0.0, 1.0) ));

        REQUIRE(0.0 ==
                Approx( histogramIntegral( 0.5,
                                                              0.0, 1.0,
                                                              0.0, 1.0,
                                                              0.0, 1.0) ));

        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralInterpolate] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::integralInterpolate
                               < math::interpolate::histogram >( 1.0,
                                                                 0.0, 1.0,
                                                                 0.0, 1.0,
                                                                 0.0, 1.0) ));

        REQUIRE(0.0 ==
                Approx( histogramIntegral( 1.0,
                                                              0.0, 1.0,
                                                              0.0, 1.0,
                                                              0.0, 1.0) ));

        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralInterpolate] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::integralInterpolate
                               < math::interpolate::histogram >( 1.0,
                                                                 1.0, 2.0,
                                                                 0.0, 1.0,
                                                                 1.0, 2.0) ));

        REQUIRE(0.0 ==
                Approx( histogramIntegral( 1.0,
                                                              1.0, 2.0,
                                                              0.0, 1.0,
                                                              1.0, 2.0) ));

        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralInterpolate] No Errors Expected";
        REQUIRE(0.5 == Approx( math::interpolate::integralInterpolate
                               < math::interpolate::histogram >( 1.5,
                                                                 1.0, 2.0,
                                                                 0.0, 1.0,
                                                                 1.0, 2.0) ));

        REQUIRE(0.5 ==
                Approx( histogramIntegral( 1.5,
                                                              1.0, 2.0,
                                                              0.0, 1.0,
                                                              1.0, 2.0) ));

        LOG(INFO) << "Test " << ++testNumber
                  << ": [integralInterpolate] No Errors Expected";
        REQUIRE(1.0 == Approx( math::interpolate::integralInterpolate
                               < math::interpolate::histogram >( 2.0,
                                                                 1.0, 2.0,
                                                                 0.0, 1.0,
                                                                 1.0, 2.0) ));

        REQUIRE(1.0 ==
                Approx( histogramIntegral( 2.0,
                                                              1.0, 2.0,
                                                              0.0, 1.0,
                                                              1.0, 2.0) ));
      }
    }
  }
}

