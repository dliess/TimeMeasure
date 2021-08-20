cmake_minimum_required (VERSION 2.6)

add_subdirectory(DestinationZmq)

add_executable(TimeMeasureExample main.cpp)
target_link_libraries(TimeMeasureExample TimeMeasure)