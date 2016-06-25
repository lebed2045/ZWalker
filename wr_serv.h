//*****************************************************************************
//
// wr_serv.h - Walking Robot's Engine
//
//*****************************************************************************

#ifndef __WR_SERV_H__
#define __WR_SERV_H__

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

  
#define WR_SERV_ANGULAR_FACTOR 90
#define WR_SERV_FACTOR_SIZE 4
#define WR_SERV_COUNT 9

  
typedef void (*wrServFunction)(long,long);

typedef struct{
  	//
  	// pointer on WRPWMSetRation or WRTimerSetRation
  	//
	wrServFunction setRatio;
	//
	// First argument to setRation function
	//
	long arg1;		

	//
	// factor[i] - duty factor of PWM correcpond to i*WR_SERV_ANGULAR_FACTOR
	//
	long factor[WR_SERV_FACTOR_SIZE];
	
	//
	// 
	//
	long currentSignalDuration;
	long currentAngle;
	
	//
	// for slow movement
	//
	long stepSize;
	long stepCount;
	long finalSignalDuration;
	
	int isEnable;
} wrServ;

extern wrServ wrServs[];

void WRServTimerHandler();
void WRServInit();

void WRServSetAngleWithDelay(long id, long angle, long delay);
void WRServSetAngle(long id, long angle);
void HeadSet(long angle);
void WRServSetRatio(long id, long ratio);

void WRServSetEnable(long id, int isEnable);

int  WRServIsMovementComplete();

void WRServSaveFactor(long id, long angle);
void WRServDeleteFactor(long id);

void WRServSaveSettings();
void WRServLoadSettings();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WR_SERV_H__
