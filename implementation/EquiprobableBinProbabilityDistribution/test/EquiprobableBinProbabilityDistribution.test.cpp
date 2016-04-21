#define CATCH_CONFIG_RUNNER

#include <array>

#include "catch.hpp"

#include "math/implementation/EquiprobableBinProbabilityDistribution.hpp"

int testNumber = 0;
double widthFactor = 3.78787878787879E-03;
std::array<double, 33> v = {{
    -1,
    -9.96212121212121E-01,
    -9.88636363636364E-01,
    -9.77272727272727E-01,
    -9.62121212121212E-01,
    -9.43181818181818E-01,
    -9.20454545454546E-01,
    -8.93939393939394E-01,
    -8.63636363636364E-01,
    -8.29545454545455E-01,
    -7.91666666666667E-01,
    -7.5E-01,
    -7.04545454545455E-01,
    -6.55303030303031E-01,
    -6.02272727272728E-01,
    -5.45454545454546E-01,
    -4.84848484848485E-01,
    -4.20454545454546E-01,
    -3.52272727272728E-01,
    -2.80303030303031E-01,
    -2.04545454545455E-01,
    -1.25E-01,
    -4.16666666666671E-02,
    4.5454545454545E-02,
    1.36363636363636E-01,
    2.31060606060606E-01,
    3.29545454545454E-01,
    4.31818181818181E-01,
    5.37878787878788E-01,
    6.47727272727272E-01,
    7.61363636363636E-01,
    8.78787878787878E-01,
    1}};

math::implementation::DataReferencingEquiprobableBinProbabilityDistribution
< std::array< double, 33 >::iterator > epbpd(v.begin(), v.end(), true);

math::API::ProbabilityDistribution& pd = epbpd;

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "EquiprobableBinProbabilityDistribution Tests";
  LOG(INFO) << "=========================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "EquiprobableBinProbabilityDistribution Tests Complete";
  return result;
}

SCENARIO("Invalid bin boundaries will cause the ctor to throw",
  "[math], [EquiprobableBinProbabilityDistribution], [ctor]"){
  GIVEN("out of order bin boundaries"){
    std::array<double, 4> v = {{-1, 0.5, -0.5, 1}};
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        using epbpd =
          math::implementation::DataReferencingEquiprobableBinProbabilityDistribution
          < std::array< double, 4 >::iterator >;
        REQUIRE_THROWS(epbpd(v.begin(), v.end(), false));
      }
    }
  }
  GIVEN("bin boundaries specifying a zero-width bin"){
    std::array<double, 4> v = {{-1, 0.5, 0.5, 1}};
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        using epbpd =
          math::implementation::DataReferencingEquiprobableBinProbabilityDistribution
          < std::array< double, 4 >::iterator >;
        REQUIRE_THROWS(epbpd(v.begin(), v.end(), false));
      }
    }
  }
  GIVEN("insufficient bin boundaries to define a bin"){
    std::array<double, 1> v = {{-1}};
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        using epbpd =
          math::implementation::DataReferencingEquiprobableBinProbabilityDistribution
          < std::array< double, 1 >::iterator >;
        REQUIRE_THROWS(epbpd(v.begin(), v.end(), false));
      }
    }
  }
}
