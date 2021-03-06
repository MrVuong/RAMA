/*
 * OSC.c
 *
 *  Created on: Nov 5, 2017
 *      Author: vuong
 */

#include <stdint.h>
#include "SYSCTL.h"

void initOSCPLL(void) {

    //The PLL is configured using direct register writes to the RCC/RCC2 register. If the RCC2 register
    //is being used, the USERCC2 bit must be set and the appropriate RCC2 bit/field is used. The steps
    //required to successfully change the PLL-based system clock are (pp.231):
    SYSCTL[SYSCTL_RCC2_R] |= SYSCTL_RCC2_USERCC2;       //Extend RCC register fields to RCC2
                                                        //Bitfields in RCC2 with similar functions to
                                                        //RCC will take precedence if USERCC2 bit is set.

    //1. Bypass the PLL and system clock divider by setting the BYPASS bit and clearing the USESYS
    //bit in the RCC register, thereby configuring the microcontroller to run off a "raw" clock source
    //and allowing for the new PLL configuration to be validated before switching the system clock
    //to the PLL.
    SYSCTL[SYSCTL_RCC_R]  |= SYSCTL_RCC2_BYPASS2;       //Bypass PLL while configuring
    SYSCTL[SYSCTL_RCC2_R] &= ~(SYSCTL_RCC2_BYPASS2);    //Bypass2 in RCC2 needs to be cleared to configure
                                                        //DIV400 and SYSDIV2LSB bitfields in RCC2.
    SYSCTL[SYSCTL_RCC_R]  &= ~(SYSCTL_RCC_USESYSDIV);   //Raw clock source used while configuring PLL.

    //2. Select the crystal value (XTAL) and oscillator source (OSCSRC), and clear the PWRDN bit in
    //RCC/RCC2. Setting the XTAL field automatically pulls valid PLL configuration data for the
    //appropriate crystal, and clearing the PWRDN bit powers and enables the PLL and its output.
    SYSCTL[SYSCTL_RCC_R]  |= SYSCTL_RCC_XTAL;           //16Mhz crystal oscillator chosen for PLL
    SYSCTL[SYSCTL_RCC2_R] |= SYSCTL_RCC2_OSCSRC2;       //16MHz PIOSC source selected
    SYSCTL[SYSCTL_RCC2_R] &= ~SYSCTL_RCC2_PWRDN2;       //Enable PLL and output

    //3. Select the desired system divider (SYSDIV) in RCC/RCC2 and set the USESYS bit in RCC. The
    //SYSDIV field determines the system frequency for the microcontroller.
    //SYSDIV2 divided the 400MHz PLL down to 200MHz
    SYSCTL[SYSCTL_RCC2_R] |= SYSCTL_RCC2_SYSDIV2 | SYSCTL_RCC2_SYSDIV400;
    //SYSDIV400 and SYSDIV2LSB offer a divisor of 2.5 and brings the 200MHz signal to 80MHz
    SYSCTL[SYSCTL_RCC2_R] &= ~SYSCTL_RCC2_SYSDIV2LSB;
    //80MHz signal is used undivided, system clock
    SYSCTL[SYSCTL_RCC_R]  |= SYSCTL_RCC_USESYSDIV;

    //4. Wait for the PLL to lock by polling the PLLLRIS bit in the Raw Interrupt Status (RIS) register.
    while (!(SYSCTL[SYSCTL_RIS_R] & SYSCTL_RIS_PLLLRIS));

    //5. Enable use of the PLL by clearing the BYPASS bit in RCC/RCC2.
    SYSCTL[SYSCTL_RCC2_R] &= ~SYSCTL_RCC2_BYPASS2;
}

