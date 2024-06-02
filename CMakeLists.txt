cmake_minimum_required(VERSION 3.17)
project(Dropbox LANGUAGES CXX)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

set(CMAKE_BUILD_TYPE Debug)

option(ENABLE_CPPCHECK "Run CppCheck static code analysis" OFF)
option(ENABLE_CLANG_TIDY "Run ClangTidy on for code fomatting" ON)
option(ENABLE_COVERAGE "Run Coverage on for test coverage" OFF)
option(ENABLE_CCACHE "Run ccache on for caching" OFF)

if(ENABLE_CPPCHECK)
    find_program(CPPCHECK cppcheck)
    if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK
        ${CPPCHECK}
        --suppress=syntaxError
        --suppress=missingIncludeSystem
        --enable=all
        --inconclusive
        --suppress=*:*json.hpp
        --suppress=*:*log.hpp
        --suppress=*:*optionparser.h)
    else()
    message(SEND_ERROR "cppcheck requested but executable not found")
    endif()
endif()

# set(CPPCHECK_EXCLUDES
#     ${CMAKE_SOURCE_DIR}/extern/
#     ${CMAKE_BINARY_DIR}/
# )

if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
    else()
    message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()
endif()

if (ENABLE_COVERAGE)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
    find_package(codecov)
    add_coverage(ClaraTests)
    list(APPEND LCOV_REMOVE_PATTERNS "/usr/")
    coverage_evaluate()
endif()

if(ENABLE_CCACHE)
    find_program(CCACHE ccache)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

enable_testing()
add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(test_integration)


message("\n")
message("#########################################")
message("\t \t Summary")
message("#########################################")
message("Build type:       \t ${CMAKE_BUILD_TYPE}")
message("Install prefix:   \t ${CMAKE_INSTALL_PREFIX}")
message("Testing enabled:  \t ${ENABLE_TESTING}")
message("Clang-tidy:       \t ${ENABLE_CLANG_TIDY}")
message("Cppcheck:         \t ${ENABLE_CPPCHECK}")
message("Compiler:         \t ${CMAKE_CXX_COMPILER_ID}")
message("CCache executable:\t ${ENABLE_CCACHE}")
message("Building doc:     \t ${BUILD_DOC}")
message("------------------------------------------")
message("Version:          \t ${PROJECT_VERSION}")
message("########################################")