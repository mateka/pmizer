project (libxmp)

file(GLOB SRCS "src/*.cpp")

add_library(libxmp ${SRCS})
target_link_libraries(libxmp ${JPEG_LIBRARIES} XMPCoreStatic XMPFilesStatic)
set_property(TARGET libxmp PROPERTY CXX_STANDARD 14)