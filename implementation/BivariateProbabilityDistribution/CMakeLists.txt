if(${verbose_traversal})
  message(STATUS "Entered BivariateProbabilityDistribution directory")
endif(${verbose_traversal})

set(long_path "${math_HEADER_DIR}/implementation/BivariateProbabilityDistribution/")

if(NOT(EXISTS "${long_path}/src"))
  file(MAKE_DIRECTORY "${long_path}/src")
endif(NOT(EXISTS "${long_path}/src"))

set(headers "")
list(APPEND headers
  "src/BivariateProbabilityDistribution"
  "src/conditionalProbabilityDensity"
  "src/conditionalCumulativeProbability"
  "src/conditionalProbabilityDistribution"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in" 
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

# traverse subdirectories
if(${local_testing})
  list(APPEND testLabels BivariateProbabilityDistribution)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set(math_src "${math_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting BivariateProbabilityDistribution directory")
endif(${verbose_traversal})
