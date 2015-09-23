//     Project: EnvSim
//      Module:
// Description: 
//
// History:
// - 22.09.15, kastner: 

#include <stdio.h>
#include "src/interp.h"
#include "src/tcl/client.tcl.h"

void main() {
  es_Interp *interp = es_init_interp();
  es_eval_tcl(interp,es_tcl_client);
  es_eval_tcl(interp,
              "client::connect 127.0.0.1 19999;"
              "client::begin track;"
  );
  es_free_interp(interp);
}