#define CATCH_CONFIG_RUNNER

// system include
#include <complex>

// other includes
#include "catch.hpp"

// what we're testing
#include "math/API/Matrix.hpp"

int testNumber = 0;

namespace {

  // test variable

}

int main( int argc, const char* argv[] )
{
  LOG(INFO) << "";
  LOG(INFO) << " Matrix Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "Matrix Tests Complete!";
  return result;
}

SCENARIO("Matrix construction ", "[math], [Matrix]") {

  GIVEN("a default constructor"){

    WHEN("constructing a valid Matrix using the default constructor") {

      math::API::Matrix<double> defaultconstructor;
      THEN("the number of columns and rows of the Matrix should be zero") {

        LOG(INFO) << "Test " << ++testNumber 
          << ": [construction] No Errors Expected";
        REQUIRE( 0 == defaultconstructor.rows() );
        REQUIRE( 0 == defaultconstructor.cols() );
      }
    }
  }

  GIVEN("a constructor with matrix sizes") {

    WHEN("constructing a valid Matrix using the constructor with row and colu;mn siwe") {

      math::API::Matrix<double> matrix(3, 4);
      THEN("the size of the matrix should be 3 rows and 4 columns") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [construction] No Errors Expected";
        REQUIRE( 3 == matrix.rows() );
      }
    }
  }

  GIVEN("a copy constructor") {

    WHEN("constructing a valid Matrix using the copy constructor") {

      math::API::Matrix<double> a(2, 2);
      a(0, 0) = 1.0;
      a(0, 1) = 2.0;
      a(0, 0) = 3.0;
      a(0, 1) = 4.0;
      math::API::Matrix<double> copy(a);
      THEN("the size and elements of both matrices should be the same") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [construction] No Errors Expected";
        REQUIRE( 2 == copy.rows() );
        REQUIRE( 2 == copy.cols() );
        REQUIRE( a(0, 0) == copy(0, 0) );
        REQUIRE( a(0, 1) == copy(0, 1) );
        REQUIRE( a(1, 0) == copy(1, 0) );
        REQUIRE( a(1, 1) == copy(1, 1) );
      }
    }
  }

  GIVEN("a copy assignment operator") {

    WHEN("constructing a valid Vector using the copy constructor") {

      math::API::Matrix<double> a(2, 2);
      a(0, 0) = 1.0;
      a(0, 1) = 2.0;
      a(0, 0) = 3.0;
      a(0, 1) = 4.0;
      math::API::Matrix<double> assign;
      assign = a;
      THEN("the size and elements of both matrices should be the same") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [construction] No Errors Expected";
        REQUIRE( 2 == assign.rows() );
        REQUIRE( 2 == assign.cols() );
        REQUIRE( a(0, 0) == assign(0, 0) );
        REQUIRE( a(0, 1) == assign(0, 1) );
        REQUIRE( a(1, 0) == assign(1, 0) );
        REQUIRE( a(1, 1) == assign(1, 1) );
      }
    }
  }
}

SCENARIO("Matrix resizing ", "[math], [Matrix]") {

    GIVEN("a resize function") {

        WHEN("resizing a valid Matrix using the resize function") {

            math::API::Matrix<double> matrix(2, 3);
            matrix.resize(3, 2);
            THEN("the size of the Matrix should be the new size") {

        LOG(INFO) << "Test " << ++testNumber
        << ": [resizing] No Errors Expected";
        REQUIRE( 3 == matrix.rows() );
        REQUIRE( 2 == matrix.cols() );
            }
        }
    }
}

