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
}

/*-------------------------------------------------------------------------+
| Function: cmd_sd - set date (day, month, year)
+--------------------------------------------------------------------------*/
void cmd_sd(int argc, char **argv)
{   
    int intended_day, intended_month, intended_year;
    int max_day;
    printf("Selected sd -> this sets the date\n");
    
    if (argc == 4) {
        intended_day = atoi(argv[1]);
        intended_month = atoi(argv[2]);
        intended_year = atoi(argv[3]);

        if (intended_day < 1 || intended_day > 31 || intended_month < 1 || intended_month > 12 || intended_year < 1970 || intended_year > 2037) {
           printf("Invalid date! Your date is out of range\n");
        
        } else {
            max_day = get_days_in_month(intended_month, intended_year);
            if (intended_day > max_day) {
                printf("Invalid date! Day exceeds maximum for the month\n");
            } else {
                current_time_tm.tm_mday = intended_day;
                current_time_tm.tm_mon = intended_month - 1; // tm_mon is 0-11
                current_time_tm.tm_year = intended_year - 1900; // tm_year is years since 1900
                current_time = clock_tm_to_time(&current_time_tm);
                printf("Date set successfully!\n");
            }
        }
    
    } else {
        printf("Wrong number of arguments! Usage: sd <day> <month> <year>\n");
    }
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
    int intended_hours, intended_minutes, intended_seconds;
    printf("Selected sc -> this sets the clock\n");

    if (argc == 4) {
        intended_hours = atoi(argv[1]);
        intended_minutes = atoi(argv[2]);
        intended_seconds = atoi(argv[3]);

        if (intended_hours < 0 || intended_hours > 23 || intended_minutes < 0 || intended_minutes > 59 || intended_seconds < 0 || intended_seconds > 59){
           printf("Invalid time! Your time is out of range\n");
        } else {
            current_time_tm.tm_hour = intended_hours;
            current_time_tm.tm_min = intended_minutes;
            current_time_tm.tm_sec = intended_seconds;
            current_time = clock_tm_to_time(&current_time_tm);
            printf("Time set successfully!\n");
        }
    
    } else {
        printf("Wrong number of arguments! Usage: sc <hours> <minutes> <seconds>\n");
    }
}

/*-------------------------------------------------------------------------+
| Function: cmd_rt - read temperature
+--------------------------------------------------------------------------*/
void cmd_rt(int argc, char **argv)
{

    printf("rt -> read the temperature\n");
    xTaskNotify(xSensorTaskHandle, 0x10, eSetBits);
    printf("%f\n",temperature);
    //printf("Cmd> ");

    printf("Selected rt -> read the temperature\n");
    printf("%f\n",temperature);
}

/*-------------------------------------------------------------------------+
| Function: cmd_rmm - read maximum and minimum of temperature
+--------------------------------------------------------------------------*/
void cmd_rmm(int argc, char **argv)
{
    printf("Selected rmm -> read maximum and minimum of temperature\n");
    printf("Maximum : %f\n",temperature_max);
    printf("Minimum : %f\n",temperature_min);
}

/*-------------------------------------------------------------------------+
| Function: cmd_cmm - clear maximum and minimum of temperature
+--------------------------------------------------------------------------*/
void cmd_cmm(int argc, char **argv)
{
    printf("Selected cmm -> clear maximum and minimum of temperature\n");
    temperature_max = -273.15; temperature_min = 15000000.0;
    printf("cleared!\n");
}

/*-------------------------------------------------------------------------+
| Function: cmd_rp - read parameters (pmon, tala)
+--------------------------------------------------------------------------*/
void cmd_rp(int argc, char **argv)
{
    printf("Selected rp -> read pmon and tala\n");
    printf("PMON = %d\n",pmon);
    printf("TALA = %d\n",tala);
}

/*-------------------------------------------------------------------------+
| Function: cmd_mmp - modify monitoring period (seconds - 0 deactivate)
+--------------------------------------------------------------------------*/
void cmd_mmp(int argc, char **argv)
{
    int new_pmon;
    new_pmon = atoi(argv[1]);
    printf("Selected mmp -> modify monitoring period\n");
    if (argc == 2) {
        if (new_pmon < 0 || new_pmon > 99) {
            printf("Invalid monitoring period! It must be between 0 and 99.\n");
            return;
        }
        pmon = new_pmon;
        printf("PMON = %d\n",pmon);
    } else {
        printf("Wrong number of arguments! Usage: mmp <seconds>\n");
    }
}

/*-------------------------------------------------------------------------+
| Function: cmd_mta - modify time alarm (seconds)
+--------------------------------------------------------------------------*/
void cmd_mta(int argc, char **argv)
{
    int new_tala;
    new_tala = atoi(argv[1]);
    printf("Selected mta -> modify time alarm\n");
    if (argc == 2) {
        if (new_tala < 0 || new_tala > 60) {
            printf("Invalid time alarm! It must be between 0 and 60 seconds.\n");
            return;
        }
        tala = new_tala;
        printf("TALA = %d\n",tala);
    } else {
        printf("Wrong number of arguments! Usage: mta <seconds>\n");
    } 
}

/*-------------------------------------------------------------------------+
| Function: cmd_rai - read alarm info (alarm clock, tlow, thigh, active/inactive)
+--------------------------------------------------------------------------*/
void cmd_rai(int argc, char **argv)
{
    printf("Selected rai -> read alarm info:\n");
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
}

