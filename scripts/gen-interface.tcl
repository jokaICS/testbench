proc getFullName {obj} {
  set pkg [GetRole $obj package]
  while {$pkg != {} } {
    append fname "[Get $pkg name]::"
    set pkg [GetRole $pkg parentPackage]
  }
  append fname [Get $obj name]
  return $fname
}


proc getTblEntryType {type} {
  switch $type {
    bool { return BOOL }
    real { return DOUBLE }
    int  { return INT }
    default { return 0 }
  }
}

#proc getTypeDesc {type keyPrefix adrPrefix} {
#  set entries {}
#
#  switch [Class $type] {
#    Structure {
#      append keyPrefix .
#      append adrPrefix .
#      foreach e [GetRole $type element] {
#        set typename [getTblEntryType [Get [GetRole $e type] name]]
#        set name [Get $e name]
#        if {$typename!=0} {
#          lappend entries "$keyPrefix$name $typename $adrPrefix$name"
#        } else { 
#          foreach subtype [GetRole [GetRole $e type] definition] {
#            lappend entries [join [getTypeDesc $subtype $keyPrefix$name $adrPrefix$name]]
#          }
#        }
#      }
#    }
#    NamedType {
#      lappend entries [getTypeDesc [GetRole $type type] $keyPrefix $adrPrefix]
#    }
#    default { output [Class $type] }
#  }
#  output $entries\n\n
#  return $entries
#}

proc getEntries {entity keyPrefix adrPrefix} {
  lappend entries

  switch [Class $entity] {
    NamedType {
      if [Call $entity IsPredefined] {
        lappend entries [list "$keyPrefix [getTblEntryType [Get $entity name]] $adrPrefix"]
      } else {
        lappend entries [join [getEntries [GetRole $entity definition] $keyPrefix $adrPrefix]]
      }      
    }
    LocalVariable {
      set name [Get $entity name]
      lappend entries [join [getEntries [GetRole $entity type] $keyPrefix$name $adrPrefix$name]]
    }
    Structure {
      foreach elem [GetRole $entity element] {
        set name [Get $elem name]
	lappend entries [join [getEntries [GetRole $elem type] $keyPrefix.$name $adrPrefix.$name]]
      }
      #output $entries\n\n
    }
    default {  }
  }
  #output $entries\n\n
  return $entries
}


proc getEntriesForNode {node} {
  set entries {}
  foreach in [GetRole $node input] {
    lappend entries [join [getEntries $in "" "&in."]]
  }
  #output [join $entries]\n\n
  return [join $entries]
}


proc printEntries {entries entriesVar} {
  output "ossm_atbl_Entry $entriesVar\[\] = \{\n"
  foreach e $entries {
    output "  {.key = \"[lindex $e 0]\", .type = [lindex $e 1], .adr = [lindex $e 2]},\n"
  }
  output "\};\n"
}


proc printInterface {entries header nodeCName {entriesVar iface_entries} {tableVar iface_tbl}} {
  output "#include <ossm.h>\n"
  output "#include \"$header\"\n\n"

  output "outC_$nodeCName out;\n"
  output "inC_$nodeCName in;\n\n"

  printEntries $entries $entriesVar

  output \n\n
  output "ossm_atbl_Table $tableVar = \{\n"
  output "  .size = [llength $entries],\n"
  output "  .sorting = UNSORTED,\n"
  output "  .entries = $entriesVar\n"
  output "\};\n\n"

  output "ossm_Status cycle() \{\n"
  output "  $nodeCName (&in,&out);\n"
  output "  return OSSM_OK;\n"
  output "\};\n\n"

  output "ossm_scade_Interface* init() \{\n"
  output "  ${nodeCName}_init(&out);\n"
  output "  return ossm_scade_init_default(&$tableVar,cycle);\n"
  output "\};\n\n"
}

printInterface [getEntriesForNode $selection] Simulation/Integration.h Integration