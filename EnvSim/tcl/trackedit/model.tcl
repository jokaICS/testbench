#     Project: openETCS / EnvSim
#      Module: trackedit / model.tcl
# Description: Data model for access to the track messages
# 
# History:
# - 24.09.15, J. Kastner: initial version

namespace eval ::model {}

proc model::getMessageList {} {
  foreach msg [track::info] {
    set rec [list b[lindex $msg 1] "BG [lindex $msg 2]" [lindex $msg 3]]
    lappend data $rec
  }
  return $data
}

proc model::getMessage {id} {
  switch -regexp -matchvar i -- $id {
    b(\\d+) { return [getBaliseMessage [lindex $i 1]] }
    default { error "invalid message index $id" }
  }
}

proc model::getBaliseMessage {id} {
  track::balise load $id
  foreach h [track::balise get header] {
    dict set msg header [lindex $h 0] [lindex $h 1]
  }
  return $msg
}
