#include "commands.h"

QueueHandle_t xQueue_send; /*sem isto aqui o extern dá erro*/

/*-------------------------------------------------------------------------+
| Function: cmd_sair - termina a aplicacao
+--------------------------------------------------------------------------*/ 
void cmd_sair (int argc, char **argv)
{
    printf("Sair, não sei o que faz...\n");
    printf("Toma uma vaca...\n");
    printf("\n");
    printf("             (__)    \n");
    printf("             (00)    \n");
    printf("       /------\\/     \n");
    printf("      / |    ||      \n");
    printf("     *  /\\---/\\      \n");
    printf("        ~~   ~~      \n");
    printf("\n");
    //printf("Cmd> ");
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
    //printf("Cmd> ");
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
        xStatus = xQueueSend( xQueue_send, &lValueToSend, 0 );
    }
    else {
        printf ("wrong number of arguments!\n");
    }
    //printf("Cmd> ");
}

/*-------------------------------------------------------------------------+
| Function: cmd_rdt - read date/time (dd/MM/YYYY hh:mm:ss)
+--------------------------------------------------------------------------*/
void cmd_rdt(int argc, char **argv)
{
    printf("Selected rdt -> here is date and time\n");

    char buf[32];

    snprintf(buf, sizeof(buf),
             "%02d/%02d/%04d %02d:%02d:%02d\n",
             current_time_tm.tm_mday,
             current_time_tm.tm_mon + 1,
             current_time_tm.tm_year + 1900,
             current_time_tm.tm_hour,
             current_time_tm.tm_min,
             current_time_tm.tm_sec);

    printf("%s\n", buf);
    //printf("Cmd> ");

}

/*-------------------------------------------------------------------------+
| Function: cmd_sd - set date (day, month, year)
+--------------------------------------------------------------------------*/
void cmd_sd(int argc, char **argv)
{
    printf("Selected sd -> this sets the date\n");
    if ( sscanf(argv[1],"%d", &current_time_tm.tm_mday) != 1 ){printf("Please insert day month year\n"); return;}
    if ( sscanf(argv[2],"%d", &current_time_tm.tm_mon)  != 1 ){printf("Please insert day month year\n");  return;}
    if ( sscanf(argv[3],"%d", &current_time_tm.tm_year) != 1 ){printf("Please insert day month year\n"); return;}
    current_time_tm.tm_mon -= 1; /*tm_mon vai de 0 a 11*/
    current_time_tm.tm_year -= 1900; /*tm_year é anos desde 1900*/
    current_time = mktime(&current_time_tm);
    printf("Cmd> ");
}

/*-------------------------------------------------------------------------+
| Function: cmd_rc - read clock
+--------------------------------------------------------------------------*/
void cmd_rc(int argc, char **argv)
{
    printf("Selected rc -> this reads the clock?\n");
    printf("Here is my raw counter:\n");
    
    char buf[32];

    snprintf(buf, sizeof(buf),
             "%02d:%02d:%02d\n",
             current_time_tm.tm_hour,
             current_time_tm.tm_min,
             current_time_tm.tm_sec);

    printf("%s\n", buf);
}

/*-------------------------------------------------------------------------+
| Function: cmd_sc - set clock (hours, minutes, seconds)
+--------------------------------------------------------------------------*/
void cmd_sc(int argc, char **argv)
{
    printf("This sets the clock\n");
    //printf("Cmd> ");

}

/*-------------------------------------------------------------------------+
| Function: cmd_rt - read temperature
+--------------------------------------------------------------------------*/
void cmd_rt(int argc, char **argv)
{
    printf("rt -> read the temperature\n");
    printf("%f\n",temperature);
    //printf("Cmd> ");

}

/*-------------------------------------------------------------------------+
| Function: cmd_rmm - read maximum and minimum of temperature
+--------------------------------------------------------------------------*/
void cmd_rmm(int argc, char **argv)
{
    printf("rmm -> read maximum and minimum of temperature\n");
    printf("Maximum : %f\n",temperature_max);
    printf("Minimum : %f\n",temperature_min);
    printf("\n");
    //printf("Cmd> ");

}

/*-------------------------------------------------------------------------+
| Function: cmd_cmm - clear maximum and minimum of temperature
+--------------------------------------------------------------------------*/
void cmd_cmm(int argc, char **argv)
{
    printf("cmm -> clear maximum and minimum of temperature\n");
    temperature_max = -273.15; temperature_min = 15000000.0;
    printf("cleared!\n");
    printf("\n");
    //printf("Cmd> ");

}

/*-------------------------------------------------------------------------+
| Function: cmd_rp - read parameters (pmon, tala)
+--------------------------------------------------------------------------*/
void cmd_rp(int argc, char **argv)
{
    printf("Reading parameters:\n");
    printf("PMON = %d\n",pmon);
    printf("TALA = %d\n",tala);
    //printf("Cmd> ");
}

/*-------------------------------------------------------------------------+
| Function: cmd_mmp - modify monitoring period (seconds - 0 deactivate)
+--------------------------------------------------------------------------*/
void cmd_mmp(int argc, char **argv)
{
    printf("Monitoring period changed to:\n");
    printf("PMON = %d\n",argv[1]);
}

