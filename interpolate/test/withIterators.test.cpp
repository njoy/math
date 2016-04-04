#include <vector>

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

auto fLin = [](double x){return 5.0*x + 4;};
auto FLin = [](double x){return 2.5*std::pow(x,2) + 4 * x;};

auto fLog = [](double x){return 6.0*pow(x, 2.0);};
auto FLog = [](double x){return 2.0*pow(x, 3.0);};

std::vector<double> X = {1.0,2.0,3.0,4.0,5.0};
std::vector<double> Ylin = {fLin(X[0]),
                            fLin(X[1]),
                            fLin(X[2]),
                            fLin(X[3]),
                            fLin(X[4])};
std::vector<double> integralYlin = {FLin(X[0]),
                                    FLin(X[1]),
                                    FLin(X[2]),
                                    FLin(X[3]),
                                    FLin(X[4])};
std::vector<double> Ylog = {fLog(X[0]),
                            fLog(X[1]),
                            fLog(X[2]),
                            fLog(X[3]),
                            fLog(X[4])};
std::vector<double> integralYlog = {FLog(X[0]),
                                    FLog(X[1]),
                                    FLog(X[2]),
                                    FLog(X[3]),
                                    FLog(X[4])};
auto Xbegin = X.begin();
auto Xend   = X.end();
auto YlinBegin = Ylin.begin();
auto integralYlinBegin = integralYlin.begin();
auto YlogBegin = Ylog.begin();
auto integralYlogBegin = integralYlog.begin();

SCENARIO("The interpolation withIterators function"
         " will return the correct value"){
  GIVEN("iterators to a domain and function evaluations"){
    WHEN("passed to the withIterator function"){
      THEN("the correct value will be returned"){
        for (double x : X){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          REQUIRE(fLin(x) ==
                  Approx(
                    math::interpolate::withIterators<
                    std::vector<double>::iterator, math::interpolate::linLin >
                    (x, Xbegin, Xend, YlinBegin)));
        }
        for (unsigned int i = 1; i < X.size(); ++i){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          double x = ( X[i] + X[i-1] ) / 2.0;
          REQUIRE(fLin(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator,
                      math::interpolate::linLin >
                    (x, Xbegin, Xend, YlinBegin)));
          
        }
        for (double x : X){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          REQUIRE(fLog(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator, math::interpolate::logLog >
                    (x, Xbegin, Xend, YlogBegin)));
        }
        for (unsigned int i = 1; i < X.size(); ++i){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          double x = ( X[i] + X[i-1] ) / 2.0;
          REQUIRE(fLog(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator, math::interpolate::logLog >
                    (x, Xbegin, Xend, YlogBegin)));
          
        }
      }
    }
  }
}

SCENARIO("The integral interpolation withIterators function"
         " will return the correct value"){
  GIVEN("iterators to a domain and function evaluations"){
    WHEN("passed to the withIterator function"){
      THEN("the correct value will be returned"){
        for (double x : X){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          REQUIRE(FLin(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator,
                    std::vector<double>::iterator,
                    math::interpolate::integralInterpolate
                    <math::interpolate::linLin> >
                    (x, Xbegin, Xend, integralYlinBegin, YlinBegin)));
        }
        for (unsigned int i = 1; i < X.size(); ++i){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          double x = ( X[i] + X[i-1] ) / 2.0;
          REQUIRE(FLin(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator,
                    std::vector<double>::iterator,
                      linLinIntegral >
                    (x, Xbegin, Xend, integralYlinBegin, YlinBegin)));
          
        }
        for (double x : X){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          REQUIRE(FLog(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator,
                    std::vector<double>::iterator,
                      logLogIntegral>
                    (x, Xbegin, Xend, integralYlogBegin, YlogBegin)));
        }
        for (unsigned int i = 1; i < X.size(); ++i){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          double x = ( X[i] + X[i-1] ) / 2.0;
          REQUIRE(FLog(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator,
                    std::vector<double>::iterator,
                      logLogIntegral >
                    (x, Xbegin, Xend, integralYlogBegin, YlogBegin)));
          
        }
      }
    }
  }
}

SCENARIO("The integral interpolation withIterators function with one"
         " iterator parameter will return the correct value"){
  GIVEN("iterators to a domain and function evaluations"){
    WHEN("passed to the withIterator function"){
      THEN("the correct value will be returned"){
        for (double x : X){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          REQUIRE(FLin(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator,
                     math::interpolate::integralInterpolate
                    <math::interpolate::linLin> >
                    (x, Xbegin, Xend, integralYlinBegin, YlinBegin)));
        }
        for (unsigned int i = 1; i < X.size(); ++i){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          double x = ( X[i] + X[i-1] ) / 2.0;
          REQUIRE(FLin(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator,
                       linLinIntegral >
                    (x, Xbegin, Xend, integralYlinBegin, YlinBegin)));
          
        }
        for (double x : X){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          REQUIRE(FLog(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator,
                       logLogIntegral>
                    (x, Xbegin, Xend, integralYlogBegin, YlogBegin)));
        }
        for (unsigned int i = 1; i < X.size(); ++i){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [withIterators] No Errors Expected";
          double x = ( X[i] + X[i-1] ) / 2.0;
          REQUIRE(FLog(x) ==
                  Approx(
                    math::interpolate::withIterators
                    < std::vector<double>::iterator,
                       logLogIntegral >
                    (x, Xbegin, Xend, integralYlogBegin, YlogBegin)));
          
        }
      }
    }
  }
}
