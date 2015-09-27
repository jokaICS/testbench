//     Project: openETCS libenvsim
//      Module: scade / scade_track.c
// Description: Implementation of the init and cycle functions for the SCADE ScriptedTrack operator
//
// History:
// - 25.09.15, J. Kastner: initial version

#ifdef WITH_JIM
#include <stdio.h>
#include "../trackmsg.h"
#include "../tcl/interp.h"
#include "../logging.h"

es_TrackSimState es_scripted_tracksim_state = {
  .messages = &es_tracksim_track,
  .prevBmsg = NULL,
  .prevBPos = 0.0
};


void es_scripted_tracksim_init(outC_ScriptedTrack_EnvSim *out) {
  es_log_init(NULL);

  LOG_INFO(scade_track,"Initializing ScriptedTrack");
  char *cfgfile = getenv("OPENETCS_ENVSIM_CONFIG");
  if(cfgfile==NULL) {
    LOG_WARN(scade_track,"Environment variable OPENETCS_ENVSIM_CONFIG not defined; using 'envsim.cfg'\n");
    cfgfile = "envsim.cfg";
  }

  es_Interp *interp = es_get_interp();
  // load configuration
  snprintf(es_msg_buf,ES_MSG_BUF_SIZE,"config::parse \"%s\"",cfgfile);
  es_eval_tcl(interp,es_msg_buf);

  // load track, if defined in configuration
  es_eval_tcl(interp,
     "set trackfile [config::get track];"
     "if {$trackfile eq {}} {log warn scade_track {no track loaded!}} {source $trackfile; log info scade_track {track successfully loaded}}");

  // use loaded track for current simulation
  es_scripted_tracksim_state.messages = &es_tracksim_track;
  LOG_INFO(scade_track,"tracksize: %d\n",es_list_size(es_tracksim_track.bmsgs));
}


void es_scripted_tracksim_cycle(outC_ScriptedTrack_EnvSim *out, double actualPos, double radioPos) {
  es_exec_tracksim_cycle(&es_scripted_tracksim_state,actualPos);
  es_write_next_balise_message(&out->baliseMessage);
}

#endif