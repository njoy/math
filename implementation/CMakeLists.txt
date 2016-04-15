if(${verbose_traversal})
  message(STATUS "Entered implementation directory")
endif(${verbose_traversal})

set(header_only_subdirs "")
list(APPEND header_only_subdirs
  "IteratorInterpolationRegion"
  "InterpolationRegionIntegral"
  "VectorInterpolationRegion"
  "IteratorTaylorSeries"
  "IteratorLegendreSeries"
  "ProbabilityDistribution"
  "BivariateProbabilityDistribution"
  "SplicedProbabilityDistribution"
  )
set(subdirs "")
list(APPEND subdirs
  ${header_only_subdirs}
  "HeterogeneousInterpolationRegion"
  "VectorSeries"
  )
  
foreach (subdir ${header_only_subdirs})
  if(NOT(EXISTS "${math_HEADER_DIR}/implementation/${subdir}"))
    file(MAKE_DIRECTORY "${math_HEADER_DIR}/implementation/${subdir}")
  endif(NOT(EXISTS "${math_HEADER_DIR}/implementation/${subdir}"))
endforeach (subdir)

set(headers "")
list(APPEND headers
  ${subdirs}
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${math_HEADER_DIR}/implementation/${header}.hpp"
    COPYONLY
    )
  list(APPEND math_src_headers
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    )
  list(APPEND math_bin_headers
    "${math_HEADER_DIR}/implementation/${header}.hpp"
    )
endforeach(header)

foreach (subdir ${subdirs})
  add_subdirectory( ${subdir} )
endforeach (subdir)

set(math_src "${math_src}" PARENT_SCOPE)
set(math_src_headers "${math_src_headers}" PARENT_SCOPE)
set(math_bin_headers "${math_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting implementation directory")
endif(${verbose_traversal})
