cmake_minimum_required (VERSION 2.6)
project (TimeMeasure)
set (CMAKE_CXX_STANDARD 11)

find_package (Threads REQUIRED)

add_library(${CMAKE_PROJECT_NAME} INTERFACE)
target_include_directories(${CMAKE_PROJECT_NAME}
    INTERFACE
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
target_link_libraries(${CMAKE_PROJECT_NAME} INTERFACE ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(Examples EXCLUDE_FROM_ALL)


# installation

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
    EXPORT ${CMAKE_PROJECT_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${CMAKE_PROJECT_NAME}Config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME})
install(FILES "Measurer.h"
              "Histogram.h"
              "CyclicDataOutputterThread.h"
              "OutputterDestinations.h"
              "TimeMeasureTypes.h"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME})


install(EXPORT ${CMAKE_PROJECT_NAME}-targets
  FILE
    ${CMAKE_PROJECT_NAME}Targets.cmake
  NAMESPACE
    ${CMAKE_PROJECT_NAME}::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}
)