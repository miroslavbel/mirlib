cmake_minimum_required(VERSION 3.15.0)

project(mirlib LANGUAGES ASM C)

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

if(MIR_BUILD_CRT0)
  message(WARNING "`MIR_BUILD_CRT0' option is highly experimental")

  if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
      add_library(crt0 OBJECT src/mir/rt/linux/x86_64/crt0.S)
    else()
      message(
        SEND_ERROR "`MIR_BUILD_CRT0' option does not supported for this arch")
    endif() # CMAKE_SYSTEM_PROCESSOR
  else()
    message(SEND_ERROR "`MIR_BUILD_CRT0' option does not supported for this OS")
  endif() # CMAKE_SYSTEM_NAME

  # FIXME: seems like `PREFIX`, `OUTPUT_NAME`, and `SUFFIX` don't work with
  #        Object Libraries. The resulting name should be `crt0.o` not
  #        `crt0.S.o`
  set_target_properties(
    crt0
    PROPERTIES PREFIX ""
               OUTPUT_NAME "crt0"
               SUFFIX ".o")

endif() # MIR_BUILD_CRT0
