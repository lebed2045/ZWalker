//*****************************************************************************
//
// wr_console.h - Walking Robot's Console
//
//*****************************************************************************

#ifndef __WR_CONSOLE_H__
#define __WR_CONSOLE_H__

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
  
//
// Constant form utils/cmdline.h
//
#define CMDLINE_BAD_CMD         (-1)
#define CMDLINE_TOO_MANY_ARGS   (-2)
//
// WRotbot constants
//
#define CMDLINE_WRONG_ARGS		(-3)
#define CMDLINE_COMMAND_FAIL	(-4)
#define CMDLINE_COMMAND_OK		(0)


extern void WRConsoleInit(void);
void WRConsoleCharPut(unsigned long ulBase,  unsigned char ucData);
void WRConsoleHandler();
void WRSendDistance(int);
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WR_CONSOLE_H__
