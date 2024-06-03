project(DropboxServer)

set(BINARY ${PROJECT_NAME})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SERVER_SRC  ${CMAKE_CURRENT_SOURCE_DIR}/src/dropboxServer.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/serverSocket.cpp
)

add_executable(${BINARY}    ${SERVER_SRC}
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(${BINARY} PUBLIC CommonLib stdc++fs)
target_link_libraries(${BINARY} PRIVATE Threads::Threads)
target_include_directories(${BINARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${BINARY} PUBLIC ${CMAKE_SOURCE_DIR}/extern)

set(TARGET_LIB ServerLib)
add_library(${TARGET_LIB} STATIC ${SERVER_SRC})
target_include_directories(${TARGET_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${TARGET_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/src/lib/include)
target_include_directories(${TARGET_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/extern)

# enable_testing()
# add_subdirectory(tests)
