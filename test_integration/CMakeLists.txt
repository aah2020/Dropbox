cmake_minimum_required(VERSION 3.17)

set(BINARY ${CMAKE_PROJECT_NAME}_Integration_Test)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

SET(TEST_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GTestMain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/singleFileAdditionTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/multipleFilesAdditionTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/filesAndDirectoryAdditionTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fileDeletionTest.cpp)
add_executable(${BINARY} ${TEST_SRC})
add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PRIVATE Threads::Threads)
target_link_libraries(${BINARY} PUBLIC ServerLib ClientLib CommonLib gtest stdc++fs)
target_include_directories(${BINARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)