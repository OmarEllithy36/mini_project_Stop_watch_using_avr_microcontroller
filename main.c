/*
 * main.c
 *
 *  Created on: ???/???/????
 *      Author: Omar Ellithy
 */

#include "avr/io.h"
#include <avr/interrupt.h>
#include "util/delay.h"
#include "data_types.h"
#include "func.h"

uint8 num1 = 0;
uint8 num2 = 0;
uint8 num3 = 0;
uint8 num4 = 0;
uint8 num5 = 0;
uint8 num6 = 0;
uint8 INT0_flag = 0;
uint8 overFlow = 0;


int main(void)
{
 /* Configure DDR & Interrupt & Timer1 Registers*/

	DDR_CONFG();
	Interrupt_CONFG();
	Timer1_CONGF();

	while(1)
	{
		if(INT0_flag == 1){
			/* reset all num to rest the stop watch */

			num1 = 0; num2 = 0; num3 = 0; num4 = 0;	num5 = 0; num6 = 0;
			INT0_flag = 0;
		}

		display_Seg(&overFlow, &num1, SEG1);
		display_Seg(&overFlow, &num2, SEG2);
		display_Seg(&overFlow, &num3, SEG3);
		display_Seg(&overFlow, &num4, SEG4);
		display_Seg(&overFlow, &num5, SEG5);
		display_Seg(&overFlow, &num6, SEG6);

		if(num1==9 && num2==9 && num3==9 && num4==9 && num5==9 && num6==9){
		 /* check if the Stop Watch reach max, if true reset */

			num1 = 0; num2 = 0; num3 = 0; num4 = 0;	num5 = 0; num6 = 0;
		}

	}

}


ISR(TIMER1_COMPA_vect)
{
	num1++;
}

ISR(INT0_vect)
{
	INT0_flag = 1;
}

ISR(INT1_vect)
{
	TIMSK &= ~(1<<OCIE1A);
}

ISR(INT2_vect)
{
	TIMSK |= (1<<OCIE1A);
}
