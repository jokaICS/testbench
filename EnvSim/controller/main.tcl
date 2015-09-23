
#set scriptdir S:/testbench/EnvSim/controller
set scriptdir "[file dirname [info script]]"

source "$scriptdir/config.tcl"
source "$scriptdir/ui.tcl"
source "$scriptdir/server.tcl"

ui::createApp
srv::start 19999

