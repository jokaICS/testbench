# tachometer.tcl --
# 
# Part of: The TCL'ers Wiki
# Contents: a tachometer-like widget
# Date: Fri Jun 13, 2003
# 
# Abstract
# 
# 
# 
# Copyright (c) 2003 Marco Maggi
# 
# The author  hereby grant permission to use,  copy, modify, distribute,
# and  license this  software  and its  documentation  for any  purpose,
# provided that  existing copyright notices  are retained in  all copies
# and that  this notice  is included verbatim  in any  distributions. No
# written agreement, license, or royalty  fee is required for any of the
# authorized uses.  Modifications to this software may be copyrighted by
# their authors and need not  follow the licensing terms described here,
# provided that the new terms are clearly indicated on the first page of
# each file where they apply.
# 
# IN NO  EVENT SHALL THE AUTHOR  OR DISTRIBUTORS BE LIABLE  TO ANY PARTY
# FOR  DIRECT, INDIRECT, SPECIAL,  INCIDENTAL, OR  CONSEQUENTIAL DAMAGES
# ARISING OUT  OF THE  USE OF THIS  SOFTWARE, ITS DOCUMENTATION,  OR ANY
# DERIVATIVES  THEREOF, EVEN  IF THE  AUTHOR  HAVE BEEN  ADVISED OF  THE
# POSSIBILITY OF SUCH DAMAGE.
# 
# THE  AUTHOR  AND DISTRIBUTORS  SPECIFICALLY  DISCLAIM ANY  WARRANTIES,
# INCLUDING,   BUT   NOT  LIMITED   TO,   THE   IMPLIED  WARRANTIES   OF
# MERCHANTABILITY,    FITNESS   FOR    A    PARTICULAR   PURPOSE,    AND
# NON-INFRINGEMENT.  THIS  SOFTWARE IS PROVIDED  ON AN "AS  IS" BASIS,
# AND  THE  AUTHOR  AND  DISTRIBUTORS  HAVE  NO  OBLIGATION  TO  PROVIDE
# MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
# 
# $Id: 9108,v 1.6 2003-07-12 08:00:49 jcw Exp $
#
package require Tcl 8
package require Tk  8

option add *borderWidth          1

option add *Scale.label          speed
option add *Scale.resolution     1
option add *Scale.showValue      1

proc main { argc argv } \
{
  global forever

    wm withdraw .
    wm title . "A tachometer-like widget"
    wm geometry . +10+10

    tachometer::constructor .t1 ::value1 { 0 10 20 30 40 50 60 70 80 90 100 }
  scale .s1 -command "set ::value1" -variable ::value1

    tachometer::constructor .t2 ::value2 { 0 {} {} 5 {} {} 10 }
  scale .s2 -command "set ::value2" -variable ::value2

    button .b -text Quit -command "set ::forever 1"

    grid .t1 .s1 .t2 .s2 .b -padx 2 -pady 2
    wm deiconify .
    vwait forever
    tachometer::destructor .t1
    tachometer::destructor .t2
    exit 0
}

namespace eval tachometer {
  option add *Tachometer.min                       0.0
    option add *Tachometer.max                       100.0
    option add *Tachometer.indexid                   {}

  option add *Tachometer.relief                    flat
    option add *Tachometer.borderWidth               0

    option add *Tachometer.Canvas.background         gray
    option add *Tachometer.Canvas.width              50m
    option add *Tachometer.Canvas.height             50m
    option add *Tachometer.Canvas.foreground         black
    option add *Tachometer.Canvas.highlightThickness 0
    option add *Tachometer.Canvas.borderWidth        1
    option add *Tachometer.Canvas.relief             raised

    variable pi [expr {3.14159265359/180.0}]
}

