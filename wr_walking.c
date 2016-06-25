#include "wr_walking.h"

typedef struct 
{
	int step;
	char leg;
	const char* state;
} step_of_walking;


step_of_walking walk_forward[] = 
{
  {1,'b',"forward"},
  {1,'c',"forward"},
  
  {2,'a',"back"},
  {2,'d',"back"},
  
  {3,'b',"stand"},
  {3,'c',"stand"},
  
  {4,'a',"pre_forward_1"},
  {4,'d',"pre_forward_1"},
  
  {5,'a',"forward"},
  {5,'d',"forward"},
  
  {6,'b',"back"},
  {6,'c',"back"},

  {7,'a',"stand"},
  {7,'d',"stand"},
  
  {8,'b',"pre_forward_1"},
  {8,'c',"pre_forward_1"},
  
  {0,0,0}  
};

step_of_walking walk_back[] = 
{
  {1,'b',"back"},
  {1,'c',"back"},
  
  {2,'a',"forward"},
  {2,'d',"forward"},
  
  {3,'b',"stand"},
  {3,'c',"stand"},
  
  {4,'a',"pre_back_1"},
  {4,'d',"pre_back_1"},
  
  {5,'a',"back"},
  {5,'d',"back"},
  
  {6,'b',"forward"},
  {6,'c',"forward"},

  {7,'a',"stand"},
  {7,'d',"stand"},
  
  {8,'b',"pre_back_1"},
  {8,'c',"pre_back_1"},
  
  {0,0,0}
};

step_of_walking walk_left[] = 
{
  {1,'c',"forward"},
  {2,'a',"back"},  
  {3,'c',"stand"},  
  {4,'a',"pre_forward_1"},  
  {5,'a',"forward"},  
  {6,'c',"back"},
  {7,'a',"stand"},  
  {8,'c',"pre_forward_1"},
  
  {1,'b',"back"},  
  {2,'d',"forward"},  
  {3,'b',"stand"},  
  {4,'d',"pre_back_1"},  
  {5,'d',"back"},  
  {6,'b',"forward"},
  {7,'d',"stand"},  
  {8,'b',"pre_back_1"},
  
   {0,0,0}
};

step_of_walking walk_right[] = 
{
  {1,'b',"forward"},
  {2,'d',"back"},
  {3,'b',"stand"},
  {4,'d',"pre_forward_1"},
  {5,'d',"forward"},
  {6,'b',"back"},
  {7,'d',"stand"},
  {8,'b',"pre_forward_1"},

  {1,'c',"back"},
  {2,'a',"forward"},  
  {3,'c',"stand"},  
  {4,'a',"pre_back_1"},  
  {5,'a',"back"},
  {6,'c',"forward"},
  {7,'a',"stand"},  
  {8,'c',"pre_back_1"},
 
  {0,0,0}
};


long wrWalkingState = 0;
int isWalk;
long wrWalkingAngle;
long wrWalkingDelay;
long wrWalkingType;
step_of_walking* wrWalkingAlgo;
long wrWalkingAlgoLength;

void WRWalkingInit()
{
	isWalk = 0; //FALSE
	wrWalkingAngle = 45;
	wrWalkingDelay = 500;
	wrWalkingType = 0;
	wrWalkingAlgo = 0;
	wrWalkingAlgoLength = 0;
}

void WRWalkingSetAngle( long angle )
{
	wrWalkingAngle = angle;
}
void WRWalkingSetDelay( long delay )
{
	wrWalkingDelay = delay;	
}

void WRWalkingTakeState( long state )
{
  	long angle = wrWalkingAngle;
	long delay = wrWalkingDelay;
	step_of_walking* temp = wrWalkingAlgo;
			
	for(; temp->step; temp++ )
	{
		if( temp->step == state )
		{
			WRLegDo( temp->leg, temp->state, angle, delay );
			/*
			char str[15];
			strcpy(str,temp->state);
			str[0] = temp->leg;			
			UARTStrSend( UART0_BASE, str );			
			*/
		}
	}
}

//
// Walking
//

void WRWalkingStart(long mode)
{
	wrWalkingState = 1;
	isWalk = 1; //TRUE
	
	wrWalkingType = mode;
	//find walking algorithm by name	
	if( wrWalkingType == WR_WALKING_FORWARD )
		wrWalkingAlgo = walk_forward;
	if( wrWalkingType == WR_WALKING_BACK )
		wrWalkingAlgo = walk_back;	
	if( wrWalkingType == WR_WALKING_RIGHT )
		wrWalkingAlgo = walk_right;
	if( wrWalkingType == WR_WALKING_LEFT )
		wrWalkingAlgo = walk_left;	
	
	//calc length of walking algo
	wrWalkingAlgoLength = 0;
	for(step_of_walking* temp = wrWalkingAlgo; temp->state; temp++)
	{
		if( temp->step > wrWalkingAlgoLength ) 
			wrWalkingAlgoLength = temp->step;
	}
}

void WRWalkingStop()
{
	isWalk = 0; //FALASE
}

void WRWalkingDo(const char *command,  long angle, long delay)
{
	if( angle > 0 )
	  	WRWalkingSetAngle( angle );
	if( delay > 0 )
		WRWalkingSetDelay( delay );
		
	if( strcmp(command,"forward") == 0 )
		WRWalkingStart( WR_WALKING_FORWARD );
	if( strcmp(command,"back") == 0 )
		WRWalkingStart( WR_WALKING_BACK );
	if( strcmp(command,"right") == 0 )
		WRWalkingStart( WR_WALKING_RIGHT );
	if( strcmp(command,"left") == 0 )
		WRWalkingStart( WR_WALKING_LEFT );
	if( strcmp(command,"stop") == 0 )
		WRWalkingStop();
}


void WRWalkingTimerHandler()
{
	if( isWalk && WRLegIsMovementComplete() )
	{
		WRWalkingTakeState( wrWalkingState );
		
		wrWalkingState++;
		
		if( wrWalkingState > wrWalkingAlgoLength )
		  wrWalkingState = 1;
	}
}
