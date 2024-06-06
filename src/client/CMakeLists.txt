project(DropboxClient)

message(STATUS "Enabled C++17")

set(BINARY ${PROJECT_NAME})

set(CLIENT_SRC  ${CMAKE_CURRENT_SOURCE_DIR}/src/clientSocket.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/dropboxClient.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${BINARY} ${CLIENT_SRC}  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${BINARY} PUBLIC CommonLib stdc++fs)
target_include_directories(${BINARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${BINARY} PUBLIC ${CMAKE_SOURCE_DIR}/extern)

set(TARGET_LIB ClientLib)
add_library(${TARGET_LIB} STATIC ${CLIENT_SRC})
target_include_directories(${TARGET_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${TARGET_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/src/lib/include)
target_link_libraries(${BINARY} PRIVATE Threads::Threads)
target_include_directories(${TARGET_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/extern)

enable_testing()
add_subdirectory(test)