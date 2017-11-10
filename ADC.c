/*
 * ADC.c
 *
 *  Created on: Oct 31, 2017
 *      Author: vuong
 */

#include <stdint.h>
#include "ADC.h"

void initADC_SS(void) {

        //Set ADC clock to run off 16MHz clock derived from PLL
        ADC0[ADC_CC] &= ADC_CS;
        //Indicate the ADC resolution and max sample rate.
        ADC0[ADC_PP] |= ADC_RSL | ADC_MSR;
        //Specifies the ADC resolution in run, sleep or deep sleep modes.
        ADC0[ADC_PP] |= ADC_MSR;

        //1. Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
        //ADCACTSS register. Programming of the sample sequencers is allowed without having them
        //enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
        //event were to occur during the configuration process.
        //Disable active sample sequencer 0 prior to configuration.
        ADC0[ADC_ACTSS] &= ~ADC_ASEN0;

        //2. Configure the trigger event for the sample sequencer in the ADCEMUX register.
        //ADC will continuously sample.
        ADC0[ADC_EMUX] = ADC_EM0;

        //3. When using a PWM generator as the trigger source, use the ADC Trigger Source Select
        //(ADCTSSEL) register to specify in which PWM module the generator is located. The default
        //register reset selects PWM module 0 for all generators.
        // N/A PWM trigger not used.

        //4. For each sample in the sample sequence, configure the corresponding input source in the
        //ADCSSMUXn register.
        ADC0[ADC_SSMUX0] = ADC_MUX0 | ADC_MUX1 | ADC_MUX2 | ADC_MUX3 | ADC_MUX4;

        //5. For each sample in the sample sequence, configure the sample control bits in the corresponding
        //nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
        //is set. Failure to set the END bit causes unpredictable behavior.
        ADC0[ADC_SSCTL0] = ADC_END0 | ADC_END1 | ADC_END2 | ADC_END3 | ADC_END4;

        //6. If interrupts are to be used, set the corresponding MASK bit in the ADCIM register.
        ADC0[ADC_IM] = ADC_SS0_MASK0;

        //7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
        //register.
        ADC0[ADC_ACTSS] |= ADC_ASEN0;

}


