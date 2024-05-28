cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SRC LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SRC})

add_executable(${BINARY} ${TEST_SRC})
add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC gtest)