//*****************************************************************************
//
//						WRobot == Walking Robot
// 
// This is was a part of revision 6852 of the EK-LM3S811 Firmware Package.
//
//*****************************************************************************

#include "wobot.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif


//*****************************************************************************
//
// The interrupt handler for the SysTick timer interrupt.
//
//*****************************************************************************
void SysTickIntHandler(void)
{
	WRServTimerHandler();	
	WRWalkingTimerHandler();
}


//*****************************************************************************
//
//                            Walking Robot
//
//*****************************************************************************
int main(void)
{
    //
    // Set the clocking to run directly from the crystal.
    //
	//Caution! All current settings depend from 6MHz frqequency of clocking!!!
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_6MHZ);
		
    /*=============================SysTick===================================*/
	SysTickPeriodSet( SysCtlClockGet() / WR_SYS_TIMER_FREQUENCY );		
	IntPrioritySet( FAULT_SYSTICK, 0 );
	SysTickIntEnable();
	SysTickEnable();	
    /*=======================================================================*/	
	
	/*=============================USER CODE=================================*/
	WRPWMInit();
	WRTimerInit();
	WRFlashInit();
	WRServInit();
	WRLegInit();
	WRUART0Init();
	WRUART1Init();
	WRConsoleInit();
        SonarInit();
	/*=======================================================================*/
    /*===============================OLED====================================*/
    //
    // Initialize the OLED display and write status.
    //
   // Display96x16x1Init(false);
    /*=======================================================================*/

        
        

        

	while(1)
    {
      
     if (GetStatus()==3) WRSendDistance(GetDistFromSonar());
       
	  	//=================blink==========================
	
	  	//================================================		
    }
}
