if(${verbose_traversal})
  message(STATUS "Entered API directory")
endif(${verbose_traversal})

set(headers "")
list(APPEND headers
  "ConditionalProbabilityDistribution"
  "Matrix"
  "ProbabilityDistribution"
  "SeriesExpansion"
  "SparseMatrix"
  "InterpolationTable"
  "InterpolationTableIntegral"
  "Vector"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${math_HEADER_DIR}/API/${header}.hpp"
    COPYONLY
    )
endforeach(header)

add_subdirectory( Matrix )
add_subdirectory( SparseMatrix )
add_subdirectory( Vector )

set(math_src "${math_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting API directory")
endif(${verbose_traversal})


