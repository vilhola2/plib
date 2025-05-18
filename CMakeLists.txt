cmake_minimum_required(VERSION 3.25)
project(plib)
enable_language(C ASM)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS OFF)

# Check compiler vendor and version
if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_C_COMPILER_VERSION VERSION_LESS "18.0")
        message(FATAL_ERROR "Clang 18 or newer is required for full C23 support. Found: ${CMAKE_C_COMPILER_VERSION}")
    endif()
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_C_COMPILER_VERSION VERSION_LESS "14.0")
        message(FATAL_ERROR "GCC 14 or newer is required for full C23 support. Found: ${CMAKE_C_COMPILER_VERSION}")
    endif()
else()
    message(FATAL_ERROR "Unsupported or unknown compiler: ${CMAKE_C_COMPILER_ID}. Full C23 support required.")
endif()

# Detect architecture
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH_LOWER)
if(ARCH_LOWER STREQUAL "amd64")
    set(ARCH "x86_64")
elseif(ARCH_LOWER STREQUAL "x86_64")
    set(ARCH "x86_64")
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

file(GLOB ASM_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/asm/${ARCH}/*.S")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -DNDEBUG")
include_directories(${CMAKE_SOURCE_DIR}/src)
file(GLOB C_SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")

message(STATUS "ASM sources: ${ASM_SOURCES}")
message(STATUS "C sources: ${C_SOURCES}")

add_library(${PROJECT_NAME} ${C_SOURCES} ${ASM_SOURCES})