/*-------------------------------------------------------------------------+
| Function: cmd_sac - set alarm clock (hours, minutes, seconds)
+--------------------------------------------------------------------------*/
void cmd_sac(int argc, char **argv)
{
    int intended_hours, intended_minutes, intended_seconds;
    printf("Selected sac -> set alarm clock:\n");
    if (argc == 4) {
        intended_hours = atoi(argv[1]);
        intended_minutes = atoi(argv[2]);
        intended_seconds = atoi(argv[3]);

        if (intended_hours < 0 || intended_hours > 23 || intended_minutes < 0 || intended_minutes > 59 || intended_seconds < 0 || intended_seconds > 59){
           printf("Invalid time! Your time is out of range\n");
        } else {
            alarm_time_hours = intended_hours;
            alarm_time_minutes = intended_minutes;
            alarm_time_seconds = intended_seconds;
            printf("Alarm time set successfully!:%02d:%02d:%02d\n",alarm_time_hours,alarm_time_minutes,alarm_time_seconds);
        }
    
    } else {
        printf("Wrong number of arguments! Usage: sac <hours> <minutes> <seconds>\n");
    }
}

/*-------------------------------------------------------------------------+
| Function: cmd_sat - set alarm temperature thresholds (tlow, thigh)
+--------------------------------------------------------------------------*/
void cmd_sat(int argc, char **argv)
{
    int new_tlow, new_thigh;
    printf("Selected sat -> set alarm temperature thresholds:\n");
    if (argc == 3) {
        new_tlow = atoi(argv[1]);
        new_thigh = atoi(argv[2]);

        if (new_tlow < 0 || new_tlow > 50 || new_thigh < 0 || new_thigh > 50 || new_tlow >= new_thigh){
           printf("Invalid temperature thresholds! They must be between 0 and 50, and tlow must be less than thigh.\n");
        } else {
            tlow = new_tlow;
            thigh = new_thigh;
            printf("Temperature thresholds set successfully!\n");
            printf("tlow = %f\n", tlow);
            printf("thigh = %f\n", thigh);
        }
    
    } else {
        printf("Wrong number of arguments! Usage: sat <tlow> <thigh>\n");
    }
}

/*-------------------------------------------------------------------------+
| Function: cmd_adac - activate/deactivate alarm clock
+--------------------------------------------------------------------------*/
void cmd_adac(int argc, char **argv)
{
    printf("Selected adac -> Setting alarm clock:\n");
    AlarmClock_enable = ! AlarmClock_enable;
    if(AlarmClock_enable == true)
    {
        printf("enabled\n");
    }else
    {
        printf("disabled\n");
    }
}

/*-------------------------------------------------------------------------+
| Function: cmd_adat - activate/deactivate alarm temperature
+--------------------------------------------------------------------------*/
void cmd_adat(int argc, char **argv)
{
    printf("Selected adat -> Setting alarm temperature:\n");
    AlarmTemp_enable = ! AlarmTemp_enable;
    if(AlarmTemp_enable == true)
    {
        printf("enabled\n");
    }else
    {
        printf("disabled\n");
    }
}

/*-------------------------------------------------------------------------+
| Function: cmd_rts - read task state (Bubble Level, Hit Bit, Config Sound)
+--------------------------------------------------------------------------*/
void cmd_rts(int argc, char **argv)
{
    printf("Selected rts -> read task state\n");
    printf("Bubble Level : ");
    if(Bubble_enable == true){printf("enabled\n");}else{printf("disabled\n");}
    printf("Hit Bit Game :");
    if(HitBit_enable == true){printf("enabled\n");}else{printf("disabled\n");}
    printf("Config Sound :");
    if(ConfigSound.enable == true){printf("enabled\n");}else{printf("disabled\n");}
}

/*-------------------------------------------------------------------------+
| Function: cmd_adbl - activate/deactivate Bubble Level task
+--------------------------------------------------------------------------*/
void cmd_adbl(int argc, char **argv)
{
    printf("Selected adbl -> toggle state of Bubble level\n");
    Bubble_enable = !Bubble_enable;
    printf("Toggled!\n");
    printf("Bubble Level : ");
    if(Bubble_enable == true){printf("enabled\n");}else{printf("disabled\n");}
}

/*-------------------------------------------------------------------------+
| Function: cmd_adhb - activate/deactivate Hit Bit task
+--------------------------------------------------------------------------*/
void cmd_adhb(int argc, char **argv)
{
    printf("Selected adhb -> toggle state of Hitbit game\n");
    HitBit_enable = !HitBit_enable;
    printf("Toggled!\n");
    printf("Hit Bit Game :");
    if(HitBit_enable == true)
    {
        printf("enabled\n");
    }else{
        printf("disabled\n");
    }
}

/*-------------------------------------------------------------------------+
| Function: cmd_adcs - activate/deactivate Config Sound operation
+--------------------------------------------------------------------------*/
void cmd_adcs(int argc, char **argv)
{
    printf("Selected adcs -> toggle state of Config Sound\n");
    ConfigSound.enable = !ConfigSound.enable;
    printf("Toggled!\n");
    printf("Config Sound :");
    if(ConfigSound.enable == true){printf("enabled\n");}else{printf("disabled\n");}
}