SCENARIO("Matrix arithmetic ", "[math], [Matrix]") {

  GIVEN("matrix operations: +, -, *, /, dot product and norm") {

    WHEN("using the operations") {

      math::API::Matrix<double> a(2, 2);
      math::API::Matrix<double> b(2, 2);
      math::API::Matrix<double> c(2, 2);
      math::API::Matrix<std::complex<double>> c1(2, 2);
      math::API::Matrix<std::complex<double>> c2(2, 2);
      a(0, 0) = 1.0;
      a(0, 1) = 2.0;
      a(1, 0) = 3.0;
      a(1, 1) = 4.0;
      b(0, 0) = 8.0;
      b(0, 1) = 6.0;
      b(1, 0) = 4.0;
      b(1, 1) = 2.0;
      c1(0, 0) = std::complex<double>(1.0, 1.0);
      c1(0, 1) = std::complex<double>(2.0, 2.0);
      c1(1, 0) = std::complex<double>(3.0, 3.0);
      c1(1, 1) = std::complex<double>(4.0, 4.0);

      math::API::Vector<double> v(2);
      math::API::Vector<double> x(2);
      v(0) = 1.0;
      v(1) = 2.0;

      double s = 2.0;

      THEN("give the correct result") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [arithmetic] No Errors Expected";

        c = a + b;
        REQUIRE( Approx( 9.0 ) == c(0, 0) );
        REQUIRE( Approx( 8.0 ) == c(0, 1) );
        REQUIRE( Approx( 7.0 ) == c(1, 0) );
        REQUIRE( Approx( 6.0 ) == c(1, 1) );

        c = a - b;
        REQUIRE( Approx( -7.0 ) == c(0, 0) );
        REQUIRE( Approx( -4.0 ) == c(0, 1) );
        REQUIRE( Approx( -1.0 ) == c(1, 0) );
        REQUIRE( Approx( 2.0 ) == c(1, 1) );

        c = -a;
        REQUIRE( Approx( -1.0 ) == c(0, 0) );
        REQUIRE( Approx( -2.0 ) == c(0, 1) );
        REQUIRE( Approx( -3.0 ) == c(1, 0) );
        REQUIRE( Approx( -4.0 ) == c(1, 1) );

        c = a;
        c += b;
        REQUIRE( Approx( 9.0 ) == c(0, 0) );
        REQUIRE( Approx( 8.0 ) == c(0, 1) );
        REQUIRE( Approx( 7.0 ) == c(1, 0) );
        REQUIRE( Approx( 6.0 ) == c(1, 1) );

        c = a;
        c -= b;
        REQUIRE( Approx( -7.0 ) == c(0, 0) );
        REQUIRE( Approx( -4.0 ) == c(0, 1) );
        REQUIRE( Approx( -1.0 ) == c(1, 0) );
        REQUIRE( Approx( 2.0 ) == c(1, 1) );

        c = a * s;
        REQUIRE( Approx( 2.0 ) == c(0, 0) );
        REQUIRE( Approx( 4.0 ) == c(0, 1) );
        REQUIRE( Approx( 6.0 ) == c(1, 0) );
        REQUIRE( Approx( 8.0 ) == c(1, 1) );

        c = s * a;
        REQUIRE( Approx( 2.0 ) == c(0, 0) );
        REQUIRE( Approx( 4.0 ) == c(0, 1) );
        REQUIRE( Approx( 6.0 ) == c(1, 0) );
        REQUIRE( Approx( 8.0 ) == c(1, 1) );

        c = a;
        c *= s;
        REQUIRE( Approx( 2.0 ) == c(0, 0) );
        REQUIRE( Approx( 4.0 ) == c(0, 1) );
        REQUIRE( Approx( 6.0 ) == c(1, 0) );
        REQUIRE( Approx( 8.0 ) == c(1, 1) );

        c = a / s;
        REQUIRE( Approx( 0.5 ) == c(0, 0) );
        REQUIRE( Approx( 1.0 ) == c(0, 1) );
        REQUIRE( Approx( 1.5 ) == c(1, 0) );
        REQUIRE( Approx( 2.0 ) == c(1, 1) );

        c = a;
        c /= s;
        REQUIRE( Approx( 0.5 ) == c(0, 0) );
        REQUIRE( Approx( 1.0 ) == c(0, 1) );
        REQUIRE( Approx( 1.5 ) == c(1, 0) );
        REQUIRE( Approx( 2.0 ) == c(1, 1) );

        c = a * b;
        REQUIRE( Approx( 16.0 ) == c(0, 0) );
        REQUIRE( Approx( 10.0 ) == c(0, 1) );
        REQUIRE( Approx( 40.0 ) == c(1, 0) );
        REQUIRE( Approx( 26.0 ) == c(1, 1) );

        c = a;
        c *= b;
        REQUIRE( Approx( 16.0 ) == c(0, 0) );
        REQUIRE( Approx( 10.0 ) == c(0, 1) );
        REQUIRE( Approx( 40.0 ) == c(1, 0) );
        REQUIRE( Approx( 26.0 ) == c(1, 1) );

        c = a.transpose();
        REQUIRE( Approx( 1.0 ) == c(0, 0) );
        REQUIRE( Approx( 3.0 ) == c(0, 1) );
        REQUIRE( Approx( 2.0 ) == c(1, 0) );
        REQUIRE( Approx( 4.0 ) == c(1, 1) );

        c = a.conjugate();
        REQUIRE( Approx( 1.0 ) == c(0, 0) );
        REQUIRE( Approx( 2.0 ) == c(0, 1) );
        REQUIRE( Approx( 3.0 ) == c(1, 0) );
        REQUIRE( Approx( 4.0 ) == c(1, 1) );

        c2 = c1.conjugate();
        REQUIRE( Approx( 1.0 ) == c2(0, 0).real() );
        REQUIRE( Approx( 2.0 ) == c2(0, 1).real() );
        REQUIRE( Approx( 3.0 ) == c2(1, 0).real() );
        REQUIRE( Approx( 4.0 ) == c2(1, 1).real() );
        REQUIRE( Approx( -1.0 ) == c2(0, 0).imag() );
        REQUIRE( Approx( -2.0 ) == c2(0, 1).imag() );
        REQUIRE( Approx( -3.0 ) == c2(1, 0).imag() );
        REQUIRE( Approx( -4.0 ) == c2(1, 1).imag() );

        x = a * v;
        REQUIRE( Approx( 5.0 ) == x(0) );
        REQUIRE( Approx( 11.0 ) == x(1) );
      }
    }
  }
}

