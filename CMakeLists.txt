cmake_minimum_required(VERSION 3.28.3) # may need to change this if you get an error about the CMake version
project(cs3100_sequence)

set(CMAKE_CXX_STANDARD 20)

# Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

get_filename_component(CURRENT_DIR_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
get_filename_component(PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)
get_filename_component(PARENT_DIR_NAME "${PARENT_DIR}" NAME)

if (CURRENT_DIR_NAME STREQUAL "starter" OR CURRENT_DIR_NAME STREQUAL "solution")
    set(TARGET_NAME "${PARENT_DIR_NAME}_${CURRENT_DIR_NAME}")
else ()
    set(TARGET_NAME "${CURRENT_DIR_NAME}")
endif ()

set(TEST_HARNESS_TARGET "${TARGET_NAME}_TestHarness")
set(DEBUG_TARGET "${TARGET_NAME}_Debug")

add_executable(${TEST_HARNESS_TARGET}
        SequenceTestHarness.cpp
        Sequence.cpp
        Sequence.h
        linked_list.h
)

add_executable(${DEBUG_TARGET}
        SequenceDebug.cpp
        Sequence.cpp
        Sequence.h
        linked_list.h
)

target_link_libraries(${TEST_HARNESS_TARGET} gtest_main)
include(GoogleTest)
gtest_discover_tests(${TEST_HARNESS_TARGET})

# Make SequenceDebug the default startup target
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${DEBUG_TARGET})