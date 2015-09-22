cmake_minimum_required(VERSION 3.3)
project(engine)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../Scade/Simulation/ ../Scade/include ../Scade/ jimtcl)


set(SOURCE_FILES
    src/scade/ScriptedTrack_EnvSim.c
    src/scade/ScriptedTrack_EnvSim.h src/interp.c src/interp.h)

add_library(envsim ${SOURCE_FILES})

target_link_libraries(envsim tcl)
#add_executable(engine ${SOURCE_FILES})