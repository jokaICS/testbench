#include <stdio.h>
#include "Simulation/Integration.h"
#include <tcl.h>
#include <ossm.h>

extern ossm_scade_Interface* init();

int AppInit(Tcl_Interp *interp) {
  if(Tcl_Init(interp) == TCL_ERROR)
    return TCL_ERROR;
  //if(Tk_Init(interp) == TCL_ERROR)
  //  return TCL_ERROR;


  ossm_scade_Interface *iface = init();
  ossm_tclcmd_register(iface,interp);

  return TCL_OK;
}

int main(int argc, char *argv[]) {
  Tcl_Main(argc,argv,AppInit);
  //Tk_Main(argc,argv,AppInit);
  return 0;
}
