project (libpmizer)

file(GLOB SRCS "src/*.cpp")

add_library(libpmizer ${SRCS})
target_link_libraries(libpmizer ${Boost_LIBRARIES} ${JPEG_LIBRARIES} ${TIFF_LIBRARIES} ${PNG_LIBRARIES})
set_property(TARGET libpmizer PROPERTY CXX_STANDARD 14)