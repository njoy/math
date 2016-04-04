if(${verbose_traversal})
  message(STATUS "Entered IteratorTaylorSeries directory")
endif(${verbose_traversal})

set(long_path "${math_HEADER_DIR}/implementation/IteratorTaylorSeries/")

if(NOT(EXISTS "${long_path}/src"))
  file(MAKE_DIRECTORY "${long_path}/src")
endif(NOT(EXISTS "${long_path}/src"))

set(headers "")
list(APPEND headers
  "src/IteratorTaylorSeries"
  "src/eval"
  "src/derivative"
  "src/integral"
  "src/integrate"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in" 
    "${long_path}/${header}.hpp"
    COPYONLY
    )
  list(APPEND math_src_headers
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in" 
    )
  list(APPEND math_bin_headers
    "${long_path}/${header}.hpp"
    )
endforeach(header)

# setup test labels
list(APPEND testLabels IteratorTaylorSeries)

# traverse subdirectories
if(${local_testing})
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set(math_src "${math_src}" PARENT_SCOPE)
set(math_src_headers "${math_src_headers}" PARENT_SCOPE)
set(math_bin_headers "${math_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting IteratorTaylorSeries directory")
endif(${verbose_traversal})
