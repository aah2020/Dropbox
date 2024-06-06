cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(BINARY ClientTests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${BINARY} ${TEST_SOURCES})
add_test(NAME ${BINARY} COMMAND ${BINARY} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${BINARY} PRIVATE Threads::Threads)
target_link_libraries(${BINARY} PUBLIC ServerLib ClientLib CommonLib gtest stdc++fs)
