//     Project: EnvSim
//      Module: libenvsim / tcl / track.h
// Description: Tcl interface for management of track messages
//
// History:
// - 23.09.15, J. Kastner: initial version

#ifndef LIBENVSIM_TRACK_H
#define LIBENVSIM_TRACK_H

#include "../utils.h"
#include "../trackmsg.h"

es_Status es_tcl_track_balise(char* subcmd, char* arg, void (*appendResult)(char*,es_ClientData), es_ClientData data);

es_Status es_tcl_track_add(char* subcmd, double pos);

es_Status es_tcl_track_info(void (*appendResult)(char* res, es_ClientData data), es_ClientData data);

#endif //LIBENVSIM_TRACK_H
