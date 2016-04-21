if(${verbose_traversal})
  message(STATUS "Entered API directory")
endif(${verbose_traversal})

set(headers "")
list(APPEND headers
  "InterpolationTable"
  "InterpolationTableIntegral"
  "SeriesExpansion"
  "ProbabilityDistribution"
  "ConditionalProbabilityDistribution"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${math_HEADER_DIR}/API/${header}.hpp"
    COPYONLY
    )
endforeach(header)

set(math_src "${math_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting API directory")
endif(${verbose_traversal})


