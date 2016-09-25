#include "F28x_Project.h"
#include "dickson_regulation.h"


float duty_main = 0.5;		// duty ratio, between 0 to 1
int fsw = 200;		 	// switching frequency, in kHz
float split = 0.75;		// split phase duty ratio
// deadtime is realized through phase shift, since we are not using the B channels
int deadtime_R = 0;		// rising edge deadtime in number of clock cycles
int deadtime_F = 0;		// falling edge deadtime, currently not used

int period =1000;		// period of the PWM counters
float duty6,duty7,duty8,duty9,duty10,duty11;	// duty ratio of each pwm channel
int phase6,phase7,phase8,phase9,phase10,phase11;	// phase shift of each pwm channel
int offset;			// offset of phase shift to compensate for propagation delay
//
// InitEPwm1Example - Initialize EPWM1 configuration
//
void InitEPwm1()
{
    EPwm1Regs.TBPRD = 6000;                       // Set timer period
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                     // Clear counter

    //
    // Setup TBCLK
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm1Regs.CMPA.bit.CMPA = duty6;

    //
    // Set actions
    //
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
    EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Active Low PWMs - Setup Deadband
    //
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm1Regs.DBRED.bit.DBRED = deadtime_R;
    EPwm1Regs.DBFED.bit.DBFED = deadtime_R;
    EPwm1_DB_Direction = DB_UP;

    //
    // Interrupt where we will change the Deadband
    //
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm1Regs.ETSEL.bit.INTEN = 1;               // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;          // Generate INT on 3rd event
}



void InitPWMs_dickson()
{

	period = sys_clock/fsw;
	
	duty6 = 0.5*duty_main*period;		// Ph1
	duty7 = duty6;		// Ph2
	duty8 = 0.5*duty_main*split*period;			// Ph5
	duty9 = duty8;				// Ph6
	duty10 = 1 - duty6;				// Ph3
	duty11 = 1 - duty6;				// Ph4

	phase6 = 0;			// Ph1
	phase7 = 0.5*period;		// Ph2
	phase8 = phase6;	// Ph5
	phase9 = phase7;	// Ph6
	duty10 = phase& + offset;		// Ph3
	duty11 = phase6 + offset;		// Ph4
	
			
	InitEPwm6();
	InitEPwm7();
	InitEPwm8();
	InitEPwm9();
	InitEPwm10();
	InitEPwm11();
}
void InitEPwm6()
{
    EPwm6Regs.TBPRD = period;                       // Set timer period
    EPwm6Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm6Regs.TBCTR = 0x0000;                     // Clear counter

    //
    // Setup TBCLK
    //
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm6Regs.CMPA.bit.CMPA = duty6*period;

    //
    // Set actions
    //
    EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
    EPwm6Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm6Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
    EPwm6Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Active Low PWMs - Setup Deadband
    //
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm6Regs.DBRED.bit.DBRED = deadtime_R;
    EPwm6Regs.DBFED.bit.DBFED = deadtime_R;
    EPwm1_DB_Direction = DB_UP;

}

void InitEPwm7()
{
    EPwm7Regs.TBPRD = period;                       // Set timer period
    EPwm7Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm7Regs.TBCTR = 0x0000;                     // Clear counter

    //
    // Setup TBCLK
    //
    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm7Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm7Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm7Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm7Regs.CMPA.bit.CMPA = duty7*period;

    //
    // Set actions
    //
    EPwm7Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
    EPwm7Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm7Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
    EPwm7Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Active Low PWMs - Setup Deadband
    //
    EPwm7Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm7Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    EPwm7Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm7Regs.DBRED.bit.DBRED = deadtime_R;
    EPwm7Regs.DBFED.bit.DBFED = deadtime_R;
    EPwm1_DB_Direction = DB_UP;


}
void InitEPwm8()
{
    EPwm8Regs.TBPRD = period;                       // Set timer period
    EPwm8Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm8Regs.TBCTR = 0x0000;                     // Clear counter

    //
    // Setup TBCLK
    //
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm8Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm8Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm8Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm8Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm8Regs.CMPA.bit.CMPA = duty8*period;

    //
    // Set actions
    //
    EPwm8Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
    EPwm8Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm8Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
    EPwm8Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Active Low PWMs - Setup Deadband
    //
    EPwm8Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm8Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    EPwm8Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm8Regs.DBRED.bit.DBRED = deadtime_R;
    EPwm8Regs.DBFED.bit.DBFED = deadtime_R;
    EPwm1_DB_Direction = DB_UP;


}
void InitEPwm9()
{
    EPwm9Regs.TBPRD = period;                       // Set timer period
    EPwm9Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm9Regs.TBCTR = 0x0000;                     // Clear counter

    //
    // Setup TBCLK
    //
    EPwm9Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm9Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm9Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm9Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm9Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm9Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm9Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm9Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm9Regs.CMPA.bit.CMPA = duty9*period;

    //
    // Set actions
    //
    EPwm9Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
    EPwm9Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm9Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
    EPwm9Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Active Low PWMs - Setup Deadband
    //
    EPwm9Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm9Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    EPwm9Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm9Regs.DBRED.bit.DBRED = deadtime_R;
    EPwm9Regs.DBFED.bit.DBFED = deadtime_R;
    EPwm1_DB_Direction = DB_UP;


}
void InitEPwm10()
{
    EPwm10Regs.TBPRD = period;                       // Set timer period
    EPwm10Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm10Regs.TBCTR = 0x0000;                     // Clear counter

    //
    // Setup TBCLK
    //
    EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm10Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm10Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm10Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm10Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm10Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm10Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm10Regs.CMPA.bit.CMPA = duty10*period;

    //
    // Set actions
    //
    EPwm10Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
    EPwm10Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm10Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
    EPwm10Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Active Low PWMs - Setup Deadband
    //
    EPwm10Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm10Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    EPwm10Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm10Regs.DBRED.bit.DBRED = deadtime_R;
    EPwm10Regs.DBFED.bit.DBFED = deadtime_R;
    EPwm1_DB_Direction = DB_UP;

}
void InitEPwm11()
{
    EPwm11Regs.TBPRD = period;                       // Set timer period
    EPwm11Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm11Regs.TBCTR = 0x0000;                     // Clear counter

    //
    // Setup TBCLK
    //
    EPwm11Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm11Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm11Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm11Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm11Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm11Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm11Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm11Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm11Regs.CMPA.bit.CMPA = duty11*period;

    //
    // Set actions
    //
    EPwm11Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
    EPwm11Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm11Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
    EPwm11Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Active Low PWMs - Setup Deadband
    //
    EPwm11Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm11Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    EPwm11Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm11Regs.DBRED.bit.DBRED = deadtime_R;
    EPwm11Regs.DBFED.bit.DBFED = deadtime_R;
    EPwm1_DB_Direction = DB_UP;

}
