#include "commands.h"

/*-------------------------------------------------------------------------+
| Function: cmd_sair - termina a aplicacao
+--------------------------------------------------------------------------*/ 
void cmd_sair (int argc, char **argv)
{
//  exit(0);
}

/*-------------------------------------------------------------------------+
| Function: cmd_test - apenas como exemplo
+--------------------------------------------------------------------------*/ 
void cmd_test (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}

/*-------------------------------------------------------------------------+
| Function: cmd_send - send message
+--------------------------------------------------------------------------*/ 
void cmd_send (int argc, char** argv)
{
int32_t lValueToSend;
BaseType_t xStatus;

    if (argc == 2) {
        printf ("msg: %s\n", argv[1]);
        lValueToSend = atoi(argv[1]);
        xStatus = xQueueSend( xQueue, &lValueToSend, 0 );
    }
    else {
        printf ("wrong number of arguments!\n");
    }
}

/*-------------------------------------------------------------------------+
| Function: cmd_rdt - read date/time (dd/MM/YYYY hh:mm:ss)
+--------------------------------------------------------------------------*/
void cmd_rdt(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_sd - set date (day, month, year)
+--------------------------------------------------------------------------*/
void cmd_sd(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_rc - read clock
+--------------------------------------------------------------------------*/
void cmd_rc(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_sc - set clock (hours, minutes, seconds)
+--------------------------------------------------------------------------*/
void cmd_sc(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_rt - read temperature
+--------------------------------------------------------------------------*/
void cmd_rt(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_rmm - read maximum and minimum of temperature
+--------------------------------------------------------------------------*/
void cmd_rmm(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_cmm - clear maximum and minimum of temperature
+--------------------------------------------------------------------------*/
void cmd_cmm(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_rp - read parameters (pmon, tala)
+--------------------------------------------------------------------------*/
void cmd_rp(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_mmp - modify monitoring period (seconds - 0 deactivate)
+--------------------------------------------------------------------------*/
void cmd_mmp(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_mta - modify time alarm (seconds)
+--------------------------------------------------------------------------*/
void cmd_mta(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_rai - read alarm info (alarm clock, tlow, thigh, active/inactive)
+--------------------------------------------------------------------------*/
void cmd_rai(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_sac - set alarm clock (hours, minutes, seconds)
+--------------------------------------------------------------------------*/
void cmd_sac(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_sat - set alarm temperature thresholds (tlow, thigh)
+--------------------------------------------------------------------------*/
void cmd_sat(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_adac - activate/deactivate alarm clock
+--------------------------------------------------------------------------*/
void cmd_adac(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_adat - activate/deactivate alarm temperature
+--------------------------------------------------------------------------*/
void cmd_adat(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_rts - read task state (Bubble Level, Hit Bit, Config Sound)
+--------------------------------------------------------------------------*/
void cmd_rts(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_adbl - activate/deactivate Bubble Level task
+--------------------------------------------------------------------------*/
void cmd_adbl(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_adhb - activate/deactivate Hit Bit task
+--------------------------------------------------------------------------*/
void cmd_adhb(int argc, char **argv)
{

}

/*-------------------------------------------------------------------------+
| Function: cmd_adcs - activate/deactivate Config Sound operation
+--------------------------------------------------------------------------*/
void cmd_adcs(int argc, char **argv)
{

}

