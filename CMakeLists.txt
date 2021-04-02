cmake_minimum_required(VERSION 3.12)

project(Cbb VERSION 1.0.0 LANGUAGES CXX)

if (NOT CBB_BUILD_TESTS)
  set(CBB_BUILD_TESTS_DEFAULT "OFF")

  if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    set(CBB_BUILD_TESTS_DEFAULT "ON")
  endif()

  set(CBB_BUILD_TESTS
    ${CBB_BUILD_TESTS_DEFAULT}
    CACHE
    BOOL
    "Toggle building of Ieme tests")
endif()

enable_testing()

add_subdirectory(src)
