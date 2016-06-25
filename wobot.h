//*****************************************************************************
//
// wobot.h - Walking Robot's main settings and includes
//
//*****************************************************************************

#ifndef __WOBOT_H__
#define __WOBOT_H__

// by Hz
#define WR_SYS_TIMER_FREQUENCY 500
#define WR_PWMTIMER_RATE 100

// baud rate of bluetooth
#define WR_UART1_BAUD 9600
// baud rate of wire
#define WR_UART0_BAUD 115200

#include "wr_console.h"
#include "wr_serv.h"
#include "wr_pwmtimer.h"
#include "wr_uart.h"
#include "wr_flash.h"
#include "wr_leg.h"
#include "wr_walking.h"
#include "wr_sonar.h"
#include "str.h"

#include "inc/lm3s811.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "driverlib/flash.h"
#include "driverlib/uart.h"
#include "driverlib/systick.h"

#include "drivers/display96x16x1.h"

#include "utils/cmdline.h"


#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#endif // __WOBOT_H__
