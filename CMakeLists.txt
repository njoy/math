cmake_minimum_required( VERSION 3.2 )

set(projectName "math")
set(projectVersion "0.5.0")

if(NOT DEFINED commonCMakeScripts_path)
  set(commonCMakeScripts_path "${CMAKE_SOURCE_DIR}/commonCMakeScripts")
endif(NOT DEFINED commonCMakeScripts_path)

include(subprojects.cmake)
include(${commonCMakeScripts_path}/objectOriented.cmake)
include(${commonCMakeScripts_path}/doxygen.cmake)

# create the utility build tree header directory and immediate children if necessary
if(NOT(EXISTS "${math_HEADER_DIR}/interpolate"))
  file(MAKE_DIRECTORY "${math_HEADER_DIR}/interpolate")
endif(NOT(EXISTS "${math_HEADER_DIR}/interpolate"))

# Initialize a variable for collecting utility implementation components
list(APPEND ${projectName}_src) # (empty list)
list(APPEND ${projectName}_src_headers) # (empty list)
list(APPEND ${projectName}_bin_headers) # (empty list)

set(headers "")
list(APPEND headers
  "interpolate"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in" 
    "${math_HEADER_DIR}/${header}.hpp"
    COPYONLY
    )
  list(APPEND math_src_headers
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in" 
    )
  list(APPEND math_bin_headers
    "${math_HEADER_DIR}/${header}.hpp"
    )
endforeach(header)

# setup test labels
list(APPEND testLabels math)

# traverse subdirectories
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/interpolate" )

include(${commonCMakeScripts_path}/assemble.cmake)
include(${commonCMakeScripts_path}/terminus.cmake)
