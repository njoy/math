if(${verbose_traversal})
  message(STATUS "Entered Array directory")
endif(${verbose_traversal})

set(headers "")
list(APPEND headers
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${math_HEADER_DIR}/API/Array/${header}.hpp"
    COPYONLY
    )
  list(APPEND math_src_headers
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    )
  list(APPEND math_bin_headers
    "${math_HEADER_DIR}/API/Array/${header}.hpp"
    )
endforeach(header)

if (${local_testing})
  list(APPEND testLabels Array)
  add_subdirectory(test)
endif (${local_testing})

list(APPEND math_src
  )
set(math_src "${math_src}" PARENT_SCOPE)
set(math_src_headers "${math_src_headers}" PARENT_SCOPE)
set(math_bin_headers "${math_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting Array directory")
endif(${verbose_traversal})
