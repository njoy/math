#define CATCH_CONFIG_RUNNER

// other includes
#include "catch.hpp"

// what we're testing
#include "math/API/SparseMatrix.hpp"

int testNumber = 0;

namespace {

  // test variable

}

int main( int argc, const char* argv[] )
{
  LOG(INFO) << "";
  LOG(INFO) << " SparseMatrix Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "SparseMatrix Tests Complete!";
  return result;
}
SCENARIO("SparseMatrix construction ", "[math], [SparseMatrix]"){

  GIVEN("a default constructor"){

    WHEN("constructing a valid SparseMatrix using the default constructor") {

      math::API::SparseMatrix<double> defaultconstructor;
      THEN("the number of columns and rows of the SparseMatrix should be zero") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [construction] No Errors Expected";
        REQUIRE( 0 == defaultconstructor.rows() );
        REQUIRE( 0 == defaultconstructor.cols() );
      }
    }
  }

  GIVEN("a constructor with SparseMatrix sizes") {

    WHEN("constructing a valid SparseMatrix using the constructor with row and colu;mn siwe") {

      math::API::SparseMatrix<double> matrix(3, 4);
      THEN("the size of the matrix should be 3 rows and 4 columns") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [construction] No Errors Expected";
        REQUIRE( 3 == matrix.rows() );
      }
    }
  }

  GIVEN("a copy constructor") {

    WHEN("constructing a valid Matrix using the copy constructor") {

      math::API::SparseMatrix<double> a(2, 2);
      a(0, 0) = 1.0;
      a(0, 1) = 2.0;
      a(0, 0) = 3.0;
      a(0, 1) = 4.0;
      math::API::SparseMatrix<double> copy(a);
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

      math::API::SparseMatrix<double> a(2, 2);
      a(0, 0) = 1.0;
      a(0, 1) = 2.0;
      a(0, 0) = 3.0;
      a(0, 1) = 4.0;
      math::API::SparseMatrix<double> assign;
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

SCENARIO("Matrix resizing ", "[math], [Matrix]"){

  GIVEN("a resize function") {

    WHEN("resizing a valid Matrix using the resize function") {

      math::API::SparseMatrix<double> matrix(2, 3);
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

SCENARIO("Matrix arithmetic ", "[math], [Matrix]"){

  GIVEN("matrix operations: +, -, *, /, dot product and norm") {

    WHEN("using the operations") {

      math::API::SparseMatrix<double> a(2, 2);
      math::API::SparseMatrix<double> b(2, 2);
      math::API::SparseMatrix<double> c(2, 2);
      math::API::SparseMatrix<std::complex<double>> c1(2, 2);
      math::API::SparseMatrix<std::complex<double>> c2(2, 2);
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

// *= operator not implemented for the SparseMatrix
//        c = a;
//        c *= b;
//        REQUIRE( Approx( 16.0 ) == c(0, 0) );
//        REQUIRE( Approx( 10.0 ) == c(0, 1) );
//        REQUIRE( Approx( 40.0 ) == c(1, 0) );
//        REQUIRE( Approx( 26.0 ) == c(1, 1) );

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
