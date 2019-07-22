cmake_minimum_required(VERSION 3.0)

project(blackhole)

add_executable(blackhole main.cpp)

install(TARGETS blackhole RUNTIME DESTINATION bin)
