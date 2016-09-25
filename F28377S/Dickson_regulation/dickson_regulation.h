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
#define EPWM1_MAX_DB   0x03FF
#define EPWM2_MAX_DB   0x03FF
#define EPWM3_MAX_DB   0x03FF
#define EPWM1_MIN_DB   0
#define EPWM2_MIN_DB   0
#define EPWM3_MIN_DB   0
#define DB_UP          1
#define DB_DOWN        0

//
// Globals
//
extern Uint32 EPwm1TimerIntCount;
extern Uint32 EPwm2TimerIntCount;
extern Uint32 EPwm3TimerIntCount;
extern Uint16 EPwm1_DB_Direction;
extern Uint16 EPwm2_DB_Direction;
extern Uint16 EPwm3_DB_Direction;


void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitEPwm3Example(void);
void InitEPwm6(void);
void InitEPwm7(void);
void InitEPwm8(void);
void InitEPwm9(void);
void InitEPwm10(void);
void InitEPwm11(void);

#endif




