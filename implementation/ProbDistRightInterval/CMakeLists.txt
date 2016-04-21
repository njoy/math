if(${verbose_traversal})
  message( STATUS "Entered ProbDistRightInterval directory" )
endif(${verbose_traversal})

set( long_path "${math_HEADER_DIR}/implementation/ProbDistRightInterval/" )

# traverse subdirectories
if(${local_testing})
  list( APPEND testLabels ProbDistRightInterval )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set( math_src "${math_src}" PARENT_SCOPE )

if(${verbose_traversal})
  message( STATUS "Exiting ProbDistRightInterval directory" )
endif(${verbose_traversal})
