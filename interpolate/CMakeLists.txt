if(${verbose_traversal})
  message(STATUS "Entered interpolation directory")
endif(${verbose_traversal})

if(NOT(EXISTS "${math_HEADER_DIR}/interpolate/src"))
  file(MAKE_DIRECTORY "${math_HEADER_DIR}/interpolate/src")
endif(NOT(EXISTS "${math_HEADER_DIR}/interpolate/src"))

set(headers "")
list(APPEND headers
  "src/integrate"
  "src/integralInterpolate"
  "src/withIterators"
  "src/constructLinearLinearInterpolationGrid"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${math_HEADER_DIR}/interpolate/${header}.hpp"
    COPYONLY
    )
  list(APPEND math_src_headers
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    )
  list(APPEND math_bin_headers
    "${math_HEADER_DIR}/interpolate/${header}.hpp"
    )
endforeach(header)

if (${local_testing})
  list(APPEND testLabels interpolate)
  add_subdirectory(test)
endif (${local_testing})

list(APPEND math_src
  "${CMAKE_CURRENT_SOURCE_DIR}/src/monotoneCubicSpline.cpp"
  )
set(math_src "${math_src}" PARENT_SCOPE)
set(math_src_headers "${math_src_headers}" PARENT_SCOPE)
set(math_bin_headers "${math_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting interpolation directory")
endif(${verbose_traversal})
