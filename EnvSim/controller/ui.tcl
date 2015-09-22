package require Tk
package require BWidget

wm title . "openETCS SimEnv Controller"

grid [ttk::frame .c -padding 5] -column 0 -row 0 -sticky nwes

# Log area
grid [tk::text .c.log]
