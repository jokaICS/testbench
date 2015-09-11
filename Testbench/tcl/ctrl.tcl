namespace eval ctrl {
  variable running false
}

proc ctrl::setTraction {t} {
  set ::in_traction $t
  .c.desk.traction.label configure -text [format "%.0f" $t]
}

proc ctrl::setBrake {b} {
  set ::in_brake $b
  .c.desk.brake.label configure -text [format "%.0f" $b]
}

proc ctrl::cycle {} {
  SSM::cycle
  OSSM::update_link ::out_timestamp ::out_currentVelocityInKmH ::out_emergencyBrake ::out_serviceBrake\
                    ::out_debugMode_raw ::out_debugLevel ::out_debugPermittedSpeed ::out_debugInterventionSpeed
}

proc ctrl::loop {} {
  variable running

  if {! $running} return
  ctrl::cycle
  after 10 ctrl::loop
}

proc ctrl::run {} {
  variable running
  if $running {
    set running false
    .c.foot.step configure -state normal
    .c.foot.run configure -text Run -image btn_run
  } else {
    set running true
    .c.foot.step configure -state disabled
    .c.foot.run configure -text Pause -image btn_pause
  }
  ctrl::loop
}


proc ctrl::reset {} {
  variable running
  set running false
  set in_reset true
}

proc ctrl::update_led {widget args} {
  upvar #0 [lindex $args 0] var
  if $var {
    $widget configure -image led_red
  } else {
    $widget configure -image led_grey
  }
}
    

