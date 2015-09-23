cmake_minimum_required(VERSION 3.3)
project(libenvsim C)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include_directories(../Scade/Simulation/ ../Scade/include ../Scade/ ${JIMTCL})

set(SOURCE_FILES
    src/scade/ScriptedTrack_EnvSim.c src/scade/ScriptedTrack_EnvSim.h
    src/utils.c src/utils.h
    src/interp.c src/interp.h
    src/trackmsg.c src/trackmsg.h
)

add_library(envsim ${SOURCE_FILES})
link_directories(${JIMTCL})
target_link_libraries(envsim jim)

add_executable(main test.c)
target_link_libraries(main envsim)

IF(ENABLE_TESTS)
    add_subdirectory(test/unit)
ENDIF(ENABLE_TESTS)