//rtc_edit.c
#include <lpc21xx.h>
#include "lcd.h"
#include "kpm.h"
#include "medicine.h"
#include "rtc_defines.h"
#include "rtc_edit.h"
#include "LCD_defines.h"
#include "delay.h"
#include "medicine.h"

void edit_rtc_time()
{
    s32 hh,mm,ss,d,m,y,dow;
		u8 key;
    CmdLCD(CLEAR_LCD);
    StrLCD("Edit Time");
		delay_ms(300);

    CCR = RTC_RESET;      //stop rtc

	h:CmdLCD(GOTO_LINE1_POS0);
		StrLCD("'='hour '-'skip");
		key=KeyScan();
		if(key=='-')
		{
				goto min;
		}
		else if(key=='=')
		{
		hour:CmdLCD(CLEAR_LCD);
    StrLCD("Hour:(00-23)");
		CmdLCD(GOTO_LINE2_POS0);
    hh = read_two_digit();
		if(hh<0 || hh>23)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid hour!");
			delay_ms(100);
			goto hour;
		}
		HOUR = hh;
		l1:CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto min;
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_ms(300);
			goto l1;
		}
	}
	else 
	{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_us(300);
			goto h;
	}
	
	min:CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
		StrLCD("'='min '-'skip");
		key=KeyScan();
		if(key=='-')
		{
				goto sec;
		}
		else if(key == '=')
		{
		min1:CmdLCD(CLEAR_LCD);
    StrLCD("Minute:(00-59)");
		CmdLCD(GOTO_LINE2_POS0);
    mm = read_two_digit();
		if(mm<0 || mm>59)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid Minute!");
			delay_ms(100);
			goto min1;
		}
		MIN=mm;
		l2:CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto sec;
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_ms(300);
			goto l2;
		}
	}
	else 
	{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_us(300);
			goto min;
	}
	
		
	sec:CmdLCD(CLEAR_LCD);
		StrLCD("'='sec '-'skip");
		key=KeyScan();
    if(key=='-')
		{
				goto D;
		}
		else if(key=='=')
		{
		sec1:CmdLCD(CLEAR_LCD);
    StrLCD("Second:(00-59)");
    CmdLCD(GOTO_LINE2_POS0);
		ss = read_two_digit();
		if(ss<0 || ss>59)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid second!");
			delay_ms(100);
			goto sec1;
		}
		SEC=ss;
		l3:CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto D;
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_ms(300);
			goto l3;
		}
	}
	else 
	{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_us(300);
			goto sec;
	}
	
	D:CmdLCD(CLEAR_LCD);
		StrLCD("'='date '-'skip");
	  key=KeyScan();
		if(key=='-')
		{
				goto M;
		}
		else if(key=='=')
		{
		D1:CmdLCD(CLEAR_LCD);
			StrLCD("Edit Date");
			delay_ms(100);
			CmdLCD(CLEAR_LCD);
		StrLCD("Date:(01-31)");
		CmdLCD(GOTO_LINE2_POS0);
		d=read_two_digit();
		if(d<1 || d>31)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid date!");
			delay_ms(100);
			goto D1;
		}
		DOM=d;
		l4:CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto M;
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_ms(300);
			goto l4;
		}
	}
	else 
	{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_us(300);
			goto D;
	}
	
		
	M:CmdLCD(CLEAR_LCD);
		StrLCD("'='month '-'skip");
		key=KeyScan();
    if(key=='-')
		{
				goto Y;
		}
		else if(key=='=')
		{
		M1:CmdLCD(CLEAR_LCD);
		StrLCD("Month:(01-12)");
		CmdLCD(GOTO_LINE2_POS0);
		m=read_two_digit();
		if(m<1 || m>12)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid month!");
			delay_ms(100);
			goto M1;
		}
		MONTH=m;
		l5:CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto Y;
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_ms(300);
			goto l5;
		}
	}
	else 
	{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_us(300);
			goto M;
	}
	
		
	Y:CmdLCD(CLEAR_LCD);
		StrLCD("'='year '-'skip");
		key=KeyScan();
    if(key=='-')
		{
				goto Dow;
		}
		else if(key=='=')
		{
		Y1:CmdLCD(CLEAR_LCD);
		StrLCD("Year(2025-2030)");
		CmdLCD(GOTO_LINE2_POS0);
		y=read_four_digit();
		if(y<2025 || y>2030)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid year!");
			delay_ms(100);
			goto Y1;
		}
		YEAR=y;
		l6:CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto Dow;
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_ms(300);
			goto l6;
		}
	}
	else 
	{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_us(300);
			goto Y;
	}
	
	Dow:CmdLCD(CLEAR_LCD);
		StrLCD("'='Day '-'skip");
		key=KeyScan();
    if(key=='-')
		{
				return;
		}
		else if(key=='=')
		{
		Dow1:CmdLCD(CLEAR_LCD);
		StrLCD("Day:(0-6)");
		CmdLCD(GOTO_LINE2_POS0);
		dow=read_single_digit();
		if(dow<0 || dow>6)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid day!");
			delay_ms(100);
			goto Dow1;
		}
		DOW=dow;  
	}
	else 
	{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid key!");
			delay_us(300);
			goto Dow;
	}
	
    CCR = RTC_ENABLE;

    CmdLCD(CLEAR_LCD);
    StrLCD("Clock Updated");
    delay_ms(500);
		return;
}

