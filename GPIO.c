/*
 * GPIO.c
 *
 *  Created on: Nov 4, 2017
 *      Author: vuong
 */

#include <stdint.h>
#include "SYSCTL.h"
#include "GPIO.h"
#include "ADC.h"

void initADC_I2C_UART_GPIO(void) {

    //1. Enable the ADC, I2C, and UART clock using the RCGCADC/RCGCI2C/RCGCUART register (see page 352,348,344).
    //                                  ADC0
    SYSCTL[SYSCTL_RCGCADC]  |= SYSCTL_RCGCADC0;
    //                                  I2C3
    SYSCTL[SYSCTL_RCGCI2C]  |= SYSCTL_RCGCI2C3;
    //                                  UART1
    SYSCTL[SYSCTL_RCGCUART] |= SYSCTL_RCGCUART1;

    //2. Enable the clock to the appropriate GPIO modules via the RCGCGPIO register (see page 340).
    //To find out which GPIO ports to enable, refer to “Signal Description” on page 801.
    //                         UART1 Rx(PB0) Tx(PB1) |UART1 CTS(PC5) RTS(PC4)|I2C3 SDA(PD1) SCL(PD0) |ADC0 AIN0 AIN1 AIN2 AIN8 AIN9
    //                                               |                       |                       |     PE3  PE2  PE1  PE5  PE4
    SYSCTL[SYSCTL_RCGCGPIO] |= SYSCTL_RCGCGPIO_PORTB | SYSCTL_RCGCGPIO_PORTC | SYSCTL_RCGCGPIO_PORTD | SYSCTL_RCGCGPIO_PORTE;
    SYSCTL[SYSCTL_RCGCGPIO] |= SYSCTL_RCGCGPIO_PORTB | SYSCTL_RCGCGPIO_PORTC | SYSCTL_RCGCGPIO_PORTD | SYSCTL_RCGCGPIO_PORTE;

    //Enable high-performance buses
    SYSCTL[GPIO_HBCTL] |= SYSCTL_RCGCGPIO_PORTB | SYSCTL_RCGCGPIO_PORTC | SYSCTL_RCGCGPIO_PORTD | SYSCTL_RCGCGPIO_PORTE;

    //                          U1Rx        U1Tx
    GPIO_PORTB[GPIO_DIR] |= ~GPIO_PIN_0 | GPIO_PIN_1;
    //                          U1RTS       U1CTS
    GPIO_PORTC[GPIO_DIR] |= GPIO_PIN_4 | ~GPIO_PIN_5;
    //                          I2C3SCL     I2C3SDA
    GPIO_PORTD[GPIO_DIR] |= GPIO_PIN_0 | ~GPIO_PIN_1;
    //Make port PE1, PE2, PE3, PE4, and PE5 input pins
    //                          AIN2,        AIN1,        AIN0,         AIN9,       AIN8
    GPIO_PORTE[GPIO_DIR] &= ~(GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);

    //3. Set the GPIO AFSEL bits for the input pins (see page 671). To determine which GPIOs to
    //configure, see Table 23-4 on page 1344.
    //                          U1Rx        U1Tx
    GPIO_PORTB[GPIO_AFSEL] |= GPIO_PIN_0 | GPIO_PIN_1;
    //                          U1RTS       U1CTS
    GPIO_PORTC[GPIO_AFSEL] |= GPIO_PIN_4 | GPIO_PIN_5;
    //                          I2C3SCL     I2C3SDA
    GPIO_PORTD[GPIO_AFSEL] |= GPIO_PIN_0 | GPIO_PIN_1;
    //                          AIN2,        AIN1,        AIN0,         AIN9,       AIN8
    GPIO_PORTE[GPIO_AFSEL] |= GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;

    //GPIO_PORTD has special considerations. This pin is configured as a GPIO by default but is locked and
    //can only be reprogrammed by unlocking the pin in the GPIOLOCK register and uncommitting it by setting the
    //GPIOCR register.
    GPIO_PORTD[GPIO_LOCK] |= 0x4C4F434B;
    GPIO_PORTD[GPIO_CR]   |= GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_PORTD[GPIO_LOCK] |= 0;

    //4. Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
    //GPIO Digital Enable (GPIODEN) register (see page 682).
    //Enable the digital signals for UART1 and I2C3
    //                          U1Rx        U1Tx
    GPIO_PORTB[GPIO_DEN] |= GPIO_PIN_0 | GPIO_PIN_1;
    //                          U1RTS       U1CTS
    GPIO_PORTC[GPIO_DEN] |= GPIO_PIN_4 | GPIO_PIN_5;
    //                        I2C3SCL     I2C3SDA
    GPIO_PORTD[GPIO_DEN] |= GPIO_PIN_0 | GPIO_PIN_1;
    //                          AIN2,        AIN1,        AIN0,         AIN9,       AIN8
    GPIO_PORTE[GPIO_DEN] &= ~(GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);

    //4. Enable the I2CSDA pin for open-drain operation. See page 676.
    //                       I2C3SCL     I2C3SDA
    GPIO_PORTD[GPIO_ODR] |= GPIO_PIN_0 | GPIO_PIN_1;

    //4. Configure the GPIO(UART) current level and/or slew rate as specified for the mode selected (see
    //page 673 and page 681).
    //                          U1Rx        U1Tx
    GPIO_PORTB[GPIO_DR8R] |= GPIO_PIN_0 | GPIO_PIN_1;
    //                         U1RTS       U1CTS
    GPIO_PORTC[GPIO_DR8R] |= GPIO_PIN_4 | GPIO_PIN_5;
    //                          U1Rx        U1Tx
    GPIO_PORTB[GPIO_SLR]  |= GPIO_PIN_0 | GPIO_PIN_1;
    //                         U1RTS       U1CTS
    GPIO_PORTC[GPIO_SLR]  |= GPIO_PIN_4 | GPIO_PIN_5;

    //5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
    //the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block.
    //                          AIN2,        AIN1,        AIN0,         AIN9,       AIN8
    GPIO_PORTE[GPIO_AMSEL] |= GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;

    //5. Configure the PMCn fields in the GPIOPCTL register to assign the I2C signals to the appropriate
    //pins. See page 688 and Table 23-5 on page 1351.
    // Need PMC3 enabled for I2C3SCL(PD0) and I2C3SDA(PD1)
    GPIO_PORTD[GPIO_PCTL] &= ~((0xF<<(4*0)) | (0xF<<(4*1)));
    GPIO_PORTD[GPIO_PCTL] |= (1<<(4*0)) | (1<<(4*1));

    //5. Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate
    //pins (see page 688 and Table 23-5 on page 1351).
    // Need PMC1 enabled for U1Rx(PB0) and U1Tx(PB1)
    GPIO_PORTB[GPIO_PCTL] &= ~((0xF<<(4*0)) | (0xF<<(4*1)));
    GPIO_PORTB[GPIO_PCTL] |= (1<<(4*0)) | (1<<(4*1));
    // Need PMC8 enabled for handshaking signals U1RTS(PC4) and U1CTS(PC5)
    GPIO_PORTC[GPIO_PCTL] &= ~((0xF<<(4*4)) | (0xF<<(4*5)));
    GPIO_PORTC[GPIO_PCTL] |= (1<<(4*4)) | (1 <<(4*5));

    //6. If required by the application, reconfigure the sample sequencer priorities in the ADCSSPRI
    //register. The default configuration has Sample Sequencer 0 with the highest priority and Sample
    //Sequencer 3 as the lowest priority.
    // initADC_SS initial ADC sample sequencer

}








