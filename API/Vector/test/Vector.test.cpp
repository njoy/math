#define CATCH_CONFIG_RUNNER

// other includes
#include "catch.hpp"

// what we're testing
#include "math/API/Vector.hpp"

int testNumber = 0;

namespace {

  // test variable

}

int main( int argc, const char* argv[] )
{
  LOG(INFO) << "";
  LOG(INFO) << " Vector Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "Vector Tests Complete!";
  return result;
}

SCENARIO("Vector construction ", "[math], [Vector]") {

  GIVEN("a default constructor"){
        
    WHEN("constructing a valid Vector using the default constructor") {

      math::API::Vector<double> defaultconstructor;
      THEN("the size of the vector should be zero") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [construction] No Errors Expected";
        REQUIRE( 0 == defaultconstructor.size() );
      }
    }
  }

  GIVEN("a constructor with a vector size") {

    WHEN("constructing a valid Vector using the constructor with vector size") {

      math::API::Vector<double> vector(3);
      THEN("the size of the vector should be 3 and the elements equal to 0") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [construction] No Errors Expected";
        REQUIRE( 3 == vector.size() );
      }
    }
  }

  GIVEN("a copy constructor") {

    WHEN("constructing a valid Vector using the copy constructor") {

      math::API::Vector<double> v(2);
      v(0) = 1.0;
      v(1) = 2.0;
      math::API::Vector<double> copy(v);
      THEN("the size of both vectors should be the same") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [construction] No Errors Expected";
        REQUIRE( 2 == copy.size() );
        REQUIRE( v(0) == copy(0) );
        REQUIRE( v(1) == copy(1) );
      }
    }
  }

  GIVEN("a copy assignment operator") {

    WHEN("constructing a valid Vector using the copy constructor") {

      math::API::Vector<double> v(2);
      v(0) = 1.0;
      v(1) = 2.0;
      math::API::Vector<double> assign;
      assign = v;
      THEN("the size and elements of both vectors should be the same") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [construction] No Errors Expected";
        REQUIRE( 2 == assign.size() );
        REQUIRE( v(0) == assign(0) );
        REQUIRE( v(1) == assign(1) );
      }
    }
  }
}

SCENARIO("Vector resizing ", "[math], [Vector]"){
    
  GIVEN("a resize function") {

    WHEN("resizing a valid Vector using the resize function") {

      math::API::Vector<double> v(3);
      v.resize(2);
      THEN("the size of the vector should be the new size") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [resizing] No Errors Expected";
        REQUIRE( 2 == v.size() );
      }
    }
  }
}

SCENARIO("Vector arithmetic ", "[math], [Vector]"){

  GIVEN("vector operations: +, -, *, /, dot product and norm") {

    WHEN("using the operations") {

      math::API::Vector<double> v(2);
      v(0) = 1.0;
      v(1) = 2.0;
      math::API::Vector<double> w(2);
      w(0) = 8.0;
      w(1) = 6.0;
      math::API::Vector<double> x(2);
      double s = 2.0;
      double d = 0.0;
      THEN("give the correct result") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [arithmetic] No Errors Expected";

        x = v + w;
        REQUIRE( Approx( 9.0 ) == x(0) );
        REQUIRE( Approx( 8.0 ) == x(1) );

        x = v - w;
        REQUIRE( Approx( -7.0 ) == x(0) );
        REQUIRE( Approx( -4.0 ) == x(1) );

        x = -v;
        REQUIRE( Approx( -1.0 ) == x(0) );
        REQUIRE( Approx( -2.0 ) == x(1) );

        x = v;
        x += w;
        REQUIRE( Approx( 9.0 ) == x(0) );
        REQUIRE( Approx( 8.0 ) == x(1) );

        x = v;
        x -= w;
        REQUIRE( Approx( -7.0 ) == x(0) );
        REQUIRE( Approx( -4.0 ) == x(1) );

        x = v * s;
        REQUIRE( Approx( 2.0 ) == x(0) );
        REQUIRE( Approx( 4.0 ) == x(1) );

        x = s * v;
        REQUIRE( Approx( 2.0 ) == x(0) );
        REQUIRE( Approx( 4.0 ) == x(1) );

        x = v;
        x *= s;
        REQUIRE( Approx( 2.0 ) == x(0) );
        REQUIRE( Approx( 4.0 ) == x(1) );

        x = v / s;
        REQUIRE( Approx( 0.5 ) == x(0) );
        REQUIRE( Approx( 1.0 ) == x(1) );

        x = v;
        x /= s;
        REQUIRE( Approx( 0.5 ) == x(0) );
        REQUIRE( Approx( 1.0 ) == x(1) );

        d = v.dot(w);
        REQUIRE( Approx( 20 ) == d );

        d = w.norm();
        REQUIRE( Approx( 10 ) == d );
      }
    }
  }
}

