/*
 * GPIO.h
 *
 *  Created on: Oct 30, 2017
 *      Author: vuong
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#define GPIO_PORTB                  (((volatile uint32_t *) 0x40059000))    //Ports B, C, D, and E
#define GPIO_PORTC                  (((volatile uint32_t *) 0x4005A000))    //using advanced high
#define GPIO_PORTD                  (((volatile uint32_t *) 0x4005B000))    //performance peripheral
#define GPIO_PORTE                  (((volatile uint32_t *) 0x4005C000))    //bus

enum {
        GPIO_DATA               =   0,              //GPIO data register
        GPIO_HBCTL              =   (0x06C >> 2),    //GPIO high-performance bus control
        GPIO_AFSEL              =   (0x420 >> 2),   //GPIO alternate function selection
        GPIO_PCTL               =   (0x52C >> 2),   //GPIO port control register
        GPIO_ADCCTL             =   (0x530 >> 2),   //GPIO ADC control
        GPIO_DIR                =   (0x400 >> 2),   //GPIO direction register
        GPIO_PUR                =   (0x510 >> 2),   //GPIO pull-up select register
        GPIO_PDR                =   (0x514 >> 2),   //GPIO pull-down select register
        GPIO_ODR                =   (0x50C >> 2),   //GPIO open drain select register
        GPIO_DEN                =   (0x51C >> 2),   //GPIO digital enable register
        GPIO_AMSEL              =   (0x528 >> 2),   //GPIO analog mode select register
        GPIO_LOCK               =   (0x520 >> 2),   //GPIO lock register
        GPIO_CR                 =   (0x524 >> 2),   //GPIO commit register
        GPIO_DR8R               =   (0x508 >> 2),   //GPIO 8-mA Drive Select register
        GPIO_SLR                =   (0x518 >> 2)    //GPIO Slew Rate Control Select register
};

enum {
        GPIO_PIN_0              = (1 << 0),         //Implement in register bit fields
        GPIO_PIN_1              = (1 << 1),         //or to assign port pins on launch pad.
        GPIO_PIN_2              = (1 << 2),         //Expand if need be.
        GPIO_PIN_3              = (1 << 3),
        GPIO_PIN_4              = (1 << 4),
        GPIO_PIN_5              = (1 << 5),
        GPIO_PIN_6              = (1 << 6),
        GPIO_PIN_7              = (1 << 7),
        GPIO_ALLPINS            = 0xFF
};


#endif /* GPIO_H_ */
