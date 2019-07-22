cmake_minimum_required(VERSION 3.0)

project(blackhole)

include_directories(_header/)

add_executable(blackhole _source/main.cpp _source/basicui.cpp _source/board.cpp _source/engine.cpp _source/game.cpp _source/sstack.cpp )

install(TARGETS blackhole RUNTIME DESTINATION bin)
