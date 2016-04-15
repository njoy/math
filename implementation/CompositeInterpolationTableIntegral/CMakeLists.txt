if(${verbose_traversal})
  message(STATUS "Entered CompositeInterpolationTableIntegral directory")
endif(${verbose_traversal})

list(APPEND math_src
  "${CMAKE_CURRENT_SOURCE_DIR}/src/CompositeInterpolationTableIntegral.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/buildBoundaries.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/interpolate.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/xGrid.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/yGrid.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/dyGrid.cpp"
  )

# traverse subdirectories
if(${local_testing})
  list(APPEND testLabels CompositeInterpolationTableIntegral)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set(math_src "${math_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting CompositeInterpolationTableIntegral directory")
endif(${verbose_traversal})
