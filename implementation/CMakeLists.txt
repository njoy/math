if(${verbose_traversal})
  message(STATUS "Entered implementation directory")
endif(${verbose_traversal})

set(header_only_subdirs "")
list(APPEND header_only_subdirs
  "InterpolationTable"
  "InterpolationTableIntegral"
  "TaylorSeries"
  "LegendreSeries"
  "SplicedProbabilityDistribution"
  "ParametricProbabilityDistribution"
  "EquiprobableBinProbabilityDistribution"
  "ProbDistLeftDomainBoundary"
  "ProbDistRightDomainBoundary"
  "ProbDistLeftInterval"
  "ProbDistRightInterval"
  "ConditionalProbabilityDistribution"
  )

set(subdirs "")
list(APPEND subdirs
  ${header_only_subdirs}
  "CompositeInterpolationTable"
  "CompositeInterpolationTableIntegral"
  )
  
foreach (subdir ${header_only_subdirs})
  if(NOT(EXISTS "${math_HEADER_DIR}/implementation/${subdir}"))
    file(MAKE_DIRECTORY "${math_HEADER_DIR}/implementation/${subdir}")
  endif(NOT(EXISTS "${math_HEADER_DIR}/implementation/${subdir}"))
endforeach (subdir)

set(headers "")
list(APPEND headers
  "AccessAbstraction"
  ${subdirs}
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${math_HEADER_DIR}/implementation/${header}.hpp"
    COPYONLY
    )
endforeach(header)

foreach (subdir ${subdirs})
  add_subdirectory( ${subdir} )
endforeach (subdir)

set(math_src "${math_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting implementation directory")
endif(${verbose_traversal})
