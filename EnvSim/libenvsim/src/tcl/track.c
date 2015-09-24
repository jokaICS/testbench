//     Project: EnvSim
//      Module: libenvsim / tcl / track.c
// Description: Tcl interface for management of track messages
//
// History:
// - 23.09.15, J. Kastner: initial version

#include <stdio.h>
#include "track.h"
#include "../trackmsg.h"

const size_t es_tcl_track_bmsize = sizeof(CompressedBaliseMessage_TM);

// static buffer reading/writing of balise messages
CompressedBaliseMessage_TM es_tcl_track_balise_buf;

es_Status es_tcl_track_balise_load_raw(char* hexdata) {
  es_hex_to_bytes(es_tcl_track_bmsize,hexdata,(char*)&es_tcl_track_balise_buf);
  return ES_OK;
}

es_Status es_tcl_track_balise_load_index(int i) {
  es_ListEntry *e = es_list_get(es_scripted_tracksim_track.bmsgs,i);

  if(e==NULL) {
    snprintf(es_msg_buf,ES_MSG_BUF_SIZE,"invalid balise index=%d",i);
    return ES_TCL_ERROR;
  }

  es_tcl_track_balise_buf = ((es_TriggeredBaliseMessage*)e->data)->msg;
  return ES_OK;
}


// retrieve data values from the balise message buffer
es_Status es_tcl_track_balise_get(char* subcmd, void (*appendResult)(char*, es_ClientData), es_ClientData data) {
  CompressedBaliseMessage_TM *bm = &es_tcl_track_balise_buf;

  if(!strcmp("header",subcmd)) {
    snprintf(es_msg_buf, ES_MSG_BUF_SIZE,
             "{nid_bg %d} {n_total %d} {m_dup %d} {m_mcount %d} {m_version %d} "
             "{nid_c %d} {q_link %d} {q_media %d} {q_updown %d}",
             bm->Header.nid_bg,
             bm->Header.n_total,
             bm->Header.m_dup,
             bm->Header.m_mcount,
             bm->Header.m_version,
             bm->Header.nid_c,
             bm->Header.q_link,
             bm->Header.q_media,
             bm->Header.q_updown);
    appendResult(es_msg_buf, data);
    return ES_OK;
  }
  snprintf(es_msg_buf,ES_MSG_BUF_SIZE,"invalid sub command '%s': expected 'header'",subcmd);
  return ES_TCL_ERROR;
}


es_Status es_tcl_track_balise(char* subcmd, char* arg, void (*appendResult)(char*,es_ClientData), es_ClientData data) {
  if(!strcmp("load",subcmd)) {
    return es_tcl_track_balise_load_index(atoi(arg));
  }
  if(!strcmp("raw",subcmd)) {
    return es_tcl_track_balise_load_raw(arg);
  }
  if(!strcmp("get",subcmd)) {
    return es_tcl_track_balise_get(arg,appendResult,data);
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


es_Status es_tcl_track_info(void (*appendResult)(char* res, es_ClientData data), es_ClientData data) {
  es_ListEntry *next = es_scripted_tracksim_track.bmsgs;
  while(next!=NULL) {
    es_TriggeredBaliseMessage *bm = (es_TriggeredBaliseMessage*)next->data;
    snprintf(es_msg_buf,ES_MSG_BUF_SIZE,"{b %d %f} ",bm->msg.Header.nid_bg,bm->triggerpos);
    appendResult(es_msg_buf,data);

    next = next->tail;
  }
  return ES_OK;
}
