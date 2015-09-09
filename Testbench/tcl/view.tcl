package require Tk

source $scriptdir/tachometer.tcl
source $scriptdir/model.tcl
source $scriptdir/ctrl.tcl

image create photo led_red -file "$scriptdir/icons/led_red.gif"
image create photo led_grey -file "$scriptdir/icons/led_grey.gif"
image create photo btn_run -file "$scriptdir/icons/play.gif"
image create photo btn_pause -file "$scriptdir/icons/pause.gif"
image create photo btn_step -file "$scriptdir/icons/step.gif"


wm title . "openETCS Sim"
# .c - content frame
grid [ttk::frame .c -padding 5] -column 0 -row 0 -sticky nwes -padx 5


# frame "Simulation"
grid [ttk::labelframe .c.sim -text "Simulation" -padding 3] -column 0 -row 0 -sticky n
grid [ttk::label .c.sim.ltstamp -text "Time (ms):"] -column 0 -row 1
grid [ttk::label .c.sim.tstamp -textvar ::out_timestamp] -column 1 -row 1
grid [ttk::button .c.sim.reset -text "Reset" -command ctrl::reset] -column 0 -row 2
foreach w [winfo children .c.sim] {grid configure $w -padx 5 -pady 5}


# frame "Desk"
grid [ttk::labelframe .c.desk -text "Desk" -padding 3] -column 1 -row 0 -sticky n
grid [ttk::checkbutton .c.desk.openDesk -text "Open desk" -variable in_openDesk] -columnspan 2

grid [ttk::frame .c.desk.leds] -column 0 -row 1 -columnspan 2
grid [ttk::label .c.desk.leds.eb -compound left -image led_grey -text {Emergency Brake}] -sticky w
trace add variable out_emergencyBrake write "ctrl::update_led .c.desk.leds.eb"
grid [ttk::label .c.desk.leds.sb -compound left -image led_grey -text {Service Brake}] -sticky w
trace add variable out_serviceBrake write "ctrl::update_led .c.desk.leds.sb"

grid [ttk::frame .c.desk.traction] -column 0 -row 2
grid [ttk::label .c.desk.traction.label -text 0]
grid [ttk::scale .c.desk.traction.scale -command ctrl::setTraction -orient vertical -length 80 -from 100.0 -to 0.0]
grid [ttk::label .c.desk.traction.name -text Traction]

grid [ttk::frame .c.desk.brake] -column 1 -row 2
grid [ttk::label .c.desk.brake.label -text 0]
grid [ttk::scale .c.desk.brake.scale -command ctrl::setBrake -orient vertical -length 80 -from 100.0 -to 0.0]
grid [ttk::label .c.desk.brake.name -text Brake]
foreach w [winfo children .c.desk] {grid configure $w -padx 5 -pady 5}

# frame "DMI outputs"
grid [ttk::labelframe .c.dmi -text "DMI outputs" -padding 3] -column 2 -row 0 -sticky n
grid [tachometer::constructor .c.dmi.tacho ::out_currentVelocityInKmH { 0 10 20 30 40 50 60 70 80 90 100 }]

# button row
grid [ttk::frame .c.foot] -column 0 -row 1 -columnspan 3 
grid [ttk::button .c.foot.step -text Step -width 5 -command ctrl::cycle] -row 0 -column 0
grid [ttk::button .c.foot.run -compound left -image btn_run -text Run -command ctrl::run -width 5] -row 0 -column 1