SCENARIO("Matrix inversion ", "[math], [Matrix]"){

  GIVEN("a matrix inversion function") {

    WHEN("using the matrix inversion") {

      math::API::Matrix<double> a(2, 2);
      math::API::Matrix<double> inverse(2, 2);
      math::API::Matrix<double> s(2, 2);

      THEN("gives the correct result for the identity matrix") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [inversion] No Errors Expected";

        a(0, 0) = 1.0;
        a(0, 1) = 0.0;
        a(1, 0) = 0.0;
        a(1, 1) = 1.0;
        s(0, 0) = 1.0;
        s(0, 1) = 0.0;
        s(1, 0) = 0.0;
        s(1, 1) = 1.0;

        inverse = a.inverse();
        REQUIRE( Approx( inverse(0, 0) ) == s(0, 0) );
        REQUIRE( Approx( inverse(0, 1) ) == s(0, 1) );
        REQUIRE( Approx( inverse(1, 0) ) == s(1, 0) );
        REQUIRE( Approx( inverse(1, 1) ) == s(1, 1) );
      }

      THEN("gives the correct result for an arbitrary 2 by 2 matrix") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [inversion] No Errors Expected";

        a(0, 0) = 4.0;
        a(0, 1) = 1.0;
        a(1, 0) = 3.0;
        a(1, 1) = 2.0;
        double det = a(0, 0) * a(1, 1) - a(0, 1) * a(1, 0);
        s(0, 0) = a(1, 1);
        s(0, 1) = -a(0, 1);
        s(1, 0) = -a(1, 0);
        s(1, 1) = a(0, 0);
        s /= det;

        inverse = a.inverse();
        REQUIRE( Approx( inverse(0, 0) ) == s(0, 0) );
        REQUIRE( Approx( inverse(0, 1) ) == s(0, 1) );
        REQUIRE( Approx( inverse(1, 0) ) == s(1, 0) );
        REQUIRE( Approx( inverse(1, 1) ) == s(1, 1) );
      }

      THEN("gives the correct result for a 5 by 5 matrix") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [inversion] No Errors Expected";

        a.resize(5, 5);
        a(0, 0) = 4.0; a(0, 1) = 0.0; a(0, 2) = 0.0; a(0, 3) = 0.0; a(0, 4) = 0.0;
        a(1, 0) = 0.0; a(1, 1) = 8.0; a(1, 2) = 0.0; a(1, 3) = 0.0; a(1, 4) = 0.0;
        a(2, 0) = 0.0; a(2, 1) = 0.0; a(2, 2) = 2.0; a(2, 3) = 0.0; a(2, 4) = 0.0;
        a(3, 0) = 0.0; a(3, 1) = 0.0; a(3, 2) = 0.0; a(3, 3) = 1.0; a(3, 4) = 0.0;
        a(4, 0) = 0.0; a(4, 1) = 0.0; a(4, 2) = 0.0; a(4, 3) = 0.0; a(4, 4) = 10.0;
        s.resize(5, 5);
        s = a;
        s(0, 0) = 0.25;
        s(1, 1) = 0.125;
        s(2, 2) = 0.5;
        s(3, 3) = 1.0;
        s(4, 4) = 0.1;

        inverse = a.inverse();
        for (unsigned int i = 0; i < inverse.rows(); ++i) {

          for (unsigned int j = 0; j < inverse.cols(); ++j) {

            REQUIRE( Approx( inverse(i, j) ) == s(i, j) );
          }
        }
      }

      THEN("gives the correct result for a 5 by 5 block matrix") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [inversion] No Errors Expected";

        a.resize(5, 5);
        a(0, 0) = 3.0;  a(0, 1) = 2.0;  a(0, 2) = 0.0;  a(0, 3) = 0.0;  a(0, 4) = 0.0;
        a(1, 0) = 4.0;  a(1, 1) = 3.0;  a(1, 2) = 0.0;  a(1, 3) = 0.0;  a(1, 4) = 0.0;
        a(2, 0) = 0.0;  a(2, 1) = 0.0;  a(2, 2) = 6.0;  a(2, 3) = 5.0;  a(2, 4) = 0.0;
        a(3, 0) = 0.0;  a(3, 1) = 0.0;  a(3, 2) = 7.0;  a(3, 3) = 6.0;  a(3, 4) = 0.0;
        a(4, 0) = 0.0;  a(4, 1) = 0.0;  a(4, 2) = 0.0;  a(4, 3) = 0.0;  a(4, 4) = 1.0;
        s.resize(5, 5);
        s(0, 0) = 3.0;  s(0, 1) = -2.0; s(0, 2) = 0.0;  s(0, 3) = 0.0;  s(0, 4) = 0.0;
        s(1, 0) = -4.0; s(1, 1) = 3.0;  s(1, 2) = 0.0;  s(1, 3) = 0.0;  s(1, 4) = 0.0;
        s(2, 0) = 0.0;  s(2, 1) = 0.0;  s(2, 2) = 6.0;  s(2, 3) = -5.0; s(2, 4) = 0.0;
        s(3, 0) = 0.0;  s(3, 1) = 0.0;  s(3, 2) = -7.0; s(3, 3) = 6.0;  s(3, 4) = 0.0;
        s(4, 0) = 0.0;  s(4, 1) = 0.0;  s(4, 2) = 0.0;  s(4, 3) = 0.0;  s(4, 4) = 1.0;

        inverse = a.inverse();
        for (unsigned int i = 0; i < inverse.rows(); ++i) {

          for (unsigned int j = 0; j < inverse.cols(); ++j) {

            REQUIRE( Approx( inverse(i, j) ) == s(i, j) );
          }
        }
      }
    }
  }
}
