//     Project: EnvSim
//      Module: libenvsim / interp.c
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

void es_free_interp(es_Interp *interp) {
  Jim_FreeInterp(interp);
}

es_Status es_eval_tcl(es_Interp *interp, const char *script) {
  int error = Jim_Eval(interp, script);
  if (error == JIM_ERR) {
    Jim_MakeErrorMessage(interp);
    fprintf(stderr, "%s\n", Jim_GetString(Jim_GetResult(interp), NULL));
    Jim_FreeInterp(interp);
  }
  return error;
}
