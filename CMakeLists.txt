cmake_minimum_required(VERSION 3.22)
project(CMSC701_A1)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS program_options)

include_directories(${Boost_INCLUDE_DIRS}, include)

add_executable(rsbuild src/rsbuild.cpp
        src/binary_reader.cpp
        src/binary_reader.h
        src/compact_vector.cpp
        src/compact_vector.h
        src/bitvector.cpp
        src/bitvector.h
)
target_link_libraries(rsbuild ${Boost_LIBRARIES})
add_executable(rsquery_rank src/rsquery_rank.cpp
        src/compact_vector.cpp
        src/compact_vector.h
        src/bitvector.cpp
        src/bitvector.h
        src/query_reader.cpp
        src/query_reader.h)
target_link_libraries(rsquery_rank ${Boost_LIBRARIES})
add_executable(rsquery_select src/rsquery_select.cpp
        src/compact_vector.cpp
        src/compact_vector.h
        src/bitvector.cpp
        src/bitvector.h
        src/query_reader.cpp
        src/query_reader.h)
target_link_libraries(rsquery_select ${Boost_LIBRARIES})
add_executable(sarray src/sarray.cpp
        src/compact_vector.cpp
        src/compact_vector.h
        src/bitvector.cpp
        src/bitvector.h
        src/command_reader.cpp
        src/command_reader.h)
target_link_libraries(sarray ${Boost_LIBRARIES})