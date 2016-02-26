/*timer function and interrupt hanlers
 * */

#include "kernel/timer.h"
#include "kernel/tty.h"
#include "kernel/irq.h"
#include "include/stdtypes.h"

//define initializer
void init_timer(uint16_t frequency){
	
	uint16_t divisor = PIT_IN_F / frequency;
	
	outb(PIC1_DATA,0xf0); //init
	outb(PIT_PORT_CNTRL,0x36);
	//send the frequency divisor
	//lower 2byte
	outb(PIT_PORT_DATA,(divisor&0xff));
	outb(PIT_PORT_DATA,(divisor>>8&0xff));
}

//define timer interrupt handler
uint32_t count=0;
void timer_handler(){
	//send End Of Interrupt to master
	outb(PIC1,EOI);
	if(count%1000 == 0){
	write_dec_at(count,70,24);
	terminal_writeat("s",73,24);
	}
	count++;
	
	return;
}
