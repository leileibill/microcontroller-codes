/*
 * dickson_adc.h
 *
 *  Created on: Sep 30, 2016
 *      Author: pilawa_group
 */

#ifndef DICKSON_ADC_H_
#define DICKSON_ADC_H_

#include "F28x_Project.h"
#include "dickson_regulation.h"


//
// Defines
//
#define RESULTS_BUFFER_SIZE 256

//
// Globals
//
extern Uint16 AdcaResults[RESULTS_BUFFER_SIZE];
extern Uint16 resultsIndex;
extern volatile Uint16 bufferFull;




void InitADC(void);
void Init_EPWM_for_ADC(void);
void SetupADCEpwm(Uint16 channel);
void ClearBuffer(void);

// Interrupt handlers
interrupt void adca1_isr(void);

#endif /* DICKSON_ADC_H_ */
