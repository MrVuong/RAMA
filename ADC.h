/*
 * ADC.h
 *
 *  Created on: Oct 29, 2017
 *      Author: vuong
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

#define ADC0              (((volatile uint32_t *) 0x40038000))

enum {
        //Register map and offsets
        ADC_CC          = (0xFC8 >> 2),     //ADC clock configuration register
        ADC_CTL         = (0x038 >> 2),     //ADC control register
        ADC_ACTSS       = 0,                //ADC active sample sequencer register
        ADC_USTAT       = (0x018 >> 2),     //ADC underflow status register
        ADC_SSPRI       = (0x020 >> 2),     //ADC sample sequence priority register
        ADC_SPC         = (0x024 >> 2),     //ADC sample phase control
        ADC_PP          = (0xFC0 >> 2),     //ADC peripheral properties register
        ADC_PC          = (0xFC4 >> 2),     //ADC peripheral configuration register
        ADC_TSSEL       = (0x01C >> 2),     //ADC trigger source select register

        ADC_RIS         = (0x004 >> 2),     //ADC raw interrupt status register
        ADC_IM          = (0x008 >> 2),     //ADC interrupt mask register
        ADC_ISC         = (0X00C >> 2),     //ADC interrupt status and clear register
        ADC_DCISC       = (0x034 >> 2),     //ADC digital comparator interrupt status and clear register

        ADC_SAC         = (0x030 >> 2),     //ADC sample average control register, hardware averager

        ADC_EMUX        = (0x014 >> 2),     //ADC event multiplexer register, trigger events

        ADC_SSMUX0      = (0x040 >> 2),     //ADC sample sequence input multiplexer select 0 register
        ADC_SSCTL0      = (0x044 >> 2),     //ADC sample sequence control 0 register
        ADC_SSFSTAT0    = (0x04C >> 2),     //ADC sample sequence FIFO 0 status register

        ADC_SSFIFO0     = (0x048 >> 2),     //ADC sample sequence result FIFO 0 register
        ADC_SSFIFO1     = (0x068 >> 2),     //ADC sample sequence result FIFO 1 register
        ADC_SSFIFO2     = (0x088 >> 2),     //ADC sample sequence result FIFO 2 register
        ADC_SSFIFO3     = (0x0A8 >> 2),     //ADC sample sequence result FIFO 3 register

        ADC_DCRIC       = (0xD00 >> 2),     //ADC digital comparator reset initial conditions register
        ADC_SSOP0       = (0x050 >> 2),     //ADC sample sequence 0 operation register
        ADC_SSDC0       = (0x054 >> 2),     //ADC sample sequence 0 digital comparator select register

        /*ADC_DCCTL0      = (0xE00 >> 2),     //ADC digital comparator control register
        ADC_DCCTL1      = (0xE04 >> 2),
        ADC_DCCTL2      = (0xE08 >> 2),
        ADC_DCCTL3      = (0xE0C >> 2),
        ADC_DCCTL4      = (0xE10 >> 2),
        ADC_DCCTL5      = (0xE14 >> 2),
        ADC_DCCTL6      = (0xE18 >> 2),
        ADC_DCCTL7      = (0xE1C >> 2),

        ADC_DCCMP0      = (0xE40 >> 2),     //ADC digital comparator range register
        ADC_DCCMP1      = (0xE44 >> 2),
        ADC_DCCMP2      = (0xE48 >> 2),
        ADC_DCCMP3      = (0xE4C >> 2),
        ADC_DCCMP4      = (0xE50 >> 2),
        ADC_DCCMP5      = (0xE54 >> 2),
        ADC_DCCMP6      = (0xE58 >> 2),
        ADC_DCCMP7      = (0xE5C >> 2),*/
};

enum {
        //ADC registers' configuration bits
        ADC_CS          = (0x0 << 0),       //ADC Clock Source
                                            //The following table specifies the clock source that generates the ADC
                                            //clock input, see Figure 5-5 on page 222.
                                            //Either the 16-MHz system clock (if the PLL bypass is in
                                            //effect) or the 16 MHz clock derived from PLL ÷ 25 (default).
                                            //Note that when the PLL is bypassed, the system clock must
                                            //be at least 16 MHz.
        ADC_RSL         = (0x12 << 18),     //Set ADC sample resolution (12-bit resolution).
        ADC_MSR         = (0x1 << 0),       //Set ADC sample rate.
                                            //Value Description
                                            //0x0 Reserved
                                            //0x1 125 ksps
                                            //0x2 Reserved
                                            //0x3 250 ksps
                                            //0x4 Reserved
                                            //0x5 500 ksps
                                            //0x6 Reserved
                                            //0x7 1 Msps
                                            //0x8 - 0xF Reserved

        ADC_ASEN0       = (1 << 0),         //ADC active sample sequencer 0 allows up to 8 sample channels
        ADC_EM0         = (0xF << 0),       //ADC trigger event, in this option, sample continuously(Always)
        ADC_MUX0        = (0x3 << 0),       //MUX0, PE3 - assign port pins to muxes
        ADC_MUX1        = (0x2 << 4),       //MUX1, PE2
        ADC_MUX2        = (0x1 << 8),       //MUX2, PE1
        ADC_MUX3        = (0x5 << 12),      //MUX3, PE5
        ADC_MUX4        = (0x4 << 16),      //MUX4, PE4

        ADC_END0        = (0x6 << 0),       //indicates end of sample sequence and sample interrupt enabled, 1st sample, MUX0
        ADC_END1        = (0x6 << 4),       //indicates end of sample sequence and sample interrupt enabled, 2nd sample, MUX1
        ADC_END2        = (0x6 << 8),       //indicates end of sample sequence and sample interrupt enabled, 3rd sample, MUX2
        ADC_END3        = (0x6 << 12),      //indicates end of sample sequence and sample interrupt enabled, 4th sample, MUX3
        ADC_END4        = (0x6 << 16),      //indicates end of sample sequence and sample interrupt enabled, 5th sample, MUX4

        ADC_SS0_MASK0   = (1 << 0),         //ADC interrupt mask enabled
};

#endif /* ADC_H_ */