/*-------------------------------------------------------------------------+
| Function: cmd_mta - modify time alarm (seconds)
+--------------------------------------------------------------------------*/
void cmd_mta(int argc, char **argv)
{
    printf("Time alarm changed to:\n");
    printf("TALA = %d\n",argv[1]);
}

/*-------------------------------------------------------------------------+
| Function: cmd_rai - read alarm info (alarm clock, tlow, thigh, active/inactive)
+--------------------------------------------------------------------------*/
void cmd_rai(int argc, char **argv)
{
    printf("Reading alarm info:\n");
    printf("Alarm Time : %02d:%02d:%02d\n",alarm_time_hours,alarm_time_minutes,alarm_time_seconds);
    printf("Temperature Low Threshold : %f\n",tlow); 
    printf("Temperature High Threshold : %f\n",thigh);
    printf("Alarm Clock : ");
    if(AlarmClock_enable == true)
    {
        printf("enabled\n");
    }else
    {
        printf("disabled\n");
    }
    printf("Alarm Temperature : ");
    if(AlarmTemp_enable == true){printf("enabled\n");}else{printf("disabled\n");}
    //printf("Cmd> ");

}

/*-------------------------------------------------------------------------+
| Function: cmd_sac - set alarm clock (hours, minutes, seconds)
+--------------------------------------------------------------------------*/
void cmd_sac(int argc, char **argv)
{
    printf("Setting alarm clock:\n");
    printf("Enter hours, minutes, seconds:\n");
    scanf("%d %d %d", &alarm_time_hours, &alarm_time_minutes, &alarm_time_seconds);
    if (alarm_time_hours <0 || alarm_time_hours >23 || alarm_time_minutes <0 || alarm_time_minutes >59 || alarm_time_seconds <0 || alarm_time_seconds >59)
    {
        printf("Invalid time! Please enter a valid time.\n");
        /*reset to default*/
        alarm_time_hours = 0; alarm_time_minutes = 0; alarm_time_seconds = 0;
    }
}

/*-------------------------------------------------------------------------+
| Function: cmd_sat - set alarm temperature thresholds (tlow, thigh)
+--------------------------------------------------------------------------*/
void cmd_sat(int argc, char **argv)
{
    printf("Setting alarm temperature thresholds:\n");
    //printf("Cmd> ");

}

/*-------------------------------------------------------------------------+
| Function: cmd_adac - activate/deactivate alarm clock
+--------------------------------------------------------------------------*/
void cmd_adac(int argc, char **argv)
{
    printf("Setting alarm clock:\n");
    AlarmClock_enable = ! AlarmClock_enable;
    if(AlarmClock_enable == true)
    {
        printf("enabled\n");
    }else
    {
        printf("disabled\n");
    }
    //printf("Cmd> ");
}

/*-------------------------------------------------------------------------+
| Function: cmd_adat - activate/deactivate alarm temperature
+--------------------------------------------------------------------------*/
void cmd_adat(int argc, char **argv)
{
    printf("Setting alarm temperature:\n");
    AlarmTemp_enable = ! AlarmTemp_enable;
    if(AlarmTemp_enable == true)
    {
        printf("enabled\n");
    }else
    {
        printf("disabled\n");
    }
    //printf("Cmd> ");
}

/*-------------------------------------------------------------------------+
| Function: cmd_rts - read task state (Bubble Level, Hit Bit, Config Sound)
+--------------------------------------------------------------------------*/
void cmd_rts(int argc, char **argv)
{
    printf("rts -> read task state\n");
    printf("Bubble Level : ");
    if(Bubble_enable == true){printf("enabled\n");}else{printf("disabled\n");}
    printf("Hit Bit Game :");
    if(HitBit_enable == true){printf("enabled\n");}else{printf("disabled\n");}
    printf("Config Sound :");
    if(ConfigSound.enable == true){printf("enabled\n");}else{printf("disabled\n");}
    //printf("\nCmd> ");

}

/*-------------------------------------------------------------------------+
| Function: cmd_adbl - activate/deactivate Bubble Level task
+--------------------------------------------------------------------------*/
void cmd_adbl(int argc, char **argv)
{
    printf("adbl -> toggle state of Bubble level\n");
    Bubble_enable = !Bubble_enable;
    printf("Toggled!\n");
    printf("Bubble Level : ");
    if(Bubble_enable == true){printf("enabled\n");}else{printf("disabled\n");}
    //printf("\nCmd> ");

}

/*-------------------------------------------------------------------------+
| Function: cmd_adhb - activate/deactivate Hit Bit task
+--------------------------------------------------------------------------*/
void cmd_adhb(int argc, char **argv)
{
    printf("adhb -> toggle state of Hitbit game\n");
    HitBit_enable = !HitBit_enable;
    printf("Toggled!\n");
    printf("Hit Bit Game :");
    if(HitBit_enable == true)
    {
        printf("enabled\n");
    }else{
        printf("disabled\n");
    }
    //printf("\nCmd> ");

}

/*-------------------------------------------------------------------------+
| Function: cmd_adcs - activate/deactivate Config Sound operation
+--------------------------------------------------------------------------*/
void cmd_adcs(int argc, char **argv)
{
    printf("adcs -> toggle state of Config Sound\n");
    ConfigSound.enable = !ConfigSound.enable;
    printf("Toggled!\n");
    printf("Config Sound :");
    if(ConfigSound.enable == true){printf("enabled\n");}else{printf("disabled\n");}
    //printf("\nCmd> ");

}

