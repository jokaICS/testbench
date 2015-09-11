#include <ossm.h>
#include "Simulation/Integration.h"

outC_Integration out;
inC_Integration in;

ossm_atbl_EnumEntry enum_M_MODE[] = {
  { .value = 0, .label = "Full_Supervision" },
  { .value = 1, .label = "On_Sight" },
  { .value = 2, .label = "Staff_Responsible" },
  { .value = 3, .label = "Shunting" },
  { .value = 4, .label = "Unfitted" },
  { .value = 5, .label = "Sleeping" },
  { .value = 6, .label = "Stand_By" },
  { .value = 7, .label = "Trip" },
  { .value = 8, .label = "Post_Trip" },
  { .value = 9, .label = "System_Failure" },
  { .value = 10, .label = "Isolation" },
  { .value = 11, .label = "Non_Leading" },
  { .value = 12, .label = "Limited_Supervision" },
  { .value = 13, .label = "National_System" },
  { .value = 14, .label = "Reversing" },
  { .value = 15, .label = "Passive_Shunting" },
  { .value = 16, .label = "No_Power" }
};

ossm_atbl_Entry test_ossm_scade_entries[] = {
  // IN
  {.key = "GUI_reset", .type = BOOL, .adr = &in.GUI_targetSpeed},
  {.key = "GUI_targetSpeed", .type = DOUBLE, .adr = &in.GUI_targetSpeed},
  {.key = "GUI_traction", .type = DOUBLE, .adr = &in.GUI_traction},
  {.key = "GUI_brake", .type = DOUBLE, .adr = &in.GUI_brake},
  {.key = "GUI_initialPosition", .type = DOUBLE, .adr = &in.GUI_initialPosition},
  {.key = "GUI_initialVelocity", .type = DOUBLE, .adr = &in.GUI_initialVelocity},
  {.key = "GUI_mode", .type = INT, .adr = &in.GUI_mode},
  {.key = "GUI_level", .type = INT, .adr = &in.GUI_level},
  {.key = "GUI_mobileHWStatus", .type = INT, .adr = &in.GUI_mobileHWStatus},
  {.key = "GUI_openDesk", .type = BOOL, .adr = &in.GUI_openDesk},
  // OUT
  {.key = "GUI_currentPositionInM", .type = DOUBLE, .adr = &out.GUI_currentPositionInM, .rdly = true},
  {.key = "GUI_currentVelocityInKmH", .type = DOUBLE, .adr = &out.GUI_currentVelocityInKmH, .rdly = true},
  {.key = "GUI_timestamp", .type = INT, .adr = &out.GUI_timestamp, .rdly = true},
  {.key = "GUI_emergencyBrake", .type = BOOL, .adr = &out.GUI_emergencyBrake, .rdly = true},
  {.key = "GUI_serviceBrake", .type = BOOL, .adr = &out.GUI_serviceBrake, .rdly = true},
  // DEBUG
  {.key = "debugPermittedSpeed", .type = DOUBLE, .adr = &out.debugPermittedSpeed, .rdly = true},
  {.key = "debugCurrentMode", .type = ENUM, .adr = &out.debugCurrentMode, .rdly = true, .data = {.size = 17, .enumtbl = enum_M_MODE}},
  {.key = "debugCurrentLevel", .type = INT, .adr = &out.debugCurrentLevel, .rdly = true},
  {.key = "debugPermittedSpeed", .type = DOUBLE, .adr = &out.debugPermittedSpeed, .rdly = true},
  {.key = "debugInterventionSpeed", .type = DOUBLE, .adr = &out.debugInterventionSpeed, .rdly = true},
  //{.key = "path/b", .type = UCHAR, .adr = &data.b}
};

ossm_atbl_Table test_ossm_scade_tbl = {
  .size = 20,
  .sorting = UNSORTED,
  .entries = test_ossm_scade_entries
};


ossm_Status cycle() {
  Integration(&in,&out);
  return OSSM_OK;
}

ossm_scade_Interface* init() {
  ossm_scade_Interface *iface = ossm_scade_init_default(&test_ossm_scade_tbl,cycle);
  Integration_init(&out);
  return iface;
}
