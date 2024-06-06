set(target CommonLib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

file(GLOB_RECURSE SRC_COMMON LIST_DIRECTORIES false *.cpp)
set(SOURCES ${SRC_COMMON})
add_library(${target} STATIC ${SRC_COMMON})

target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/extern)

enable_testing()
add_subdirectory(test)