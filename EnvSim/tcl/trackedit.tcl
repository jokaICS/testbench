#     Project: openETCS / EnvSim
#      Module: trackedit (Tcl)
# Description: main tcl script for the track editor UI
# 
# History:
# - 24.09.15, J. Kastner: initial version

set scriptpath "[file dirname [info script]]"

foreach s {view.tcl ctrl.tcl model.tcl} {
  source "$scriptpath/trackedit/$s"
}

load "$scriptpath/../libenvsim/build/Debug/envsim.dylib"

source "track.trk"

view::init
ctrl::loadTree
