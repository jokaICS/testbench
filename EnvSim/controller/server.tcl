
namespace eval ::srv {
  variable server
  variable clients
}

proc srv::start {port} {
  variable server
  set server [socket -server srv::onConnect $port]
  ui::log server "server listening on port $port"
}  


proc srv::onConnect {channel addr port} {
  fileevent $channel readable "srv::handle $channel $addr $port"
  ui::log server "connected to client $addr:$port"
}


# handles incoming command requests
proc srv::handle {channel addr port} {
  set len [gets $channel line]
  if {($len <= 0)&&[eof $channel]}  {
    close $channel
    ui::log server "client $addr:$port disconnected"
  } else {
    switch -regexp -matchvar m -- $line {
      {begin\s*(\w*)\s*} { begin "$addr:$port" [lindex $m 1] }
      getconf            { getconf "$addr:$port" }
      default {
        ui::log server "invalid command from $addr:$port: $line" error
      }
    }
  }
}


# handle command 'begin'
proc srv::begin {id type} {
  variable clients
  
  dict set clients $id type $type
  ui::log server "session established for client $type:$id"
}


# handle command 'getconf'
proc srv::getconf id {
  cnf::getconfig
}
