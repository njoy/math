if(${verbose_traversal})
  message(STATUS "Entered ParametricProbabilityDistribution directory")
endif(${verbose_traversal})

# traverse subdirectories
if(${local_testing})
  list(APPEND testLabels ParametricProbabilityDistribution)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set(math_src "${math_src}" PARENT_SCOPE)
set(math_src_headers "${math_src_headers}" PARENT_SCOPE)
set(math_bin_headers "${math_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting ParametricProbabilityDistribution directory")
endif(${verbose_traversal})
