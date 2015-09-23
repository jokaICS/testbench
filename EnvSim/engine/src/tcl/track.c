//     Project: EnvSim
//      Module: libenvsim / tcl / track.c
// Description: Tcl interface for management of track messages
//
// History:
// - 23.09.15, J. Kastner: initial version

#include <stdio.h>
#include "track.h"

const size_t es_tcl_track_bmsize = sizeof(CompressedBaliseMessage_TM);

// static buffer reading/writing of balise messages
CompressedBaliseMessage_TM es_tcl_track_balise_buf;

es_Status es_tcl_track_balise_load_raw(char* hexdata) {
  es_hex_to_bytes(es_tcl_track_bmsize,hexdata,(char*)&es_tcl_track_balise_buf);
  return ES_OK;
}

es_Status es_tcl_track_balise(char* subcmd, char* arg) {
  if(!strcmp("raw",subcmd)) {
    return es_tcl_track_balise_load_raw(arg);
  }
  snprintf(es_msg_buf,ES_MSG_BUF_SIZE,"invalid sub command: %s",subcmd);
  return ES_TCL_ERROR;
}

es_Status es_tcl_track_add(char* subcmd, double pos) {
  if(!strcmp("balise",subcmd)) {
    es_add_triggered_balise_message(&es_scripted_tracksim_track,pos,&es_tcl_track_balise_buf);
    return ES_OK;
  }
  snprintf(es_msg_buf,ES_MSG_BUF_SIZE,"invalid sub command: %s",subcmd);
  return ES_TCL_ERROR;
}

