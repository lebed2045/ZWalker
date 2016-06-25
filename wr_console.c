//*****************************************************************************
//
// wr_console.c - implementataion of the Walking Robot's Console
//
//*****************************************************************************
#include "wr_console.h"

//
// Some standard keys
//
const char WR_CONSOLE_ENTER[] = {'\r','\n',0};

//
//	the current base of uart
//
unsigned long ulBase;


//
//	return argument with prefix
//	for example:
//		WRReadLongWithPrefixFormListOfArgs(
//		4, {"bar","foo","-a10","abacaba"},"-a", &answer)
//		answer is 10
//
void WRReadLongWithPrefixFormArgs(int argc, char *argv[], char* prefix,long *answer)
{
	int prefix_len = strlen(prefix);
	for(int i = 0; i < argc; i++)
	{
		if( strlen(argv[i]) > prefix_len)
		{
		  	int cmp = 0; // is equivalent 
		  	for(int j = 0; j < prefix_len; j++)
				if( argv[i][j] != prefix[j] ) cmp = -1;
			if( cmp == 0 )
			{
				*answer = atol( argv[i] + prefix_len );
				return;
			}				
		}
	}
}

long WRLongArgWithPrefixFormArgs(int argc, char* argv[], char* prefix, long default_result)
{
  	long result = default_result;
	for(int i = 0; i < argc; i++)
	{
		if( strcmp(argv[i],prefix) == 0 )
		{
			if( i+1 < argc )
				result = atol( argv[i+1] );
		}
	}
	return result;	
}

int WRCommandServsOff(int argc, char *argv[])
{
	long mask = WRLongArgWithPrefixFormArgs(argc, argv, "-m", (1<<WR_SERV_COUNT)-1);	
	for(int i = 0; i < WR_SERV_COUNT; i++)
		if( (1<<i)&mask )
		{
			WRServSetEnable( i, 0 );		
		}
	//WRPWMTimerDisable();	
	return 0;
}

int WRCommandServsOn(int argc, char *argv[])
{
	long mask = WRLongArgWithPrefixFormArgs(argc, argv, "-m", (1<<WR_SERV_COUNT)-1);	
  	for(int i = 0; i < WR_SERV_COUNT; i++)
	  	if( (1<<i)&mask )
		{
			WRServSetEnable( i, 1 );
		}
	//WRPWMTimerEnable();	
	return 0;
}



//
// shortcuts
//
int WRCommandLinkDo(int argc, char *argv[])
{
	WRWalkingDo("stop", 0, 0);  		

	long angle = 45;
	long delay = 250;
	int mask = 15;		
	if( strcmp(argv[0],"stand2") == 0 )
		angle = 30;
	if( strcmp(argv[0],"knee") == 0 )
		mask = 3;
	angle = WRLongArgWithPrefixFormArgs(argc, argv, "-a", angle);
	delay = WRLongArgWithPrefixFormArgs(argc, argv, "-d", delay);
	mask = WRLongArgWithPrefixFormArgs(argc, argv, "-m", mask);	

	//	
	for(int i = 0; i < 4; i++)
		if( (1<<i) & mask )
		{
			WRLegDo( 'a'+i, argv[0], angle, delay );
		}
	return 0;
}

//
// do smth
//
int WRCommandDo(int argc, char *argv[])
{  		
	WRWalkingDo("stop", 0, 0);  		

	long angle = 45;
	long delay = 250;
	int mask = 15;		
	if( strcmp(argv[1],"stand2") == 0 )
		angle = 30;
	if( strcmp(argv[1],"knee") == 0 )
		mask = 3;
	angle = WRLongArgWithPrefixFormArgs(argc, argv, "-a", angle);
	delay = WRLongArgWithPrefixFormArgs(argc, argv, "-d", delay);
	mask = WRLongArgWithPrefixFormArgs(argc, argv, "-m", mask);	

	//	
	for(int i = 0; i < 4; i++)
		if( (1<<i) & mask )
		{
			WRLegDo( 'a'+i, argv[1], angle, delay );
		}
	return 0;
}


int WRCommandLinkGo(int argc, char *argv[])
{
	long angle = 30;
	long delay = 300;
	if( strcmp(argv[0],"left") == 0 || strcmp(argv[0],"right") == 0 )
		angle = 15;
	
	angle = WRLongArgWithPrefixFormArgs(argc, argv, "-a", angle);
	delay = WRLongArgWithPrefixFormArgs(argc, argv, "-d", delay);
	
	if( angle < 0 || angle > 80  ) 
	  return CMDLINE_COMMAND_FAIL;
	
	WRWalkingDo( argv[0], angle, delay );
	
	return 0;
}

