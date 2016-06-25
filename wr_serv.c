#include "wr_serv.h"

wrServ wrServs[] = 
{
 	{ WRPWMRatioSet,	0 },
	{ WRPWMRatioSet,	3 },
	{ WRPWMRatioSet,	2 },
	{ WRPWMRatioSet,	1 },
	{ WRPWMRatioSet,	4 },
	{ WRTimerRatioSet, 	7 },
	{ WRPWMRatioSet,	5 },
	{ WRTimerRatioSet,	6 }, 
        { WRPWMRatioSet,	8 }
};

unsigned long wrServTimerPeriod = 0;

void WRServInit()
{
	
	for(int i = 0; i < WR_SERV_COUNT; i++)
	{
	  	wrServ *serv = &wrServs[i];
		memset( serv->factor, 0, sizeof( serv->factor ) );
		serv->currentSignalDuration = 0;
		serv->isEnable = 0; //FALSE
	}
	WRServLoadSettings();
}

void WRServSetRatio(long id, long ratio)
{
	wrServ *serv = &wrServs[id];
	
	serv->currentSignalDuration = ratio;	
	serv->stepCount = 0;
}

void WRServSetEnable(long id, int isEnable)
{
	wrServ *serv = &wrServs[id];
	if( isEnable == 0 )
	{
		serv->setRatio( serv->arg1, 0 );
	}
	serv->isEnable = isEnable;		
}

long WRServPeriodByAngle(long id, long angle)
{
	wrServ *serv = &wrServs[id];  
	//
	// find valid settings
	//
	for(int i = 0; (i+1) < WR_SERV_FACTOR_SIZE; i++)
	  	if( serv->factor[i] != 0 && serv->factor[i+1] != 0 )
		{
  			//
			// it's obviously
			// consider function of control as liner function
			//
   		  	long dPeriod = serv->factor[i+1] - serv->factor[i];
			long prePeriod = serv->factor[i];
			long newPeriod = prePeriod + (dPeriod * (angle - i*WR_SERV_ANGULAR_FACTOR) ) / WR_SERV_ANGULAR_FACTOR;
			
			return newPeriod;
		}
	
	return 0;
}

void WRServSetAngleWithDelay(long id, long angle, long delay)
{
	wrServ *serv = &wrServs[id];  
	//
	// calculate delay 
	//
	long newPeriod = WRServPeriodByAngle( id, angle );
	serv->stepCount = delay * WR_SYS_TIMER_FREQUENCY / 1000;
	serv->stepSize = (newPeriod - serv->currentSignalDuration) / serv->stepCount;
	serv->finalSignalDuration = newPeriod;
}

void WRServSetAngle(long id, long angle)
{	
	wrServ *serv = &wrServs[id];
	serv->currentSignalDuration = WRServPeriodByAngle( id, angle );			
}

void HeadSet(long angle)
{	
	wrServ *serv = &wrServs[8];
	serv->currentSignalDuration = WRServPeriodByAngle( 8, angle );			
}

//
// set of servs in default position
//
void WRServSetDefault()
{
	for(int i = 0; i < WR_SERV_COUNT; i++)  	
	{
	  	wrServ *serv = &wrServs[i];
	  	long tempRatio = serv->factor[180 / WR_SERV_ANGULAR_FACTOR];
		if( tempRatio != 0 )
		{
			serv->currentSignalDuration = tempRatio;
			serv->isEnable = 1; //TRUE
		}
	}	
}

//
// deal with array of factors
//
void WRServDeleteFactor(long id)
{
  	wrServ *serv = &wrServs[id];
	memset(serv->factor, 0, sizeof serv->factor );
}
void WRServSaveFactor(long id, long angle)
{
  	wrServ *serv = &wrServs[id];
	int i = angle / WR_SERV_ANGULAR_FACTOR;
	
	serv->factor[i] = serv->currentSignalDuration;	
}

//
// save current settings of servs to flash memory
//
void WRServSaveSettings()
{
	wrServ *serv;
  
	WRFlashCleanBuffer();
	for(int i = 0; i < WR_SERV_COUNT; i++)
	{
	  	serv = &wrServs[i];
	  	WRFlashWriteToBuffer( (unsigned char*)serv->factor, sizeof( serv->factor ) );
	}
	WRFlashSaveBuffer(0);
}

void WRServLoadSettings()
{
	wrServ *serv;
  
	WRFlashCleanBuffer();
	WRFlashLoadBuffer(0);
	for(int i = 0; i < WR_SERV_COUNT; i++)
	{
	  	serv = &wrServs[i];
	  	WRFlashReadFromBuffer( (unsigned char*)serv->factor, sizeof( serv->factor ) );
	}	
	WRServSetDefault();	
}

//
//
//
void WRServTimerHandler()
{
  	//
  	// for any servo
  	//
	for(int i = 0; i < WR_SERV_COUNT; i++)  	
	{
	  	wrServ *serv = &wrServs[i];
				
		if( serv->stepCount > 0 )		  
		{
		  	serv->stepCount -= 1;
			serv->currentSignalDuration += serv->stepSize;
			/*if( serv->stepCount == 0 )
			  serv->currentSignalDuration = serv->finalSignalDuration;
			*/
		}
		
		if( serv->isEnable )
			serv->setRatio( serv->arg1, serv->currentSignalDuration );
	}
}

//
//
//
int  WRServIsMovementComplete()
{
  	for(int i = 0; i < WR_SERV_COUNT; i++)  	
	{
	  	wrServ *serv = &wrServs[i];				
		if( serv->isEnable && serv->stepCount > 0 )		  
			return 0; //FALSE
	}
	return 1; //TRUE
}
