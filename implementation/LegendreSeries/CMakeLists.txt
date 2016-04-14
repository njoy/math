if(${verbose_traversal})
  message(STATUS "Entered LegendreSeries directory")
endif(${verbose_traversal})

set(long_path "${math_HEADER_DIR}/implementation/LegendreSeries/")

if(NOT(EXISTS "${long_path}/src"))
  file(MAKE_DIRECTORY "${long_path}/src")
endif(NOT(EXISTS "${long_path}/src"))

set(headers "")
list(APPEND headers
  "src/LegendreSeries"
  "src/evaluate"
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

# traverse subdirectories
if(${local_testing})
  list(APPEND testLabels LegendreSeries)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set(math_src "${math_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting LegendreSeries directory")
endif(${verbose_traversal})
