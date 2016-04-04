if(${verbose_traversal})
  message(STATUS "Entered VectorSeries directory")
endif(${verbose_traversal})

# setup test labels
list(APPEND testLabels VectorSeries)

# traverse subdirectories
if(${local_testing})
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set(math_src "${math_src}" PARENT_SCOPE)
set(math_src_headers "${math_src_headers}" PARENT_SCOPE)
set(math_bin_headers "${math_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting VectorSeries directory")
endif(${verbose_traversal})
