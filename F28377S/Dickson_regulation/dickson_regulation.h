/*
 *
 *  Created on: Sep 24, 2016
 *      Author: Yutian Lei
 */

#ifndef DICKSON_REGULATION_H_
#define DICKSON_REGULATION_H_

//
// Defines
//

//#define _LAUNCHXL_F28377S


#define sys_clock 200000		// system clock frequency, in kHz
#define EPWM1_MAX_DB   0x03FF
#define EPWM2_MAX_DB   0x03FF
#define EPWM3_MAX_DB   0x03FF
#define EPWM1_MIN_DB   0
#define EPWM2_MIN_DB   0
#define EPWM3_MIN_DB   0
#define DB_UP          1
#define DB_DOWN        0

//
// Global variables
//
extern Uint32 EPwm1TimerIntCount;
extern Uint32 EPwm2TimerIntCount;
extern Uint32 EPwm3TimerIntCount;
extern Uint16 EPwm1_DB_Direction;
extern Uint16 EPwm2_DB_Direction;
extern Uint16 EPwm3_DB_Direction;

extern float duty_main;		// duty ratio, between 0 to 1
extern int fsw;		 	// switching frequency, in kHz
extern float split;		// split phase duty ratio
extern int deadtime_R;		// rising edge deadtime in number of clock cycles
extern int deadtime_F;		// falling edge deadtime

extern int period;		// period of the PWM counters
extern float duty6,duty7,duty8,duty9,duty10,duty11;	// duty ratio of each pwm channel, between 0 and 
extern int phase6,phase7,phase8,phase9,phase10,phase11;	// phase shift of each pwm channel
extern int offset;			// offset of phase shift to compensate for propagation delay

//
// Functions
//

void InitEPwm1(void);
void InitEPwm6(void);
void InitEPwm7(void);
void InitEPwm8(void);
void InitEPwm9(void);
void InitEPwm10(void);
void InitEPwm11(void);

void InitPWMs_dickson(void);


#endif




