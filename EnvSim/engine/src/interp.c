//     Project: EnvSim
//      Module: interp.c
// Description: Custom interface to the Tcl interpreter
//
// History:
// - 22.09.15, J. Kastner: initial version

#include "interp.h"

es_Interp* es_init_interp() {
  es_Interp *interp = NULL;

  interp = Jim_CreateInterp();
  Jim_RegisterCoreCommands(interp);
  Jim_InitStaticExtensions(interp);

  return interp;
}
