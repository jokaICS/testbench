//     Project: EnvSim
//      Module: libenvsim / tcl / track.h
// Description: Tcl interface for management of track messages
//
// History:
// - 23.09.15, J. Kastner: initial version

#ifndef LIBENVSIM_TRACK_H
#define LIBENVSIM_TRACK_H
#include "../envsim.h"

es_Status es_tcl_track_balise(char* subcmd, char* arg);

es_Status es_tcl_track_add(char* subcmd, double pos);

#endif //LIBENVSIM_TRACK_H
