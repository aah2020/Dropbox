project(DropboxClient)

set(BINARY ${PROJECT_NAME})

file(GLOB_RECURSE CLIENT_SRC LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${CLIENT_SRC})

add_executable(${BINARY} ${CLIENT_SRC})
add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC CommonLib)

# set(LIB ${PROJECT_NAME})
add_library(Client STATIC ${CLIENT_SRC})
# target_include_directories(ClientLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../utils/)
