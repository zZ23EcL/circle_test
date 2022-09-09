cmake_minimum_required(VERSION 3.23)
project(circle_test)

set(CMAKE_CXX_STANDARD 14)
find_package(Threads REQUIRED)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        )
include_directories(inc)
aux_source_directory(src SOURCE)
add_executable(circle_test main.cpp ${SOURCE})
target_link_libraries(circle_test PUBLIC ftdipp1 PRIVATE Threads::Threads)