if(${verbose_traversal})
  message( STATUS "Entered ProbDistLeftInterval directory" )
endif(${verbose_traversal})

set( long_path "${math_HEADER_DIR}/implementation/ProbDistLeftInterval/" )

# traverse subdirectories
if(${local_testing})
  list( APPEND testLabels ProbDistLeftInterval )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set( math_src "${math_src}" PARENT_SCOPE )

if(${verbose_traversal})
  message( STATUS "Exiting ProbDistLeftInterval directory" )
endif(${verbose_traversal})
