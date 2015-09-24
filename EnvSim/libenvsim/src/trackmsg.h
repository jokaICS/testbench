//     Project: EnvSim
//      Module: libenvsim / trackmsg.h
// Description: Management + triggering of trackside messages (balise telegrams and radio messages)
//
// History:
// - 22.09.15, J. Kastner: initial version

#ifndef ENGINE_TRACKMSG_H
#define ENGINE_TRACKMSG_H

#include "utils.h"
//#include "kcg_types.h"
#include "scade/ScriptedTrack_EnvSim.h"

typedef double es_TriggerPos;

typedef struct {
  es_TriggerPos triggerpos;
  CompressedBaliseMessage_TM msg;
} es_TriggeredBaliseMessage;


typedef struct {
  // linked list with balise messages
  // (in ascending order w.r.t. triggerpos)
  es_ListEntry *bmsgs;
} es_TrackMessages;


typedef struct {
  es_TrackMessages *messages;
  // last passed balise message
  es_ListEntry *prevBmsg;
  // last train position used for triggering of balise messages
  es_TriggerPos prevBPos;
} es_TrackSimState;


extern es_TrackMessages es_scripted_tracksim_track;

// Enqueues a balise message into the output buffer.
// Every time es_write_next_balise_message is called,
// it takes the next message from this buffer.
void es_queue_balise_message(CompressedBaliseMessage_TM *msg);

// Writes the next pending balise message from the buffer to the specified
// target structure (using memcpy). Does nothing if there is no message left
// in the balise message buffer.
void es_write_next_balise_message(CompressedBaliseMessage_TM *target);

// Adds a new balise message to the prvided track at the specified trigger position.
void es_add_triggered_balise_message(es_TrackMessages *track, es_TriggerPos pos, CompressedBaliseMessage_TM *bmsg);

//void es_scripted_tracksim_init(outC_ScriptedTrack_EnvSim *out);

//void es_scripted_tracksim_cycle(outC_ScriptedTrack_EnvSim *out, double actualPos);

void es_exec_tracksim_cycle(es_TrackSimState *state, es_TriggerPos newBPos);

#endif //ENGINE_TRACKMSG_H
