//main.c
#include <lpc21xx.h>
#include "lcd.h"
#include "kpm.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "interrupt.h"
#include "interrupt_defines.h"
#include "medicine.h"
#include "rtc_edit.h"
#include "types.h"
#include "lcd_defines.h"
#include "delay.h"

#define BUZZER 20 //p0.20

extern volatile s32 setup_flag;
//extern volatile s32 buz_flag;

s32 hour,min,sec,date,month,year,day;
void port_init()
{
        IODIR0|=1<<BUZZER;
}

void menu()
{
            u8 key;
Label:CmdLCD(CLEAR_LCD);
      StrLCD("1.Clock");
      CmdLCD(GOTO_LINE2_POS0);
      StrLCD("2.Medicine");
      StrLCD("3.Exit");

      key = KeyScan();
      if(key=='1')
      {
              edit_rtc_time();
              CmdLCD(CLEAR_LCD);
              return;
      }

      else if(key=='2')
      {
              CmdLCD(CLEAR_LCD);
              configure_medicine();
              CmdLCD(CLEAR_LCD);
              return;
      }
      else if(key=='3')
      {
              CmdLCD(CLEAR_LCD);
              return;
      }
      else
      {
              CmdLCD(CLEAR_LCD);
              StrLCD("Invalid Option!");
              delay_ms(100);
              goto Label;
               }

}

int main()
{
        s32 i,j;
        u8 msg[]="Medicine Reminder System!";
        s8 display[17];
        InitLCD();
        InitKPM();
        RTC_Init();
        port_init();
        //interrupt_init();
        interrupt_init();
        StrLCD("UserConfigurable");
        for(i=0;i<24+16;i++)
        {
                for(j=0;j<16;j++)
                {
                        if(i+j<16)
                                display[j]=' ';
                        else if(i+j-16<24)
                                display[j]=msg[i+j-16];
                        else
                                display[j]=' ';
                }
                display[16]='\0';
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD(display);
                delay_ms(200);
        }
        CmdLCD(CLEAR_LCD);
        SetRTCTimeInfo(10,40,00);
        SetRTCDateInfo(15,3,2026);
        SetRTCDay(SUN);
        while(1)
        {
                GetRTCTimeInfo(&hour,&min,&sec);
                DisplayRTCTime(hour,min,sec);
                GetRTCDateInfo(&date,&month,&year);
                DisplayRTCDate(date,month,year);
                GetRTCDay(&day);
                DisplayRTCDay(day);
                if(setup_flag)
                {
                        IOPIN1^=(1<<EINT0_STATUS_LED);
                        menu();
                        setup_flag=0;
                }
                check_medicine_time(hour,min);
        }
}
