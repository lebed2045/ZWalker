//*****************************************************************************
//
// wr_walking.h - Walking module
//
//*****************************************************************************

#ifndef __WR_WALKING_H__
#define __WR_WALKING_H__

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

#define WR_WALKING_FORWARD 0
#define WR_WALKING_BACK 1
#define WR_WALKING_RIGHT 2
#define WR_WALKING_LEFT 3
  
void WRWalkingTimerHandler();
  
void WRWalkingInit();
void WRWalkingTakeState( long state );

/*
void WRWalkingStart(long mode);
void WRWalkingStop();
void WRWalkingSetAngle( long angle );
void WRWalkingSetDelay( long delay );
*/

void WRWalkingDo(const char *command,  long angle, long delay);


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WR_WALKING_H__
