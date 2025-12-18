#ifndef MONITOR_H
#define MONITOR_H

/***************************************************************************
| File: monitor.c
|
| Autor: Carlos Almeida (IST), from work by Jose Rufino (IST/INESC), 
|        from an original by Leendert Van Doorn
| Data:  Nov 2002
***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "commands.h"
#include "pin_definition.h"

/*-------------------------------------------------------------------------+
| Variable and constants definition
+--------------------------------------------------------------------------*/ 
const char TitleMsg[] = "\n Application Control Monitor\n";
const char InvalMsg[] = "\nInvalid command!";

void cmd_sos(int argc, char **argv);
char* my_fgets(char* ln, int maxlen, FILE* stream);
int my_getline(char** argv, int argvsize);
void monitor(void);

struct  command_d {
  void  (*cmd_fnct)(int, char**);
  char* cmd_name;
  char* cmd_help;
} const commands[] = {
  {cmd_sos,  "sos",  "help"},
  {cmd_send, "send", "<msg> send message"},
  {cmd_sair, "sair", "sair"},
  {cmd_test, "test", "<arg1> <arg2> test command"},
  {cmd_rdt,  "rdt",  "read date/time (dd/MM/YYYY hh:mm:ss)"},
  {cmd_sd,   "sd",   "set date (day, month, year)"},
  {cmd_rc,   "rc",   "read clock"},
  {cmd_sc,   "sc",   "set clock (hours, minutes, seconds)"},
  {cmd_rt,   "rt",   "read temperature"},
  {cmd_rmm,  "rmm",  "read maximum and minimum of temperature"},
  {cmd_cmm,  "cmm",  "clear maximum and minimum of temperature"},
  {cmd_rp,   "rp",   "read parameters (pmon, tala)"},
  {cmd_mmp,  "mmp",  "modify monitoring period (seconds - 0 deactivate)"},
  {cmd_mta,  "mta",  "modify time alarm (seconds)"},
  {cmd_rai,  "rai",  "read alarm info (alarm clock, tlow, thigh, active/inactive)"},
  {cmd_sac,  "sac",  "set alarm clock (hours, minutes, seconds)"},
  {cmd_sat,  "sat",  "set alarm temperature thresholds (tlow, thigh)"},
  {cmd_adac, "adac", "activate/deactivate alarm clock"},
  {cmd_adat, "adat", "activate/deactivate alarm temperature"},
  {cmd_rts,  "rts",  "read task state (Bubble Level, Hit Bit, Config Sound)"},
  {cmd_adbl, "adbl", "activate/deactivate Bubble Level task"},
  {cmd_adhb, "adhb", "activate/deactivate Hit Bit task"},
  {cmd_adcs, "adcs", "activate/deactivate Config Sound operation"},
};


#define NCOMMANDS  (sizeof(commands)/sizeof(struct command_d))
#define ARGVECSIZE 3
#define MAX_LINE   50


#endif // MONITOR_H
