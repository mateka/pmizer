project (pmizer_cmd)


add_executable(pmize main.cpp)
target_link_libraries(pmize libpmizer libxmp ${Boost_LIBRARIES})
set_property(TARGET pmize PROPERTY CXX_STANDARD 14)