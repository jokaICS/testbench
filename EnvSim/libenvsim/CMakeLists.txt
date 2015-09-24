cmake_minimum_required(VERSION 3.3)
project(libenvsim C)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include_directories(../Scade/Simulation/ ../Scade/include ../Scade/ ${JIMTCL})

set(SOURCE_FILES
  src/scade/ScriptedTrack_EnvSim.c src/scade/ScriptedTrack_EnvSim.h
  src/utils.c src/utils.h
  src/tcl/interp.c src/tcl/interp.h
  src/trackmsg.c src/trackmsg.h
  src/tcl/envsimInt.c src/tcl/envsimInt.h
  src/tcl/track.c src/tcl/track.h
)

add_library(envsim STATIC ${SOURCE_FILES})


IF(WITH_TCL_EXTENSION)
  add_compile_options(-DWITH_TCL_EXTENSION)
  add_library(envsimext SHARED ${SOURCE_FILES})
  target_link_libraries(envsimext tcl)
  set_target_properties(envsimext PROPERTIES PREFIX "" OUTPUT_NAME envsim)
ENDIF(WITH_TCL_EXTENSION)


IF(WITH_JIM)
  add_compile_options(-DWITH_JIM)
  link_directories(${JIMTCL})
  target_link_libraries(envsim jim)
ENDIF(WITH_JIM)


IF(ENABLE_TESTS)
  #add_executable(main test.c)
  #target_link_libraries(main envsim)
    add_subdirectory(test/unit)
ENDIF(ENABLE_TESTS)