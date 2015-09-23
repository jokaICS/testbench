package require Tk
#package require BWidget

namespace eval ::ui {
}

proc ui::createApp {} {
  wm title . "openETCS SimEnv Controller"

  #grid [ttk::panedwindow .c -orient vertical] -column 0 -row 0 -sticky nwes 
  grid [ttk::frame .c -padding 10] -column 0 -row 0 -sticky nwes 

  # Configuration
  grid [ttk::labelframe .c.config -text Configuration] -column 0 -row 0 -pady 10
  grid [tk::text .c.config.area -height 10 -yscrollcommand ".c.config.sb set"] -column 0 -row 0
  grid [ttk::scrollbar .c.config.sb -command ".c.config.area yview" -orient vertical] -column 1 -row 0 -sticky ns

  # Log area
  grid [ttk::labelframe .c.log -text Log] -column 0 -row 1
  grid [tk::text .c.log.area -state disabled -height 10 -yscrollcommand ".c.log.sb set"] -column 0 -row 0
  grid [ttk::scrollbar .c.log.sb -command ".c.log.area yview" -orient vertical] -column 1 -row 0 -sticky ns
  .c.log.area tag configure error -foreground red
}


proc ui::log {id msg {type info}} {
  .c.log.area configure -state normal
  .c.log.area insert end "\[$id\]: $msg\n" $type
  .c.log.area configure -state disabled
  .c.log.area see end
}

proc ui::getconfig {} {
  set config [.c.config.area get 1.0 end]
  return "$config"
}
