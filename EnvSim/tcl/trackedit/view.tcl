#     Project: openETCS / EnvSim
#      Module: trackedit / view.tcl
# Description: Main UI view for trackedit
# 
# History:
# - 24.09.15, J. Kastner: initial version
package require Tk

namespace eval ::view {
  set idValue ""
  set posValue ""
}

proc view::addLabelField {path label var col row} {
  grid [ttk::label ${path}_l -text $label] -column $col -row $row
  grid [ttk::entry ${path}_v -textvariable $var] -column [expr $col + 1] -row $row
}


proc view::init {} {
  wm title . "openETCS TrackEditor"

  grid [ttk::frame .c -padding 5] -sticky nwes

  ### TREE VIEW ###
  grid [ttk::frame .c.nav -padding "0 0 5 0"] -column 0 -row 0 -sticky ns 
  grid [ttk::treeview .c.nav.tree -columns Position]
  set tree .c.nav.tree
  $tree column  #0 -width 100
  $tree heading #0 -text ID
  $tree column  #1 -width 100
  $tree heading #1 -text Position
  bind $tree <<TreeviewSelect>> ctrl::onTreeSelect

  ### DATA PANEL ###
  grid [ttk::frame .c.d] -column 1 -row 0 -sticky nwes
  grid columnconfigure .c.d 2 -minsize 20
  # message ID
  addLabelField .c.d.id ID: view::idValue 0 0
  # position
  addLabelField .c.d.pos Position: view::posValue 3 0
  # table with header values
  grid [ttk::treeview .c.d.headers -columns Value] -column 0 -columnspan 5 -row 1 -pady 10
  set headers .c.d.headers
  $headers heading #0 -text Header
  $headers heading #1 -text Value
}
