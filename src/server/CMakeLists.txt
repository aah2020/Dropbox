project(DropboxServer)

set(BINARY ${PROJECT_NAME})

file(GLOB_RECURSE SERVER_SRC LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${SERVER_SRC})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${BINARY} ${SERVER_SRC})
add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC CommonLib)
target_link_libraries(${BINARY} PRIVATE Threads::Threads)

# set(LIB ${PROJECT_NAME})
add_library(Server STATIC ${SERVER_SRC})
# target_include_directories(ClientLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../utils/)
