//     Project: EnvSim
//      Module: libenvsim / trackmsg.h
// Description: Representation + triggering of trackside messages (balise telegrams and radio messages)
//
// History:
// - 22.09.15, kastner: 

#include "envsim.h"

#define GET_TRIGGERED_BM(list_entry) (list_entry==NULL ? NULL : (es_TriggeredBaliseMessage*)list_entry->data)


static es_ListEntry *es_baliseMsgBuffer = NULL;

void es_queue_balise_message(CompressedBaliseMessage_TM *msg) {
  es_baliseMsgBuffer = es_list_append(es_baliseMsgBuffer,(char*)msg);
}


void es_write_next_balise_message(CompressedBaliseMessage_TM *target) {
  if(es_baliseMsgBuffer==NULL) {
    return;
  }

  CompressedBaliseMessage_TM *src;
  es_baliseMsgBuffer = es_list_remove_head(es_baliseMsgBuffer,(char**)&src);

  *target = *src;
}


int es_cmp_tbm(char* tbm1, char* tbm2) {
  es_TriggerPos pos1 = ((es_TriggeredBaliseMessage*)tbm1)->triggerpos;
  es_TriggerPos pos2 = ((es_TriggeredBaliseMessage*)tbm2)->triggerpos;
  if(pos1<pos2) return -1;
  if(pos1>pos2) return 1;
  return 0;
}


void es_add_triggered_balise_message(es_TrackMessages *track, es_TriggerPos pos, CompressedBaliseMessage_TM *bmsg) {
  es_TriggeredBaliseMessage *tbm = MALLOC(es_TriggeredBaliseMessage);
  tbm->triggerpos = pos;
  memcpy(&tbm->msg,bmsg, sizeof(CompressedBaliseMessage_TM));
  //tbm->msg = *bmsg;
  track->bmsgs = es_list_insert(track->bmsgs,(char*)tbm,es_cmp_tbm);
}

void es_exec_tracksim_cycle(es_TrackSimState *state, es_TriggerPos newBPos) {
  es_ListEntry *next = state->prevBmsg==NULL ? state->messages->bmsgs : state->prevBmsg->tail;

  es_TriggeredBaliseMessage *nextbm = GET_TRIGGERED_BM(next);

  while(nextbm!=NULL && nextbm->triggerpos<=newBPos) {
    es_queue_balise_message(&nextbm->msg);
    nextbm = GET_TRIGGERED_BM(next->tail);
  }
}

//------------------ interface for SCADE ScriptedTrack operator ---------------
static es_TrackSimState es_scripted_tracksim_state;

void es_scripted_tracksim_init(outC_ScriptedTrack_EnvSim *out) {
  es_scripted_tracksim_state.messages = CALLOC(es_TrackMessages);
  es_TrackMessages *track = es_scripted_tracksim_state.messages;

  es_scripted_tracksim_state.prevBmsg = NULL;
  es_scripted_tracksim_state.prevBPos = 0.0;

  track->bmsgs = NULL;

  CompressedBaliseMessage_TM *bm = CALLOC(CompressedBaliseMessage_TM);
  bm->Header.nid_bg = 43;

  es_add_triggered_balise_message(es_scripted_tracksim_state.messages,43,bm);
}

void es_scripted_tracksim_cycle(outC_ScriptedTrack_EnvSim *out, double actualPos, double radioPos) {
  es_exec_tracksim_cycle(&es_scripted_tracksim_state,actualPos);
  es_write_next_balise_message(&out->baliseMessage);
}
