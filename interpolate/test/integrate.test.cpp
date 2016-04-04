#include "catch.hpp"

#include "math/interpolate.hpp"

extern int testNumber;

SCENARIO("Integrate applied to the linear interpolation function will return the"
         " correct result",
         "[math], [interpolate], [integrate], [linLin]"){
  GIVEN("Some simple linear interpolation problems"){
    WHEN("computed using the integrate<linLin> function"){
      THEN("the correct value will be returned"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(0.5 == Approx( math::interpolate::integrate
                               < math::interpolate::linLin >( 0.0, 1.0,
                                                              0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(0.25 == Approx( math::interpolate::integrate
                                < math::interpolate::linLin >( 0.5, 1.0,
                                                               0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(0.5 == Approx( math::interpolate::integrate
                               < math::interpolate::linLin >( 0.0, 1.0,
                                                              1.0, 0.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(0.5 == Approx( math::interpolate::integrate
                               < math::interpolate::linLin >( 1.0, 2.0,
                                                              0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(1.5 == Approx( math::interpolate::integrate
                               < math::interpolate::linLin >( 1.0, 2.0,
                                                              1.0, 2.0) ));
      }
    }
  }
}

SCENARIO("Integrate applied to the logarithmic interpolation function will"
         " return the correct result",
         "[math], [interpolate], [integrate], [logLog]"){
  GIVEN("Some simple logarithmic interpolation problems"){
    WHEN("computed using the integrate<logLog> function"){
      THEN("the correct value will be returned"){
        auto f = [](const double x){return 7.50 * pow(x,3); };
        auto F = [](const double x){return 1.875 * pow(x,4); };
        std::vector<double> X = {3.75, 3.76, 3.90, 10.0, 11.22};
        for(auto it = X.begin() + 1, end = X.end();
            it != end;
            ++it){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          REQUIRE((F(*it) - F(it[-1])) ==
                  Approx( math::interpolate::integrate
                          < math::interpolate::logLog >( it[-1], *it,
                                                         f(it[-1]), f(*it) ) ));
        }
      }
    }
  }
}

SCENARIO("Integrate applied to the linear-logarithmic"
         " interpolation function will"
         " return the correct result",
         "[math], [interpolate], [integrate], [linLog]"){
  GIVEN("Some simple lin-logarithmic interpolation problems"){
    WHEN("computed using the integrate<linLog> function"){
      THEN("the correct value will be returned"){
        auto f1 = [](double x){ return 13.2 * log(3.2 * x);};
        auto F1 = [](double x){ return 13.2 * x * (log(3.2 * x) - 1);};
        auto f2 = [](double x){ return -5.6 * log(2.4 * x);};
        auto F2 = [](double x){ return -5.6 * x * (log(2.4 * x) - 1);};
        std::vector<double> X = {1E-5, 1E-2, 1, 10, 10000, 35000};
        for(auto it = X.begin() + 1, end = X.end();
            it != end;
            ++it){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          REQUIRE((F1(*it) - F1(it[-1])) ==
                  Approx( math::interpolate::integrate
                          < math::interpolate::linLog >( it[-1], *it,
                                                         f1(it[-1]), f1(*it))));
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          REQUIRE((F2(*it) - F2(it[-1])) ==
                  Approx( math::interpolate::integrate
                          < math::interpolate::linLog >( it[-1], *it,
                                                         f2(it[-1]), f2(*it))));
        }
      }
    }
  }
}

SCENARIO("Integrate applied to the logarithmic-linear"
         " interpolation function will"
         " return the correct result",
         "[math], [interpolate], [integrate], [logLin]"){
  GIVEN("Some simple log-linear interpolation problems"){
    WHEN("computed using the integrate<logLin> function"){
      THEN("the correct value will be returned"){
        auto f1 = [](double x){ return 13.2 * pow(3.14, 0.002*x);};
        auto F1 = [](double x){ return 5768.11 * exp(0.00228845*x);};
        auto f2 = [](double x){ return -13.2 * pow(3.14, 0.002*x);};
        auto F2 = [](double x){ return -5768.11 * exp(0.00228845*x);};
        std::vector<double> X = {10, 1, 1E-2, 1E-5, 0.0,
                             1E-5, 1E-2, 1, 10};
        for(auto it = X.begin() + 1, end = X.end();
            it != end;
            ++it){
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          REQUIRE((F1(*it) - F1(it[-1])) ==
                  Approx( math::interpolate::integrate
                          < math::interpolate::logLin >( it[-1], *it,
                                                         f1(it[-1]), f1(*it))));
          LOG(INFO) << "Test " << ++testNumber
                    << ": [integrate] No Errors Expected";
          REQUIRE((F2(*it) - F2(it[-1])) ==
                  Approx( math::interpolate::integrate
                          < math::interpolate::logLin >( it[-1], *it,
                                                         f2(it[-1]), f2(*it))));
        }
      }
    }
  }
}

SCENARIO("Integrate applied to the histgram interpolation function will"
         " return the correct result",
         "[math], [interpolate], [integrate], [histogram]"){
  GIVEN("Some simple histogram interpolation problems"){
    WHEN("computed using the integrate<histogram> function"){
      THEN("the correct value will be returned"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::integrate
                               < math::interpolate::histogram >( 0.0, 1.0,
                                                              0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::integrate
                                < math::interpolate::histogram >( 0.5, 1.0,
                                                               0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(1.0 == Approx( math::interpolate::integrate
                               < math::interpolate::histogram >( 0.0, 1.0,
                                                              1.0, 0.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(0.0 == Approx( math::interpolate::integrate
                               < math::interpolate::histogram >( 1.0, 2.0,
                                                              0.0, 1.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(1.0 == Approx( math::interpolate::integrate
                               < math::interpolate::histogram >( 1.0, 2.0,
                                                              1.0, 2.0) ));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [integrate] No Errors Expected";
        REQUIRE(0.5 == Approx( math::interpolate::integrate
                               < math::interpolate::histogram >( 1.0, 1.5,
                                                                 1.0, 2.0) ));
      }
    }
  }
}
