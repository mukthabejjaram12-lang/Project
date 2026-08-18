#include <lpc21xx.h>
#include "lcd.h"
#include "kpm.h"
#include "types.h"
#include "lcd_defines.h"
#include "delay.h"
#define BUZZER 20 //p0.20
struct medicine
{
    s32 hour;
    s32 min;
};

struct medicine med[3];
s32 med_count=0;
u32 flag=0;

extern volatile s32 ack_flag;
volatile s32 buz_flag=1;

int read_two_digit()
{
    u8 key;
    s32 digits[2];
    s32 i = 0;

    while(i < 3)
    {
     // CmdLCD(DISP_ON_CUR_ON);  
			key = KeyScan();

        if(key >= '0' && key <= '9')
        {
            digits[i] = key - '0';
            CharLCD(key);
						delay_ms(50);
            i++;
        }
        else if(key == '*')    // BACKSPACE
					{
            if(i > 0)
            {
                i--;
                CmdLCD(SHIFT_DISP_LEFT);   // cursor left
                CharLCD(' ');   // erase character
                CmdLCD(SHIFT_DISP_LEFT);   // cursor left again
            }
					}
				else if(key=='=')
					{
						if(i==2)
							break;
					}
		}
return digits[0]*10 + digits[1];
}

s32 read_single_digit()
{
		u8 key;
    s32 digits[1];
    s32 i = 0;

    while(i < 2)
    {
        key = KeyScan();

        if(key >= '0' && key <= '9')
        {
            digits[i] = key - '0';
            CharLCD(key);
						delay_ms(50);
            i++;
        }
				else if(key == '*')    // BACKSPACE
        {
            if(i > 0)
            {
                i--;
                CmdLCD(SHIFT_DISP_LEFT);   // cursor left
                CharLCD(' ');   // erase character
                CmdLCD(SHIFT_DISP_LEFT);   // cursor left again
            }
        }
				else if(key=='=')
				{
					if(i==1)
							break;
				}
	}
	return digits[0];
}


s32 read_four_digit()
{
		u8 key;
    s32 digits[4];
    s32 i = 0;

    while(i < 5)
    {
        key = KeyScan();
        if(key >= '0' && key <= '9')
        {
            digits[i] = key - '0';
            CharLCD(key);
						delay_ms(50);
            i++;
        }
        else if(key == '*')    // BACKSPACE
        {
            if(i > 0)
            {
                i--;
                CmdLCD(SHIFT_DISP_LEFT);   // cursor left
                CharLCD(' ');   // erase character
                CmdLCD(SHIFT_DISP_LEFT);   // cursor left again
            }
        }
				else if(key=='=')
				{
					if(i==4)
							break;
				}
		}
	return ((digits[0]*1000) + (digits[1]*100) + (digits[2]*10) + digits[3]);
}

void configure_medicine()
{
	u8 key;
label:while(med_count<3)
			{
				mh:
				CmdLCD(CLEAR_LCD);
				StrLCD("Medicine");
				CmdLCD(GOTO_LINE1_POS0+9);
				U32LCD(med_count+1);
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("Hour:(00-23)");
				CmdLCD(GOTO_LINE2_POS0+12);
				med[med_count].hour = read_two_digit();
	
				if(med[med_count].hour<0 || med[med_count].hour>23)
				{
					CmdLCD(CLEAR_LCD);
					StrLCD("Invalid Hour!");
					delay_ms(500);
					//StrLCD("             ");
					CmdLCD(CLEAR_LCD);
					goto mh;
				}
				mm:
				CmdLCD(CLEAR_LCD);
				StrLCD("Medicine");
				CmdLCD(GOTO_LINE1_POS0+9);
				U32LCD(med_count+1);
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("Minute:(00-59)");
				CmdLCD(GOTO_LINE2_POS0+14);
				med[med_count].min = read_two_digit();

				if(med[med_count].min<0 || med[med_count].min>59)
				{
					CmdLCD(CLEAR_LCD);
					StrLCD("Invalid Minute!");
					delay_ms(500);
					CmdLCD(CLEAR_LCD);
					goto mm;
				}

				med_count++;
				
		if(med_count<=2)
		{
		l:CmdLCD(CLEAR_LCD);
		StrLCD("'+'Add Medicine");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'='Stop setting!");
		key=KeyScan();
		if(key=='+')
		{
			goto label;
		}
		else if(key=='=')
		{
			return;
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid Option!");
			delay_us(300);
			goto l;
		}
		}
	}
    CmdLCD(CLEAR_LCD);
    StrLCD("Saved");
    delay_ms(500);
}

void alert_user()
{
    s32 t = 60;
		//u32 flag=0;
    CmdLCD(CLEAR_LCD);
    StrLCD("Take Medicine");

    while(t--)
    {
        IOSET0 = 1<<BUZZER;   // buzzer ON
        delay_ms(200);

        IOCLR0 = 1<<BUZZER;   // buzzer OFF
        delay_ms(200);

        if(ack_flag)      // Switch2 pressed
        {
          ack_flag = 0;
					buz_flag=0;
					IOCLR0 = 1<<BUZZER;
						
						break;
        }
    }
    IOCLR0 = 1<<BUZZER;
		CmdLCD(CLEAR_LCD);
		return;
}

void check_medicine_time(s32 h,s32 m)
{
    s32 i;
		for(i=0;i<med_count;i++)
    {
			//buz_flag=1;
        if(h==med[i].hour && m==med[i].min)
        {
						if(buz_flag)
						{
            alert_user();
						}
        }
    }
}

