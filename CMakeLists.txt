cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# set C++14 as required
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

project(textgen VERSION ${VERSION} LANGUAGES CXX)

# check for flags
INCLUDE(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-Wall" HAVE_WALL)
check_cxx_compiler_flag("-pedantic" HAVE_PEDANTIC)
check_cxx_compiler_flag("-Werror" HAVE_WERROR)
check_cxx_compiler_flag("-Weverything" HAVE_WEVERYTHING)
check_cxx_compiler_flag("-Wno-padded" HAVE_NOPADDED)
check_cxx_compiler_flag("-Wno-c++98-compat" HAVE_NO98COMPAT)
check_cxx_compiler_flag("-Wno-c++98-compat-pedantic" HAVE_NO98COMPAT_PED)
check_cxx_compiler_flag("-Wno-documentation-unknown-command" HAVE_NODOCWARN)

# set available flag
if (HAVE_WALL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()
if (HAVE_PEDANTIC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
endif()
if (HAVE_WEVERYTHING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
endif()
if (HAVE_WERROR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()
if (HAVE_NOPADDED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-padded")
endif()
if (HAVE_NO98COMPAT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat")
endif()
if (HAVE_NO98COMPAT_PED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat-pedantic")
endif()
if (HAVE_NODOCWARN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation-unknown-command")
endif()
message("-- Compiling with flags '${CMAKE_CXX_FLAGS}' on '${CMAKE_CXX_COMPILER_ID}' ${CMAKE_CXX_COMPILER_VERSION}")


# The project version number.
set(VERSION_MAJOR   1   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
add_definitions(-DTEXTGEN_VERSION="${VERSION}")

INCLUDE(CheckIncludeFileCXX)
CHECK_INCLUDE_FILE_CXX("tclap/CmdLine.h" HAVE_TCLAP)

if (NOT HAVE_TCLAP)
    message(FATAL_ERROR "The TCLAP header only library is required, but could not be found!")
endif()

file(COPY rsrc/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES src/markov.cpp)
add_executable(textgen src/main.cpp ${SOURCES})

include_directories(src/)
add_executable(textgen_test test/main.cpp ${SOURCES})