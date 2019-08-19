cmake_minimum_required(VERSION 3.0)

project(blackhole)

include_directories(_header/)

add_executable(blackhole 
                                _source/main.cpp 
                                _source/basicui.cpp 
                                _source/step_mapping.cpp
                                _source/str_step.cpp
                                _source/board.cpp 
                                _source/engine.cpp 
                                _source/game.cpp 
                                _source/sstack.cpp 
                                _source/chain.cpp
                                _source/data_line.cpp
                                _source/cache.cpp
                                _source/machine_learning.cpp)

install(TARGETS blackhole RUNTIME DESTINATION bin)
