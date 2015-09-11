
proc getFullName {obj} {
  set pkg [GetRole $obj package]
  while {$pkg != {} } {
    append fname "[Get $pkg name]::"
    set pkg [GetRole $pkg parentPackage]
  }
  append fname [Get $obj name]
  return $fname
}
  

proc accVarDesc {var} {
  set type [GetRole $var type]
  lappend ::acc "[Get $var name] [getFullName $type]"
  return 1
}

proc getNodeDesc {node} {
  set desc "name [getFullName $node]"
  set ::acc {}
  MapRole $node input accVarDesc
  set desc [concat $desc [list inputs $::acc]]
  set ::acc {}
  MapRole $node output accVarDesc
  set desc [concat $desc [list outputs $::acc]]
  return $desc
}

proc printNodeDesc {node} {
  foreach {k v} [getNodeDesc $node] {
    switch -regexp $k {
      name {output "$v; ; ; ;\n"}
      inputs|outputs {
	foreach var $v { output " ;$k;[lindex $var 0];[lindex $var 1];\n" }
      }
      default {}
    }
  }
  return 1
}

output "Node;ArgType;Name;Type;\n"
MapRole $selection calledOperator printNodeDesc
