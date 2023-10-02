/*
 * func.c
 *
 *  Created on: ???/???/????
 *      Author: Omar Ellithy
 */

#include "avr/io.h"
#include <avr/interrupt.h>
#include "util/delay.h"
#include "data_types.h"
#include "func.h"


void DDR_CONFG(void)
{
	DDRC |= 0x0F;     //make first 4 pins in PORT C as output
	PORTC &= 0xF0;    // set first 4 pins in PORT C to 0V as initial value

	DDRA |= 0x3F;     // make pins from PA0 ~ PA5 as output
	PORTA &= 0xC0;    // set pins from PA0 ~ PA5 to 0V as initial value

	/*activate internal pull up resistor at pin PD2*/
	DDRD &= ~(1<<PD2);
	PORTD |= (1<<PD2);

	/*activate internal pull up resistor at pin PB2*/
	DDRD &= ~(1<<PB2);
	PORTD |= (1<<PB2);

	DDRD &= ~(1<<PD3);   //set Pin PD3 as input

}

void Timer1_CONGF(void)
{
	TCNT1 = 0;   // Set timer1 initial count to zero

	OCR1A = 1000;   // Set the Compare value to 1000

	TIMSK |= (1<<OCIE1A);  // Enable Timer1 Compare A Interrupt

	/* Configure timer control register TCCR1A
	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1 FOC1B=0
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
	TCCR1A |= (1<<FOC1A);

	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Prescaler = F_CPU/1024 CS10=1 CS11=0 CS12=1
	 */
	TCCR1B |= (1<<WGM12) | (1<<CS10) | (1<<CS12);
}

void Interrupt_CONFG(void)
{
	SREG |= (1<<7);  // set I bit

	/*Enable Interrupt 1,2,3 request*/
	GICR |= (1<<INT1) | (1<<INT0) | (1<<INT2);

	/* Configure Interrupt 0,1 Sense Control
	 * 1. INT0 set at Falling Edge
	 * 2. INT1 set at Raising Edge
	 */
	MCUCR |= (1<<ISC10) | (1<<ISC11) | (1<<ISC01);

	MCUCSR &= ~(1<<ISC2);  // set INT2 with Falling Edge
}


void display_Seg(uint8 *const overFlow_ptr,uint8 *const num_display,uint8 seg_display)
{
	PORTA = seg_display;   //// Enable 7-SEG required and turn off the other

	/* if the seg required is the first one */
	if(seg_display == 0x01){
		// check if num reach over flow or not*/
		if(*num_display == 10){
			*num_display = 0;     // rest num
			*overFlow_ptr = 1;    // set over flow flag to increment the next SEG
		}

		PORTC = (PORTC & 0xF0) | ( (*num_display) & 0x0F);  // insert num in PORTC
		_delay_ms(3);
		return;  // exit from function
	}

	/* Check the previous 7-SEG over Flow if true increment num */
		if(*overFlow_ptr)
		{
			(*num_display)++;
		/* check if num reach over flow or not*/
			if(*num_display == 10){
				*num_display = 0;   // rest num
				PORTC = (PORTC & 0xF0) | ( (*num_display) & 0x0F); // insert num in PORTC
				_delay_ms(3);
			  /* leave over flow set to 1 to increment the next SEG*/
			}else{

				PORTC = (PORTC & 0xF0) | ( (*num_display) & 0x0F);  // insert num in PORTC
				_delay_ms(3);
				*overFlow_ptr = 0;  // rest over flow flag
			}
			return;
		}

	/* if the previous SEG did not over flow */
	PORTC = (PORTC & 0xF0) | ( (*num_display) & 0x0F);  // insert num in PORTC
	_delay_ms(3);

}
