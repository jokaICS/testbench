//     Project: EnvSim
//      Module: interp.h
// Description: Custom interface to the Tcl interpreter
//
// History:
// - 22.09.15, J. Kastner: initial version

#ifndef ENGINE_INTERP_H
#define ENGINE_INTERP_H

#include <jim.h>

typedef Jim_Interp es_Interp;

es_Interp* es_init_interp();

#endif //ENGINE_INTERP_H
