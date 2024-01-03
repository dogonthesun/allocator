cmake_minimum_required(VERSION 3.10)

set(TARGET helloworld_cli)

set(PATCH_VERSION 1 CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

### Exec

project(${TARGET} VERSION ${PROJECT_VERSION})

configure_file(include/config.h.in include/config.h)

file(GLOB SRC_FILES src/*.cpp)

add_executable(${TARGET} ${SRC_FILES})
target_include_directories(${TARGET} PRIVATE "${CMAKE_BINARY_DIR}/include")

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

### Tests

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB SRC_TEST_FILES tests/*.cpp)

add_executable(${TARGET}_test ${SRC_TEST_FILES})
target_include_directories(${TARGET}_test PRIVATE "${CMAKE_BINARY_DIR}/include")

set_target_properties(${TARGET}_test PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
    ${TARGET}_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET}_test)

### Package

install(TARGETS ${TARGET} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "ohhdl@dalailama.com")

include(CPack)
