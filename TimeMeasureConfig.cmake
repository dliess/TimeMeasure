get_filename_component(TimeMeasure_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(CMakeFindDependencyMacro)

find_dependency(Threads REQUIRED)

if(NOT TARGET TimeMeasure::TimeMeasure)
    include("${TimeMeasure_CMAKE_DIR}/TimeMeasureTargets.cmake")
endif()