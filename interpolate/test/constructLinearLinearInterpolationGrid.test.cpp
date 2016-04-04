#include "catch.hpp"

#include "math/interpolate.hpp"

extern int testNumber;


SCENARIO("The constructLinearLinearInterpolationGrid routine can render a grid"
         " for linear interpolation of an arbirary function over a specified"
         " region given the a pair of iterators encompassing the beginning and"
         " end of the region of interest and any inflection points therin",
         "[math], [interpolate], [constructLinearLinearInterpolationGrid]"){
    
  auto relativeError = [](const double reference, const double trial){
    return std::abs((trial - reference) / reference);
  };
  
  auto absoluteError = [](const double reference, const double trial){
    return std::abs(trial - reference);
  };

  double relativeErrorTolerance = 1E-8;
  double absoluteErrorThreshold = 1E-5;  
  auto criterion =
    [&absoluteErrorThreshold,
     &relativeErrorTolerance,
     &absoluteError,
     &relativeError](const double reference, const double trial){
    return
    ( absoluteError(reference, trial) <= 1E-8 ) or
    ( relativeError(reference, trial) <= 1E-5 );
  };

  int offset = 0;
  GIVEN("a criterion specificying convergence in terms of relative error with" 
        " with an absolute error threshold "){
    WHEN("used to construct a linear-linear grid for the sine function"){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [constructLinearLinearInterpolationGrid] No Errors Expected";
      constexpr double pi = 3.141592653589793;
      std::vector<double> startingYs(3, 0.0);
      std::vector<double> startingXs = {0.0, pi, 2*pi};
      std::vector<double> X, Y;
      REQUIRE_NOTHROW(
        math::interpolate::constructLinearLinearInterpolationGrid<std::sin>
        ( criterion, startingXs.begin(), startingXs.end(),
          startingYs.begin(), X, Y ));
      auto length = X.size();
      THEN("the function value will be exact at grid points"){
        auto pointsToEvaluate = length - offset;
        auto xit = X.begin() + offset;
        auto yit = Y.begin() + offset;
        while (pointsToEvaluate--){
          REQUIRE(std::sin(*xit) == Approx(*yit));
          ++xit; ++yit;
        }
      }
      AND_THEN("the value will be within tolerance at the mid-point"
               " between grid points"){
        LOG(INFO) << "Test " << ++testNumber <<
          ": [constructLinearLinearInterpolationGrid] No Errors Expected";
        auto pointsToEvaluate = length - ++offset;
        auto xit = X.begin() + offset;
        auto yit = Y.begin() + offset;
        double x, y;
        while (pointsToEvaluate--){
          x = (xit[-1] + xit[0]) * 0.5;
          y = (yit[-1] + yit[0]) * 0.5;
          REQUIRE(criterion(std::sin(x), y));
          ++xit; ++yit;
        }
      }
      AND_THEN("additional values can be appended to an existing grid"){
        LOG(INFO) << "Test " << ++testNumber <<
          ": [constructLinearLinearInterpolationGrid] No Errors Expected";
        std::vector<double> startingXs = {2*pi, 3*pi, 4*pi};
        /* convergence criteria may be modified */
        relativeErrorTolerance = 1E-7;
        absoluteErrorThreshold = 1E-6;
        math::interpolate::constructLinearLinearInterpolationGrid<std::sin>
        ( criterion, startingXs.begin(), startingXs.end(),
          startingYs.begin(), X, Y );
        offset = length;
        length = X.size();
        THEN("the function value will be exact at grid points"){
          LOG(INFO) << "Test " << ++testNumber <<
            ": [constructLinearLinearInterpolationGrid] No Errors Expected";
          auto pointsToEvaluate = length - offset;
          auto xit = X.begin() + offset;
          auto yit = Y.begin() + offset;
          while (pointsToEvaluate--){
            REQUIRE(std::sin(*xit) == Approx(*yit));
            ++xit; ++yit;
          }
        }
        AND_THEN("the value will be within tolerance at the mid-point"
                 " between grid points"){
          LOG(INFO) << "Test " << ++testNumber <<
            ": [constructLinearLinearInterpolationGrid] No Errors Expected";
          auto pointsToEvaluate = length - ++offset;
          auto xit = X.begin() + offset;
          auto yit = Y.begin() + offset;
          double x, y;
          while (pointsToEvaluate--){
            x = (xit[-1] + xit[0]) * 0.5;
            y = (yit[-1] + yit[0]) * 0.5;
            REQUIRE(criterion(std::sin(x), y));
            ++xit; ++yit;
          }
        }        
      }
      AND_THEN("overlapping grids will cause the function to throw"){
        LOG(INFO) << "Test " << ++testNumber <<
          ": [constructLinearLinearInterpolationGrid] Errors Expected";
        std::vector<double> startingXs = {0, pi, 2*pi};
        REQUIRE_THROWS(
          math::interpolate::constructLinearLinearInterpolationGrid<std::sin>
          ( criterion, startingXs.begin(), startingXs.end(),
            startingYs.begin(), X, Y ));
      }
      AND_THEN("gaps between grids will cause the function to throw"){
        LOG(INFO) << "Test " << ++testNumber <<
          ": [constructLinearLinearInterpolationGrid] Errors Expected"; 
        std::vector<double> startingXs = {5*pi, 6*pi, 7*pi};
        REQUIRE_THROWS(
          math::interpolate::constructLinearLinearInterpolationGrid<std::sin>
          ( criterion, startingXs.begin(), startingXs.end(),
            startingYs.begin(), X, Y ));
      }
    }
  }
}
      
