if(${verbose_traversal})
  message(STATUS "Entered API directory")
endif(${verbose_traversal})

set(headers "")
list(APPEND headers
  "BivariateProbabilityDistribution"
  "InterpolationRegion"
  "InterpolationRegionIntegral"
  "ProbabilityDistribution"
  "SeriesExpansion"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${math_HEADER_DIR}/API/${header}.hpp"
    COPYONLY
    )
  list(APPEND math_src_headers
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    )
  list(APPEND math_bin_headers
    "${math_HEADER_DIR}/API/${header}.hpp"
    )
endforeach(header)

set(math_src "${math_src}" PARENT_SCOPE)
set(math_src_headers "${math_src_headers}" PARENT_SCOPE)
set(math_bin_headers "${math_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting API directory")
endif(${verbose_traversal})


