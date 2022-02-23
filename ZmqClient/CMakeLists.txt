cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)


set(TARGET_NAME ZmqSubClient )
add_executable(${TARGET_NAME} "main.cpp")
target_link_libraries(${TARGET_NAME} PRIVATE cppzmq)

install(TARGETS ${TARGET_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)