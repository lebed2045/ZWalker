//*****************************************************************************
//
// wr_console.h - Walking Robot's Console
//
//*****************************************************************************

#ifndef __WR_UART_H__
#define __WR_UART_H__

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

void UARTStrSend(unsigned long ulBase, const char *pucBuffer);
void WRUART0Init();
void WRUART1Init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif 
