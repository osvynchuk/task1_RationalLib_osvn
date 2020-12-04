cmake_minimum_required(VERSION 3.5)

project(task1_RationalLib_osvn LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task1_RationalLib_osvn main.cpp rational.cpp rational.h)

find_package( Boost REQUIRED)
include_directories( ${Boost_INCLUDE_DIRS} )
target_link_libraries(task1_RationalLib_osvn ${Boost_LIBRARIES} )


##################################
# Download and install GoogleTest

include(ExternalProject)
ExternalProject_Add(gtest
  URL https://github.com/google/googletest/archive/master.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)
message("Gtest source_dir: " ${source_dir})
message("Gtest binary_dir: " ${binary_dir})

################
# Define a test
add_executable(task1_RationalLib_TEST_osvn rational_test.cpp rational.cpp rational.h)

######################################
# Configure the test to use GoogleTest
#
add_dependencies(task1_RationalLib_TEST_osvn gtest)
include_directories(${source_dir}/googletest/include)
target_link_libraries(task1_RationalLib_TEST_osvn ${binary_dir}/lib/libgtest.a)
target_link_libraries(task1_RationalLib_TEST_osvn ${binary_dir}/lib/libgtest_main.a)

##################################
# Just make the test runnable with
#   $ make test

enable_testing()
add_test(NAME    task1_RationalLib_TEST_osvn
         COMMAND task1_RationalLib_TEST_osvn)
