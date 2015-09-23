//     Project: EnvSim
//      Module: libenvsim / envsim.h
// Description: Master header for the libenvsim client library
//
// History:
// - 22.09.15, kastner: 

#ifndef ENGINE_ENVSIM_H
#define ENGINE_ENVSIM_H

#define ENVSIM_CLIENT_VERSION "0.1"

#include "utils.h"
#include "tcl/interp.h"
#include "trackmsg.h"

#define ES_MSG_BUF_SIZE 1024

extern char es_msg_buf[];
#define ES_ERROR_MSG(msg) snprintf(es_msg_buf,ES_MSG_BUF_SIZE,"%s",msg);

typedef enum {
  ES_OK,
  ES_TCL_ERROR
} es_Status;

#endif //ENGINE_ENVSIM_H
