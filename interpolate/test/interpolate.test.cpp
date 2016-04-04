#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "math/interpolate.hpp"

int testNumber = 0;

int main( int argc, char* const argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "interpolate Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "interpolate Tests Complete!";
  return result;
}
