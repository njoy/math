if(${verbose_traversal})
  message(STATUS "Entered SplicedProbabilityDistribution directory")
endif(${verbose_traversal})

set(long_path "${math_HEADER_DIR}/implementation/SplicedProbabilityDistribution/src")

if(NOT(EXISTS "${long_path}"))
  file(MAKE_DIRECTORY "${long_path}")
endif(NOT(EXISTS "${long_path}"))

set(headers "")
list(APPEND headers
  "SplicedProbabilityDistribution"
  "probabilityDensity"
  "cumulativeProbability"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
  list(APPEND math_src_headers
    "${CMAKE_CURRENT_SOURCE_DIR}/src/${header}.hpp.in"
    )
  list(APPEND math_bin_headers
    "${long_path}/${header}.hpp"
    )
endforeach(header)

# traverse subdirectories
if(${local_testing})
  list(APPEND testLabels SplicedProbabilityDistribution)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set(math_src "${math_src}" PARENT_SCOPE)
set(math_src_headers "${math_src_headers}" PARENT_SCOPE)
set(math_bin_headers "${math_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting SplicedProbabilityDistribution directory")
endif(${verbose_traversal})
