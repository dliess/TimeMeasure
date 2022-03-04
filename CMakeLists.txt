cmake_minimum_required (VERSION 3.11)

project(TimeMeasure
        VERSION 1.0.0
        LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)

set(TARGET_NAME ${PROJECT_NAME})

find_package (Threads REQUIRED)

add_library(${TARGET_NAME} INTERFACE)
target_include_directories(${TARGET_NAME}
    INTERFACE
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>"
      "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)
target_link_libraries(${TARGET_NAME} INTERFACE ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(Examples EXCLUDE_FROM_ALL)

set(FIND_CPPZMQ_DEPENDENCY "")

option(WITH_ZMQ "With Zmq" ON)
include(cmake/CPM.cmake)
if(${WITH_ZMQ})
  CPMFindPackage(
    NAME cppzmq
    GITHUB_REPOSITORY zeromq/cppzmq
    VERSION 4.7.0
    OPTIONS
      "CPPZMQ_BUILD_TESTS OFF"
  )
  target_link_libraries(${TARGET_NAME} INTERFACE cppzmq)
  add_subdirectory(ZmqClient)
  set(FIND_CPPZMQ_DEPENDENCY "find_dependency(cppzmq REQUIRED)")
endif()

# installation
set(HEADERS
  "Measurer.h"
  "Histogram.h"
  "CyclicDataOutputterThread.h"
  "OutputterDestinations.h"
  "OutputterDestinationsZmq.h"
  "TimeMeasureTypes.h"
)

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}  EXPORT ${PROJECT_NAME}-targets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install(EXPORT ${PROJECT_NAME}-targets
  NAMESPACE  ${PROJECT_NAME}::
  DESTINATION  "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

configure_file(cmake/${PROJECT_NAME}Config.cmake.in cmake/${PROJECT_NAME}Config.cmake @ONLY)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config-version.cmake" COMPATIBILITY SameMajorVersion)
install(FILES 
           "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
           "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config-version.cmake" 
        DESTINATION 
           "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")