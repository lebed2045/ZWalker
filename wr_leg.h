//*****************************************************************************
//
// wr_leg.h - Walking Robot's Legs
//
//*****************************************************************************

#ifndef __WR_LEG_H__
#define __WR_LEG_H__

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

typedef struct{
  	//
  	// shoulder joint / hip
  	//
	long idA;
	//
	// elbow / knee
	//
	long idB;
	
} wrLeg;

extern wrLeg wrLegs[];

void WRLegInit();
void WRLegDo(char cLeg,const char *state, long angle, long delay);
void WRLegSit(char cLeg, long angle);
int  WRLegIsMovementComplete();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WR_LEG_H__
