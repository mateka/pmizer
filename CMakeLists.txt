project (pmizer)

cmake_minimum_required (VERSION 3.6)
cmake_policy(SET CMP0003 NEW)

#add_definitions("/std:c++latest")

# Find image libraries
find_package(JPEG REQUIRED)
find_package(TIFF REQUIRED)
find_package(PNG REQUIRED)

# Find Boost
find_package(Boost 1.63 REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# XMP Toolkit
if(CMAKE_CL_64)
	set(XMP_Toolkit_ARCH "_x64")
endif(CMAKE_CL_64)
include_directories("${PROJECT_SOURCE_DIR}/../XMP-Toolkit-SDK-CC201607/public/include")
link_directories("${PROJECT_SOURCE_DIR}/../XMP-Toolkit-SDK-CC201607/public/libraries/windows${XMP_Toolkit_ARCH}/${CMAKE_BUILD_TYPE}")

# Add project libraries
include_directories("${PROJECT_SOURCE_DIR}/libpmizer/include")
include_directories("${PROJECT_SOURCE_DIR}/libxmp/include")

add_definitions(-D_USE_MATH_DEFINES)

add_subdirectory(libpmizer)
add_subdirectory(libxmp)
add_subdirectory(pmizer_cmd)
