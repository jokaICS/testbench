//     Project: EnvSim
//      Module: libenvsim / trackmsg.h
// Description: Representation + triggering of trackside messages (balise telegrams and radio messages)
//
// History:
// - 22.09.15, kastner: 

#include "envsim.h"
#include "trackmsg.h"
#include "scade/ScriptedTrack_EnvSim.h"

static es_ListEntry *es_baliseMsgBuffer = NULL;

void es_queue_balise_message(CompressedBaliseMessage_TM *msg) {
  es_baliseMsgBuffer = es_list_append(es_baliseMsgBuffer,(char*)msg);
}


void es_write_next_balise_message(CompressedBaliseMessage_TM *target) {
  if(es_baliseMsgBuffer==NULL) {
    return;
  }

  CompressedBaliseMessage_TM *src;
  es_baliseMsgBuffer = es_list_remove_head(es_baliseMsgBuffer,&src);

  *target = *src;
}


int es_cmp_tbm(char* tbm1, char* tbm2) {
  es_TriggerPos pos1 = ((es_TriggeredBaliseMessage*)tbm1)->triggerpos;
  es_TriggerPos pos2 = ((es_TriggeredBaliseMessage*)tbm2)->triggerpos;
  if(pos1<pos2) return -1;
  if(pos1>pos2) return 1;
  return 0;
}


void es_add_triggered_balise_message(es_TrackMessages *track, es_TriggerPos pos, CompressedBaliseMessage_TM bmsg) {
  es_TriggeredBaliseMessage *tbm = MALLOC(es_TriggeredBaliseMessage);
  tbm->triggerpos = pos;
  tbm->msg = bmsg;
  track->bmsgs = es_list_insert(track->bmsgs,(char*)tbm,es_cmp_tbm);
}


static es_TrackSimState es_scripted_tracksim_state;
static outC_ScriptedTrack_EnvSim *es_scripted_tracksim_out;

void es_scripted_tracksim_init(outC_ScriptedTrack_EnvSim *out) {
  es_scripted_tracksim_out = out;
  out->baliseMessage.Header.nid_c=42;
  es_scripted_tracksim_state.messages = NULL;
  es_scripted_tracksim_state.prevBmsg = NULL;
  es_scripted_tracksim_state.prevBPos = 0.0;
}
