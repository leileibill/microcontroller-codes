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

extern float duty_main = 0.5;		// duty ratio, between 0 to 1
extern int fsw = 200;		 	// switching frequency, in kHz

extern int period =1000;		// period of the PWM counters


extern float duty6,duty7,duty8,duty9,duty10,duty11;	// duty ratio of each pwm channel, between 0 and 
extern int phase6,phase7,phase8,phase9,phase10,phase11;	// phase shift of each pwm channel
//
// Functions
//

void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitEPwm3Example(void);
void InitEPwm6(void);
void InitEPwm7(void);
void InitEPwm8(void);
void InitEPwm9(void);
void InitEPwm10(void);
void InitEPwm11(void);

void InitPWMs_dickson(void);


#endif




