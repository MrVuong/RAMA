/*
 * SYSCTL.h
 *
 *  Created on: Oct 30, 2017
 *      Author: vuong
 */

#ifndef SYSCTL_H_
#define SYSCTL_H_

#include <stdint.h>

#define SYSCTL                      (((volatile uint32_t *)0x400FE000)) //System control base address

enum {
        SYSCTL_RCGCGPIO         =   (0x608 >> 2),   //RCGC GPIO offset
#define SYSCTL_RCGCGPIO_PORTB       (1 << 1)        //Enable run mode gating clock control
#define SYSCTL_RCGCGPIO_PORTC       (1 << 2)        //for ports: B, C, D, and E
#define SYSCTL_RCGCGPIO_PORTD       (1 << 3)
#define SYSCTL_RCGCGPIO_PORTE       (1 << 4)
        SYSCTL_RCGCI2C          =   (0x620 >> 2),   //RCGC I2C offset
#define SYSCTL_RCGCI2C3             (1 << 3)        //Enable I2C3 module
        SYSCTL_RCGCADC          =   (0x638 >> 2),   //RCGC ADC offset
#define SYSCTL_RCGCADC0             (1 << 0)        //Enable ADC0 module
        SYSCTL_RCGCUART         =   (0x618 >> 2),   //RCGC UART offset
#define SYSCTL_RCGCUART1            (1 << 1)        //Enable UART1 module
};

enum {
        SYSCTL_RCC_R            =   (0x060 >> 2),   //Run-mode clock configuration register
#define SYSCTL_RCC_USESYSDIV        (1 << 22)       //System clock is used undivided
#define SYSCTL_RCC_XTAL             (0x15 << 6)     //16MHz crystal value
        SYSCTL_RCC2_R           =   (0x070 >> 2),   //Run-mode clock 2 configuration register
#define SYSCTL_RCC2_BYPASS2         (1 << 11)       //Disable the PLL Bypass2, the system clock is the PLL output clock
                                                    //divided by the divisor specified by SYSDIV2.
                                                    //See Table 5-5 on page 223 for programming guidelines.
                                                    //Note: The ADC must be clocked from the PLL or directly from a
                                                    //16-MHz clock source to operate properly.
#define SYSCTL_RCC2_USERCC2         ((uint32_t)1<<31)//The RCC2 register fields override the RCC register fields.
#define SYSCTL_RCC2_OSCSRC2         (0x1 << 4)      //Select PIOSC precision internal oscillator.
#define SYSCTL_RCC2_PWRDN2          (1 << 13)       //Clear this bit to power and enable PLL and output
#define SYSCTL_RCC2_SYSDIV2         (0x02 << 23)    //System Clock Divisor 2
#define SYSCTL_RCC2_SYSDIV2LSB      (1 << 22)       //Additional LSB for SYSDIV2
#define SYSCTL_RCC2_SYSDIV400       (1 << 30)       //Enabling, Append the SYSDIV2LSB bit to the SYSDIV2 field to create a
                                                    //7 bit divisor using the 400 MHz PLL output, see Table
                                                    //5-6 on page 224.
        SYSCTL_RIS_R            =   (0x050 >> 2)    //Raw interrupt status register
#define SYSCTL_RIS_PLLLRIS          (1 << 6)        //PLL Lock Raw Interrupt Status
};

#endif /* SYSCTL_H_ */
