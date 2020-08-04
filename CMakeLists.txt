cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)

if(CMAKE_PROJECT_NAME)
  set(TARGET_NAME TimeMeasure)
else(CMAKE_PROJECT_NAME)
  project (TimeMeasure)
  set(TARGET_NAME ${CMAKE_PROJECT_NAME})
endif(CMAKE_PROJECT_NAME)

find_package (Threads REQUIRED)

add_library(${TARGET_NAME} INTERFACE)
target_include_directories(${TARGET_NAME}
    INTERFACE
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
target_link_libraries(${TARGET_NAME} INTERFACE ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(Examples EXCLUDE_FROM_ALL)


# installation

include(GNUInstallDirs)
install(TARGETS ${TARGET_NAME}
    EXPORT ${TARGET_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${TARGET_NAME}Config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME})
install(FILES "Measurer.h"
              "Histogram.h"
              "CyclicDataOutputterThread.h"
              "OutputterDestinations.h"
              "TimeMeasureTypes.h"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${TARGET_NAME})


install(EXPORT ${TARGET_NAME}-targets
  FILE
    ${TARGET_NAME}Targets.cmake
  NAMESPACE
    ${TARGET_NAME}::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME}
)