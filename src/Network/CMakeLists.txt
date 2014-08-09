project(Network)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
endif(NOT MSVC)

file(GLOB_RECURSE network_src_files *.cpp)
file(GLOB_RECURSE network_hdr_files *.h)

add_library(Network STATIC ${network_src_files} ${network_hdr_files})

add_dependencies(Network NetPort)
