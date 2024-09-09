cmake_minimum_required(VERSION 3.15.0)

project(mirlib LANGUAGES C)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/mir)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# NOTE: `MIR_NO_STD_ALLOCATOR' may also be turned off if using macros that rely
#       on the standard library allocator is not desirable
option(MIR_NO_STD_ALLOCATOR
  "MUST be turned off if a standard library allocator is not available" OFF)
option(MIR_NDEBUG
  "Disable all runtime assertions in mirlib, even if NDEBUG is not defined" OFF)

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.c)
add_library(mir ${SOURCES})
target_include_directories(mir PUBLIC include/)

if(MIR_NO_STD_ALLOCATOR)
  target_compile_definitions(mir PUBLIC MIR_NO_STD_ALLOCATOR)
endif()
if(MIR_NDEBUG)
  target_compile_definitions(mir PUBLIC MIR_NDEBUG)
endif()
