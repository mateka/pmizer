project (pmizer_cmd)

file(GLOB SRCS "*.cpp")

add_executable(pmize ${SRCS})
target_link_libraries(pmize libpmizer libxmp ${Boost_LIBRARIES})
set_property(TARGET pmize PROPERTY CXX_STANDARD 14)