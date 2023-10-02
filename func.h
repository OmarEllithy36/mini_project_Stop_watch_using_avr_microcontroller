/*
 * func.h
 *
 *  Created on: ???/???/????
 *      Author: Omar
 */

#ifndef FUNC_H_
#define FUNC_H_

#define SEG1 0x01
#define SEG2 0x02
#define SEG3 0x04
#define SEG4 0x08
#define SEG5 0x10
#define SEG6 0x20


void DDR_CONFG(void);
void Timer1_CONGF(void);
void Interrupt_CONFG(void);
void display_Seg(uint8 *const overFlow_ptr,uint8 *const num_display,uint8 seg_display);


#endif /* FUNC_H_ */
