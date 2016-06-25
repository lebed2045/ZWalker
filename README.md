# ZWalker
---------
Program for walking robot base of Luminary Micro LM3S811 Evaluation Kit (ARM Cortex M3), servos towerpro mg90. https://youtu.be/565xqV6W3Kk

It was my university project supervised by Zapunidi Sergey from Laboratory of photophysics of organic materials of Lomonosov State University.

Unfortunately, I was stupid enough to do not record video when I finished the robot, so the only evidence I have the old video while I first launched it. So it was kind of first, tentative steps of Zwalker and it walked far better in all future test, especially after I've changed plastic servos to the metal one. Also it controled by bluetooth. 

The robots controles via console, using following commands:
  	{ "help",		WRCommandHelp, "help [command] - manual about this command" },	

  	{ "on",			WRCommandServsOn, 	"turn on voltage" },
	{ "off",		WRCommandServsOff,  "turn off voltage" },
	
  	{ "fsave",		WRCommandFactorSave, "factor: save current position of serv $1 as $2 angle" }, 
  	{ "fdel",		WRCommandFactorDel, "factor: erase all factors of servo $1" }, 	
  	{ "fshow",		WRCommandFactorShow, "factor: show all factros of servo $1" }, 		
	
	{ "save",		WRCommandSave, "save current servs settings: factors etc." },
	{ "load",		WRCommandLoad, "load settings of servos" },
	
	{ "seta",		WRCommandSetAngle, "move serv $1 to position with $2 angle" },	
	{ "setp",		WRCommandSetPeriod, "move serv $1 to postition with $2 period of pwm" },	

	{ "measure",	WRMeasure, "return data from sonar" },	

and different complex commands, similar to a dogs tricks:

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
	