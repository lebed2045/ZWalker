//*****************************************************************************
//
// Module contain functions for work with pwm and timer in pwm mode
//
//*****************************************************************************

#ifndef __WR_PWMTIMER_H__
#define __WR_PWMTIMER_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include "wobot.h"  

void WRPWMInit();  
void WRTimerInit();

void WRPWMRatioSet(long id, long ratio);
void WRTimerRatioSet(long id, long ratio);

void WRPWMTimerEnable();
void WRPWMTimerDisable();


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WR_PWMTIMER_H__