//debug go
int WRCommandGo(int argc, char *argv[])
{
	if( argc < 1 )
		return CMDLINE_WRONG_ARGS;  
	
	long state = atol( argv[1] );

	WRWalkingTakeState( state );
	
	if( state == 0 )
	{
		return WRCommandLinkGo( argc-1, argv+1 );
	}
	
	return 0;
}



int WRCommandSetAngle(int argc, char *argv[])
{	
	if( argc < 3 )
		return CMDLINE_WRONG_ARGS;
	
	if( argc >= 3 )
	{		
		int id = atoi( argv[1] );
		int angle = atoi( argv[2] );		
		if(  argc >= 4 )
		{
		  	long delay =  atol( argv[3] );
		  	WRServSetAngleWithDelay( id, angle, delay );
		} else
		WRServSetAngle( id, angle );
	}
		
 	return 0;
}

int WRCommandSetPeriod(int argc, char *argv[])
{	
	if( argc != 3 )
		return CMDLINE_WRONG_ARGS;
	
	if( argc == 3 )
	{		
		long id = atol( argv[1] );
		long period = atol( argv[2] );
		
		WRServSetRatio( id, period );
	}
		
 	return 0;
}


//
// Code for the "factor:" commands
//
int	WRCommandFactorSave(int argc, char *argv[])
{
	if( argc != 3 )
		return CMDLINE_WRONG_ARGS;
	
	if( argc >= 3 )
	{		
		long id = atol( argv[1] );
		long angle = atol( argv[2] );		
		WRServSaveFactor(id, angle );
	}
  	return 0;
}
int	WRCommandFactorDel(int argc, char *argv[])
{
	if( argc != 2 )
		return CMDLINE_WRONG_ARGS;
	
	if( argc >= 2 )
	{		
		long id = atol( argv[1] );
		WRServDeleteFactor(id);
	}
  	return 0;
}

int	WRCommandFactorShow(int argc, char *argv[])
{
	if( argc != 2 )
		return CMDLINE_WRONG_ARGS;
	
	if( argc >= 2 )
	{		
		long id = atol( argv[1] );
		char str[10];
		UARTStrSend( ulBase, " factor[" );
		for(int i = 0; i < WR_SERV_FACTOR_SIZE; i++)
		{
			//int sprintf ( char * str, const char * format, ... );
		  	sprintf ( str, "%d", wrServs[id].factor[i] );
			UARTStrSend( ulBase, str );
			UARTStrSend( ulBase, " " );			
		}
		UARTStrSend( ulBase, "]" );		
	}
  	return 0;
}



//
// Code for the "save" command.
//
unsigned long pucBuffer[100];

int WRCommandSave(int argc, char *argv[])
{  		
	if( argc != 1 )
		return CMDLINE_WRONG_ARGS;
	
	WRServSaveSettings();
	return 0;
}

//
// Code for the "load" command.
//
int WRCommandLoad(int argc, char *argv[])
{	
	if( argc != 1 )
		return CMDLINE_WRONG_ARGS;
	
	WRServLoadSettings();	
 	return 0;
}
//
//
//WRMeasure
//
int WRMeasure(int argc, char *argv[])
{
  SendPingToSonar();
  return 0;
}
void WRSendDistance(int Distance)
{
  char DIS[20];
  LongToStr(DIS,19,Distance); 
  UARTStrSend( ulBase, DIS );	
}


