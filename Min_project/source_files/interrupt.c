#include <lpc21xx.h>
#include "interrupt.h"
#include "interrupt_defines.h"
#include "types.h"

volatile s32 setup_flag = 0;
volatile s32 ack_flag = 0;

void EINT0_ISR(void) __irq
{
        setup_flag = 1;
        EXTINT = 1<<0;
        VICVectAddr = 0;
}

void EINT1_ISR(void) __irq
{
        ack_flag = 1;
        EXTINT = 1<<1;
        VICVectAddr = 0;
}

void interrupt_init()
{
//cfg p0.1,p0.3 as EINT0 and EINT1 input pins
//clear bits 2&3 and 6&7 without affecting other bits
PINSEL0&=((u32)~3<<2)|((u32)~3<<6);
//update bits 2,3 and 6,7 for EINT0,EINT1 pin functions
PINSEL0|=EINT0_INPUT_PIN|EINT1_INPUT_PIN;
//cfg VIC peripheral/block
//allow EINT0,EINT1 as irq type
//VICintSelect=0;//default
//Enable EINT0,EINT1 through channels
VICIntEnable=1<<EINT0_VIC_CHNO|1<<EINT1_VIC_CHNO;
//cfg EINT0 as v.irq with highest priority(0)
VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
//load ent0_isr address into LUT
VICVectAddr0=(u32)EINT0_ISR;
//cfg EINT1 as v.irq with next highest priority
VICVectCntl1=(1<<5)|EINT1_VIC_CHNO;
//load eint1_isr address int LUT
VICVectAddr1=(u32)EINT1_ISR;
//cfg EINT0,EINT1 via EXT INT Peripheral
//Enable EINT0,EINT1
//EXTINT=0;//Default
//Cfg EINT0,EINT1 as edge trig interrupt
EXTMODE=(1<<1)|(1<<0);
//cfg EINT0,EINT1 as falling edge triggered
//EXTPOLAR=0;//Default
//cfg status led pin functions EINT0,EINT1 as gpio out
IODIR1|=(1<<EINT0_STATUS_LED);
}
