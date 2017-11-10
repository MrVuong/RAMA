

/*
 * main.c
 * Control Interface
 * Senior Project ECPE 195
 * Fall 2017
 * Project Associates: Paul Vuong, Zachariah Abuelhaj, Amril D'Souza, Jonathan Samson
 */

#include <stdint.h>
#include "SYSCTL.h"
#include "OSC.c"
#include "GPIO.h"
#include "ADC.h"
#include "GPIO.c"
#include "ADC.c"

// Control interface system prototypes initialization
void initOSCPLL(void);
void initADC_I2C_UART_GPIO(void);
void initADC_SS(void);

int main(void)
{
	return 0;
}