//
//	help - show help information about commands
//
int WRCommandHelp(int argc, char *argv[])
{
    tCmdLineEntry *pCmdEntry = &g_sCmdTable[0];
	
	if( argc == 1 )
	{
		UARTStrSend( ulBase, " list of abalible command:" );
		UARTStrSend( ulBase, WR_CONSOLE_ENTER );		
        while(pCmdEntry->pcCmd)
		{
			UARTStrSend( ulBase, pCmdEntry->pcCmd );			
			UARTStrSend( ulBase, " : " );
			
			if( pCmdEntry->pcHelp )
				UARTStrSend( ulBase, pCmdEntry->pcHelp );
			else
				UARTStrSend( ulBase, "no info" );
			
			UARTStrSend( ulBase, WR_CONSOLE_ENTER );			
            pCmdEntry++;
		}
		return 0;
	}
	if( argc == 2 )
	{
        while(pCmdEntry->pcCmd)
		{
            if( strcmp(argv[1], pCmdEntry->pcCmd) == 0)
            {
 				UARTStrSend( ulBase, " : " );	
				if( pCmdEntry->pcHelp )
					UARTStrSend( ulBase, pCmdEntry->pcHelp );
				else
					UARTStrSend( ulBase, "no info" );
				return 0;
            }
            pCmdEntry++;
		}		
		UARTStrSend( ulBase, " no such command" );			
		return 0;
	}
	
	return CMDLINE_WRONG_ARGS;
}
//
// The table of commands supported by WRConsole.
//
tCmdLineEntry g_sCmdTable[] =
{
  	{ "help",		WRCommandHelp, "help [command] - manual about this command" },	
	
  	{ "fsave",		WRCommandFactorSave, "factor: save current position of serv $1 as $2 angle" }, 
  	{ "fdel",		WRCommandFactorDel, "factor: erase all factors of servo $1" }, 	
  	{ "fshow",		WRCommandFactorShow, "factor: show all factros of servo $1" }, 		
	
	{ "save",		WRCommandSave, "save current servs settings: factors etc." },
	{ "load",		WRCommandLoad, "load settings of servos" },
	
	{ "seta",		WRCommandSetAngle, "move serv $1 to position with $2 angle" },	
	{ "setp",		WRCommandSetPeriod, "move serv $1 to postition with $2 period of pwm" },	
	
	{ "on",			WRCommandServsOn, 	"turn on voltage" },
	{ "off",		WRCommandServsOff,  "turn off voltage" },
	
	{ "do",			WRCommandDo, "" },
	{ "go",			WRCommandGo, "" },
	

	{ "stand",		WRCommandLinkDo, "" },
	{ "stand2",		WRCommandLinkDo, "" },	
	{ "sit",		WRCommandLinkDo, "" },	
	{ "sit2",		WRCommandLinkDo, "" },
	{ "sit3",		WRCommandLinkDo, "" },	
	{ "knee",		WRCommandLinkDo, "" },

	
	{ "forward",	WRCommandLinkGo, "" },
	{ "back",		WRCommandLinkGo, "" },
	{ "right",		WRCommandLinkGo, "" },
	{ "left",		WRCommandLinkGo, "" },
	{ "measure",		WRMeasure, "" },	
	{ 0, 0, 0 }
};


//
// The main buffer of the WRConsole
//
unsigned char wrConsoleBuffer[256];
long wrConsoleBufferLen;

//
//	Initialization of WRConsole
//
void WRConsoleInit(void){
	wrConsoleBufferLen = 0;
}


void WRConsoleHandler()
{
}

//
// Handler of console
//
void WRConsoleCharPut(unsigned long _ulBase,  unsigned char currentChar)
{  	
  	ulBase = _ulBase;
	//
	//if current key is the end of command
	//
	if( currentChar == 13 )
	{
	  	//
	  	//try to execute this command
		//
		int result = CmdLineProcess( (char*)wrConsoleBuffer );
		
		//
		//write the result of this command
		//
		switch (result){
			case CMDLINE_BAD_CMD:
		  		UARTStrSend(ulBase, ">BAD CMD		 " );
				break;
			case CMDLINE_TOO_MANY_ARGS:
				UARTStrSend(ulBase, ">TOO MANY ARGS" );
				break;
			case CMDLINE_WRONG_ARGS:
				UARTStrSend(ulBase, ">WRONG ARGS	 " );
				break;	
			case CMDLINE_COMMAND_FAIL:
				UARTStrSend(ulBase, ">FAIL         " );
				break;								
			default:	
			  	UARTStrSend(ulBase, ">OK     		 " );
				break;  
		}
		
		//
		// Erase the console buffer
		//		
		wrConsoleBuffer[0] = 0;
		wrConsoleBufferLen = 0;
		
		//
		//	Send to the console enter 
		//		
		UARTStrSend(ulBase, WR_CONSOLE_ENTER);
		return;
	}
	
	
	//
	// Otherwise, put current char to the buffer
	//
	if( isprint(currentChar) )
	{
		wrConsoleBuffer[ wrConsoleBufferLen++ ] = currentChar;
		wrConsoleBuffer[ wrConsoleBufferLen ] = 0;
		//
		// Print it
		//
		UARTCharPutNonBlocking(ulBase, currentChar );
	} 
	//
	// if key is backspace
	//
	if( currentChar == 0x7f )
	{
		if( wrConsoleBufferLen > 0 )
			wrConsoleBuffer[ --wrConsoleBufferLen ] = 0;
		UARTCharPutNonBlocking(ulBase, currentChar );
	}
	 
}
