#include "wr_leg.h"

wrLeg wrLegs[4];

void WRLegInit()
{
		wrLegs[0].idA = 0;
		wrLegs[0].idB = 1;
		wrLegs[1].idA = 2;
		wrLegs[1].idB = 3;
		wrLegs[2].idA = 4;
		wrLegs[2].idB = 5;
		wrLegs[3].idA = 7; //old 6
		wrLegs[3].idB = 6; //old 7
}
/*
void WRLegSit(char cLeg, long angle)
{
   	long id = cLeg-'a';	
	if( !(0 <= id && id < 4) ) return;
	
	long idA = wrLegs[id].idA;
	long idB = wrLegs[id].idB;	

	if( -90 <= angle && angle <= 90 )
	{
		WRServSetAngle( idA, 180+angle );
		WRServSetAngle( idB, 180-angle );
	}	
}
*/
typedef struct 
{
	const char* name;
	int A_angle;
	int A_delay;
	int B_angle;
	int b_delay;
	int isSymmetric;
} motion;

motion table_of_motions[] = 
{
  {0}
};


void WRLegDo(char cLeg,const char *state, long angle, long delay )
{
  	long id = cLeg-'a';	
	if( !(0 <= id && id < 4) ) return;
	
	long idA = wrLegs[id].idA;
	long idB = wrLegs[id].idB;	
	
	if( angle == 0 )
		angle = 45;
	
	if( delay == 0 )
	  	delay = 750;
	if( strcmp(state,"stand") == 0 )
	{
		WRServSetAngleWithDelay( idA, 180, delay );
  		WRServSetAngleWithDelay( idB, 180, delay );
	}
	if( strcmp(state,"stand2") == 0 )
	{
  		if( cLeg == 'a' || cLeg == 'b' ){
			WRServSetAngleWithDelay( idA, 180 - angle, delay );
		} else
  		if( cLeg == 'c' || cLeg == 'd' ){
			WRServSetAngleWithDelay( idA, 180 + angle, delay );		
		}
		WRServSetAngleWithDelay( idB, 180, delay );
	} else
	  
   	if( strcmp(state,"pre_forward_1") == 0 )
	{
		WRServSetAngleWithDelay( idA, 180 + angle + 15, delay );
		WRServSetAngleWithDelay( idB, 180 - angle - 15, delay/2 );
	} else	  
	  
  	if( strcmp(state,"forward") == 0 )
	{
		WRServSetAngleWithDelay( idA, 180 + angle, delay );
		WRServSetAngleWithDelay( idB, 180 - angle, delay );
	} else
	  
	if( strcmp(state,"pre_back_1") == 0 )
	{
		WRServSetAngleWithDelay( idA, 180 - angle - 15, delay );
		WRServSetAngleWithDelay( idB, 180 + angle + 15, delay/2 );
	} else	  
	  
  	if( strcmp(state,"back") == 0 )
	{
		WRServSetAngleWithDelay( idA, 180 - angle, delay );
		WRServSetAngleWithDelay( idB, 180 + angle, delay );
	} else
	  
   	if( strcmp(state,"sit") == 0 )	  
	{
		if( cLeg == 'a' || cLeg == 'b' ){
			WRServSetAngleWithDelay( idA, 180 - angle, delay );
			WRServSetAngleWithDelay( idB, 180 + angle, delay );
		} else
  		if( cLeg == 'c' || cLeg == 'd' ){
			WRServSetAngleWithDelay( idA, 180 + angle, delay );
			WRServSetAngleWithDelay( idB, 180 - angle, delay );
		}
	} else	
	  
   	if( strcmp(state,"sit2") == 0 )	  
	{
	  	int b = 90 - angle;
		if( cLeg == 'a' || cLeg == 'b' ){
			WRServSetAngleWithDelay( idA, 90 + b, delay );
			WRServSetAngleWithDelay( idB, 360 - 2*b, delay );
		} else
  		if( cLeg == 'c' || cLeg == 'd' ){
			WRServSetAngleWithDelay( idA, 270 - b, delay );
			WRServSetAngleWithDelay( idB, 0 + 2*b, delay );
		}
	} else
	
  	if( strcmp(state,"sit3") == 0 )	  
	{
	  	int b = 90 + angle;
		if( cLeg == 'a' || cLeg == 'b' ){
			WRServSetAngleWithDelay( idA, 90 + b, delay );
			WRServSetAngleWithDelay( idB, 360 - 2*b, delay );
		} else
  		if( cLeg == 'c' || cLeg == 'd' ){
			WRServSetAngleWithDelay( idA, 270 - b, delay );
			WRServSetAngleWithDelay( idB, 0 + 2*b, delay );
		}
	} else
	  
  	if( strcmp(state,"knee") == 0 )	  
	{
		WRServSetAngleWithDelay( idA, 180 + angle, delay );
		WRServSetAngleWithDelay( idB, 180 + (90-angle), delay );
	} 
	  
}

int  WRLegIsMovementComplete()
{
	return WRServIsMovementComplete();
}

