cmake_minimum_required(VERSION 2.8)

option(test "Build all tests." ON) # Makes boolean 'test' available.

set(PROJECT_NAME "Design_patterns")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-g -Wall")

# force static runtime libraries for msvc builds
if(MSVC)
  set(variables
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS_MINSIZEREL
  )
  foreach(variable ${variables})
        if(${variable} MATCHES "/MD")
          string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
        endif()
  endforeach()
endif()

#add_library(uri_lib sources/uri.cc)

add_executable(${PROJECT_NAME} main.cpp)
#target_link_libraries(${PROJECT_NAME} uri_lib)

################################
# Testing
################################
if (test)
  add_subdirectory(lib/gtest-1.6.0)
  enable_testing()

  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  add_executable(runUnitTests tests/test.cc)
  target_link_libraries(runUnitTests gtest gtest_main)
#  target_link_libraries(runUnitTests uri_lib)
  add_test(NAME that-test-I-made COMMAND runUnitTests)
  add_test(that-other-test-I-made runUnitTests)
endif()
