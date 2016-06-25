//*****************************************************************************
//
// wr_console.h - Walking Robot's Console
//
//*****************************************************************************

#ifndef __WR_SONAR_H__
#define __WR_SONAR_H__

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

int GetDistFromSonar();
void SendPingToSonar();
void SonarInit();
int GetStatus();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif 
