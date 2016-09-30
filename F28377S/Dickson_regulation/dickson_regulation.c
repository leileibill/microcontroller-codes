//###########################################################################
//
// FILE:    epwm_deadband_c28.c
//
// TITLE:   Check PWM Dead-Band
//
//! \addtogroup cpu01_example_list
//! <h1> EPWM dead band control (epwm_deadband)</h1>
//!
//! During the test, monitor ePWM1, ePWM2, and/or ePWM3 outputs
//! on a scope.
//!
//! - ePWM1A is on GPIO0
//! - ePWM1B is on GPIO1
//! - ePWM2A is on GPIO2
//! - ePWM2B is on GPIO3
//! - ePWM3A is on GPIO4
//! - ePWM3B is on GPIO5
//!
//! This example configures ePWM1, ePWM2 and ePWM3 for:
//! - Count up/down
//! - Deadband
//!
//! 3 Examples are included:
//! - ePWM1: Active low PWMs
//! - ePWM2: Active low complementary PWMs
//! - ePWM3: Active high complementary PWMs
//!
//! Each ePWM is configured to interrupt on the 3rd zero event.
//! When this happens the deadband is modified such that
//! 0 <= DB <= DB_MAX.  That is, the deadband will move up and
//! down between 0 and the maximum value.
//!
//! View the EPWM1A/B, EPWM2A/B and EPWM3A/B waveforms
//! via an oscilloscope
//
//
//###########################################################################
// $TI Release: F2837xS Support Library v200 $
// $Release Date: Tue Jun 21 13:52:16 CDT 2016 $
// $Copyright: Copyright (C) 2014-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "F28x_Project.h"
#include "dickson_regulation.h"

//
// Globals
//
//Uint32 EPwm1TimerIntCount;
//
//Uint16 EPwm1_DB_Direction;


//
// Function Prototypes
//

__interrupt void epwm1_isr(void);


//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xS_SysCtrl.c file.
//
    InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xS_Gpio.c file and
// illustrates how to set the GPIO to its default state.
//
//    InitGpio();

//
// enable PWM1, PWM2 and PWM3
//
    CpuSysRegs.PCLKCR2.bit.EPWM1=1;			// strange, I have not enabled 4-11 but they all work...
    CpuSysRegs.PCLKCR2.bit.EPWM2=1;
    CpuSysRegs.PCLKCR2.bit.EPWM3=1;

//
// For this case just init GPIO pins for ePWM1, ePWM2, ePWM3
// These functions are in the F2837xS_EPwm.c file
//

    InitEPwm6Gpio();
    InitEPwm7Gpio();
    InitEPwm8Gpio();
    InitEPwm9Gpio();
    InitEPwm10Gpio();
    InitEPwm11Gpio();

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xS_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xS_DefaultIsr.c.
// This function is found in F2837xS_PieVect.c.
//
    InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
    EALLOW; // This is needed to write to EALLOW protected registers
//    PieVectTable.EPWM1_INT = &epwm1_isr;

    PieVectTable.ADCA1_INT = &adca1_isr; //function for ADCA interrupt 1

    EDIS;   // This is needed to disable write to EALLOW protected registers

//
// Initialize the ePWMs for gate signals
//
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0;		// make EPWM clock the same as sys clock
    InitPWMs_dickson();

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =1;
    EDIS;

//
// Initialize the ADC and ePWM1 to to trigger SOC
//
	InitADC();		// configure adc

	Init_EPWM_for_ADC();	// configure ePWM

	SetupADCEpwm(0);	//Setup the ADC for ePWM triggered conversions on channel 0


//
// Step 5. User specific code, enable interrupts:
// Initialize counters:
//
//    EPwm1TimerIntCount = 0;
//    EPwm2TimerIntCount = 0;
//    EPwm3TimerIntCount = 0;

    ClearBuffer();		// Initialize adc result buffer
//
// Enable interrupts
//
//    IER |= M_INT3;	//Enable CPU INT3 which is connected to EPWM1-3 INT:
    IER |= M_INT1; //Enable group 1 interrupts

//
// Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//
//    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
//    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
//    PieCtrlRegs.PIEIER3.bit.INTx3 = 1;

    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// Start ePWM
//
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =1;
    EDIS;

//
// Step 6. IDLE loop. Just sit and loop forever (optional):
//
    for(;;)
    {
        asm ("          NOP");
    }
}

//
// epwm1_isr - EPWM1 ISR
//
__interrupt void epwm1_isr(void)
{

	// do something

//    EPwm1TimerIntCount++;

    //
    // Clear INT flag for this timer
    //
    EPwm1Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}



//
// End of file
//
