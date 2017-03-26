project (pmizer)

cmake_minimum_required (VERSION 3.6)
cmake_policy(VERSION 3.6)

# Find jpeg library
find_package(JPEG REQUIRED)

# Find Boost
find_package(Boost 1.63 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# Add project library
include_directories("${PROJECT_SOURCE_DIR}/libpmizer/include")

add_subdirectory(libpmizer)
add_subdirectory(pmizer_cmd)