proc tachometer::constructor { widget varname labels } {
  variable pi
    upvar  $varname value

    frame $widget -class Tachometer
    canvas [set c $widget.canvas]
    grid $c -sticky news

    option add ${widget}.varname $varname

    set width  [$c cget -width]
    set height [$c cget -height]
    set num  [llength $labels]
    set delta  [expr {(360.0-40.0)/($num-1)}]

# display
    set x1 [expr {$width/50.0*2.0}]
    set y1 [expr {$width/50.0*2.0}]
    set x2 [expr {$width/50.0*48.0}]
    set y2 [expr {$width/50.0*48.0}]
    $c create oval $x1 $y1 $x2 $y2 -fill white -width 1 -outline lightgray
    shadowcircle $c $x1 $y1 $x2 $y2 40 0.7m 135.0

# pin
    set x1 [expr {$width/50.0*23.0}]
    set y1 [expr {$width/50.0*23.0}]
    set x2 [expr {$width/50.0*27.0}]
    set y2 [expr {$width/50.0*27.0}]
    $c create oval $x1 $y1 $x2 $y2 -width 1 -outline lightgray -fill red
    shadowcircle $c $x1 $y1 $x2 $y2 40 0.7m -45.0

# danger marker
    $c create arc \
    [expr {$width/50.0*4.0}]  [expr {$width/50.0*4.0}] \
    [expr {$width/50.0*44.5}] [expr {$width/50.0*44.5}] \
    -start -70 -extent $delta -style arc \
    -outline red -fill red -width 3m

# graduate line
    set x1 [expr {$width/50.0*4.0}]
    set y1 [expr {$width/50.0*4.0}]
    set x2 [expr {$width/50.0*46.0}]
    set y2 [expr {$width/50.0*46.0}]
    $c create arc $x1 $y1 $x2 $y2 \
    -start -70 -extent 320 -style arc \
    -outline black -width 0.5m
    set xc [expr {($x2+$x1)/2.0}]
    set yc [expr {($y2+$y1)/2.0}]
    variable {}
  set ($c:xc) $xc
    set ($c:yc) $yc
    set ($c:motion) 0
    set ($c:varname) $varname
    bind $c <ButtonRelease>  [namespace code {needleRelease %W}]
    bind $c <Motion>         [namespace code {needleMotion %W %x %y}]

    set half [expr {$width/2.0}]
    set l1 [expr {$half*0.85}]
    set l2 [expr {$half*0.74}]
    set l3 [expr {$half*0.62}]

    set angle  110.0
    for {set i 0} {$i < $num} {incr i} \
    {
      set a [expr {($angle+$delta*$i)*$pi}]

        set x1 [expr {$half+$l1*cos($a)}]
        set y1 [expr {$half+$l1*sin($a)}]
        set x2 [expr {$half+$l2*cos($a)}]
        set y2 [expr {$half+$l2*sin($a)}]
        $c create line $x1 $y1 $x2 $y2 -fill black -width 0.5m

        set x1 [expr {$half+$l3*cos($a)}]
        set y1 [expr {$half+$l3*sin($a)}]

        set label [lindex $labels $i]
        if { [string length $label] } \
        {
          $c create text $x1 $y1 \
            -anchor center -justify center -fill black \
            -text $label -font { Helvetica 10 }
        }
    }

  rivet $c 10 10
    rivet $c [expr {$width-10}] 10
    rivet $c 10 [expr {$height-10}]
    rivet $c [expr {$width-10}] [expr {$height-10}]

    #set value 0
    drawline $widget $value

    trace add variable $varname write \
    [namespace code "tracer $widget $varname"]
    return $widget
}

proc tachometer::destructor { widget } \
{
  set varname [option get $widget varname {}]
    trace remove variable $varname write \
    [namespace code "tracer $widget $varname"]
    return
}

proc tachometer::tracer { widget varname args } \
{
  upvar  $varname value
    drawline $widget $value
    return
}

proc tachometer::drawline { widget value } \
{
  set c $widget.canvas

    variable pi
    set min  [option get $widget min {}]
    set max  [option get $widget max {}]
    set id [option get $widget indexid {}]

    set v [expr { ($value <= ($max*1.02))? $value : ($max*1.02) }]
    set angle [expr {((($v-$min)/($max-$min))*320.0+20.0)*$pi}]

    set width  [$c cget -width]
    set half [expr {$width/2.0}]
    set length [expr {$half*0.8}]

    set xl [expr {$half-$length*sin($angle)}]
    set yl [expr {$half+$length*cos($angle)}]

    set xs [expr {$half+0.2*$length*sin($angle)}]
    set ys [expr {$half-0.2*$length*cos($angle)}]

    catch {$c delete $id}
  set id [$c create line $xs $ys $xl $yl -fill red -width 0.6m]
    $c bind $id <ButtonPress> [namespace code {needlePress %W}]
    option add *[string trimleft $widget .].indexid $id
    return
}

proc tachometer::needlePress {w} \
{
  variable {}
  set ($w:motion) 1
}

proc tachometer::needleRelease {w} \
{
  variable {}
  set ($w:motion) 0
}

proc tachometer::needleMotion {w x y} \
{
  variable pi
    variable {}
  if {!$($w:motion)} { return }
  if {$y == $($w:yc) && $x == $($w:xc)} { return }
  set angle [expr {180.0 + atan2($($w:yc) - $y,$($w:xc) - $x) / $pi}]
    if {$angle >= 110.0} { set angle [expr {$angle - 110.0}] } \
    else { set angle [expr {250.0 + $angle}] }
  if {$angle >= 0.0 && $angle <= 320.0} \
  { set $($w:varname) [expr {$angle / 3.2}] }
}

proc tachometer::rivet { c xc yc } \
{
  set width 5
    set bevel 0.5m
    set angle -45.0
    set ticks 7
    shadowcircle $c \
    [expr {$xc-$width}] [expr {$yc-$width}] [expr {$xc+$width}] [expr {$yc+$width}] \
    $ticks $bevel $angle
}

proc shadowcircle { canvas x1 y1 x2 y2 ticks width orient } \
{
  set angle $orient
    set delta [expr {180.0/$ticks}]
    for {set i 0} {$i <= $ticks} {incr i} \
    {
      set a [expr {($angle+$i*$delta)}]
        set b [expr {($angle-$i*$delta)}]

        set color [expr {40+$i*(200/$ticks)}]
        set color [format "#%x%x%x" $color $color $color]

        $canvas create arc $x1 $y1 $x2 $y2 -start $a -extent $delta \
        -style arc -outline $color -width $width
        $canvas create arc $x1 $y1 $x2 $y2 -start $b -extent $delta \
        -style arc -outline $color -width $width
    }
}

