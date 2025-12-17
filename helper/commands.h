#ifndef COMMANDS_HANDLE_H
#define COMMANDS_HANDLE_H

/***************************************************************************
| File: comando.c  -  Concretizacao de comandos (exemplo)
|
| Autor: Carlos Almeida (IST)
| Data:  Nov 2002
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "queue.h"

extern QueueHandle_t xQueue;

void cmd_sair(int argc, char **argv);
void cmd_test(int argc, char **argv);
void cmd_send(int argc, char **argv);

// command read date/time (no arguments)
void cmd_rdt(int argc, char **argv); 

// command set date (3 arguments: day, month, year)
void cmd_sd(int argc, char **argv);

// command read clock (no arguments)
void cmd_rc(int argc, char **argv);

// command set clock (3 arguments: hours, minutes, seconds)
void cmd_sc(int argc, char **argv);

// command read temperature (no arguments)
void cmd_rt(int argc, char **argv);

// command read maximum and minimum of temperature (no arguments)
void cmd_rmm(int argc, char **argv);

// command clear maximum and minimum of temperature (no arguments)
void cmd_cmm(int argc, char **argv);

// command read parameters (no arguments)
void cmd_rp(int argc, char **argv);

// command modify monitoring period (1 argument: seconds)
void cmd_mmp(int argc, char **argv);

// command modify time alarm (1 argument: seconds)
void cmd_mta(int argc, char **argv);

// command read alarm info (no arguments)
void cmd_rai(int argc, char **argv);

// command set alarm clock (2 arguments: hours, minutes, seconds)
void cmd_sac(int argc, char **argv);

// command set alarm temperature thresholds (2 arguments: tlow, thigh)
void cmd_sat(int argc, char **argv);

// command activate/deactivate alarm clock (1 argument: 1/0)
void cmd_adac(int argc, char **argv);

// command activate/deactivate alarm temperature (1 argument: 1/0)
void cmd_adat(int argc, char **argv);

// command read task state (no arguments)
void cmd_rts(int argc, char **argv);

// command activate/deactivate Bubble Level task (1 argument: 1/0)
void cmd_adbl(int argc, char **argv);

// command activate/deactivate Hit Bit task (1 argument: 1/0)
void cmd_adhb(int argc, char **argv);

// command activate/deactivate Config Sound operation (1 argument: 1/0)
void cmd_adcs(int argc, char **argv);

#endif // COMMANDS_HANDLE_H
