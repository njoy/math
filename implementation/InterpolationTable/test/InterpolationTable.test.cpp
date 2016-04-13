#define CATCH_CONFIG_RUNNER

#include <functional>

#include "catch.hpp"

#include "math/implementation.hpp"

namespace{
  auto f_ = []( const double x ){ return 5.0 + 2.0 * x; };
  auto F_ = []( const double x ){ return 5.0 * x + pow(x, 2); };

  template< typename T >
  T clone(T& t){return t;}
}

namespace mi = math::implementation; 

int testNumber = 0;

std::vector<double> x {0, 1.0, 2.0, 3.0, 4.0};
std::vector<double> y {f_(x[0]), f_(x[1]), f_(x[2]), f_(x[3]), f_(x[4])};
std::vector<double> Y {F_(x[0]), F_(x[1]), F_(x[2]), F_(x[3]), F_(x[4])};

std::function<double(double)> f = f_;
std::function<double(double)> F = F_;
mi::InterpolationTable
< math::interpolate::linLin, mi::ReferencePolicy, std::vector<double>::iterator >
borrowTable( x.begin(), x.end(), y.begin(), y.end(), false );

mi::InterpolationTable
< math::interpolate::linLin, mi::TransferPolicy, std::vector<double> >
ownedTable( clone(x), clone(y), false );

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "InterpolationTable Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "InterpolationTable Tests Complete!";
  return result;
}

using DOTable = mi::DataOwningInterpolationTable< math::interpolate::linLin >;
SCENARIO("The ctor will throw for invalid grids",
         "[math], [InterpolationTable], [ctor]"){
  GIVEN("grids with mismatched lengths"){
    std::vector<double> x0 = { 1.0, 2.0, 3.0 };
    std::vector<double> y0 = { 1.0, 2.0, 3.0, 4.0 };
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [ctor] Errors Expected";
        REQUIRE_THROWS( DOTable( x0, y0, false ) );
      }
    }
  }

  GIVEN("an out of order x grid"){
    std::vector<double> x0 = { 1.0, 3.0, 2.0 };
    std::vector<double> y0 = { 1.0, 2.0, 3.0 };
    WHEN("passed to the ctor"){
      THEN("the ctor will throw"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [ctor] Errors Expected";
        REQUIRE_THROWS( DOTable( x0, y0, false ) );
      }
    }
  }
}
