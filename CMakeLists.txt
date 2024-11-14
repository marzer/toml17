cmake_minimum_required(VERSION 3.14)

project(
    tomlplusplus
    VERSION 3.4.0
    DESCRIPTION "Header-only TOML config file parser and serializer for C++17"
    HOMEPAGE_URL "https://marzer.github.io/tomlplusplus/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(tomlplusplus_tomlplusplus INTERFACE)
add_library(tomlplusplus::tomlplusplus ALIAS tomlplusplus_tomlplusplus)

set_property(
    TARGET tomlplusplus_tomlplusplus PROPERTY
    EXPORT_NAME tomlplusplus
)

target_include_directories(
  tomlplusplus_tomlplusplus
  ${tomlplusplus_warning_guard} # unquoted for list expansion
  INTERFACE
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(tomlplusplus_tomlplusplus INTERFACE cxx_std_17)

# ---- Install rules, examples, and fuzzing ----
option(TOMLPLUSPLUS_CPP_INSTALL "Enable generation of tomlplusplus install targets" ${PROJECT_IS_TOP_LEVEL})
if (TOMLPLUSPLUS_CPP_INSTALL)
  include(cmake/install-rules.cmake)
endif()
if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." OFF)
  option(BUILD_FUZZER "Build fuzzer." OFF)
  if(BUILD_EXAMPLES)
    add_subdirectory(examples)
  endif()
  if(BUILD_FUZZER AND DEFINED ENV{LIB_FUZZING_ENGINE})
    add_subdirectory(fuzzing)
  endif()
endif()
