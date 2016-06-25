#include "wr_uart.h"
#include "wr_console.h"

#include "inc/lm3s811.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"


//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void UART0IntHandler(void)
{
    unsigned long ulStatus;
    long tempChar; //current char from UART

    //
    // Get the interrrupt status.
    //
    ulStatus = UARTIntStatus(UART0_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    UARTIntClear(UART0_BASE, ulStatus);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(UARTCharsAvail(UART0_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        tempChar = UARTCharGetNonBlocking(UART0_BASE);
        WRConsoleCharPut(UART0_BASE, tempChar);
    }
}

void UART1IntHandler(void)
{
    unsigned long ulStatus;
    long tempChar; //current char from UART

    //
    // Get the interrrupt status.
    //
    ulStatus = UARTIntStatus(UART1_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    UARTIntClear(UART1_BASE, ulStatus);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(UARTCharsAvail(UART1_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        tempChar = UARTCharGetNonBlocking(UART1_BASE);
        WRConsoleCharPut(UART1_BASE, tempChar);
    }
}


//*****************************************************************************
//
// Send the string to the UART.
//
//*****************************************************************************
long timeOfOneByteSending(unsigned long ulBase)
{
	// CPU rate is SysCtlClockGet (6 Mhz)
  	// in SysCtlDelay method one loop takes 3 cycle
	// configuration of UART as 8-N-1
  	// so one byte contain 9 bit and each sending each bit take 6M / baud rate
  	// (1000 / (baud rate of connection)) * 9 for sending of one byte
    // (cpu clock / 1000) cycles of cpu in 1ms
    // (9000 / baud) * (cpu clock / 1000) * 3 - loop of SysTlcDelay
    // But call a lot of function also take much time 
  	// because I can't estimate that time so ignore it =(
  	long baud = 0;
	if( ulBase == UART0_BASE )
		baud = WR_UART0_BAUD;
	if( ulBase == UART1_BASE )
		baud = WR_UART1_BAUD;
  	return  (3*9*SysCtlClockGet()) / baud;
	
}
void UARTStrSend(unsigned long ulBase, const char *pucBuffer)
{
    //
    // Loop while there are more characters to send.
    //
	long delay = timeOfOneByteSending(ulBase);
    while(*pucBuffer)
    {
        //
        // Write the next character to the UART.
        //
        UARTCharPutNonBlocking(ulBase, (unsigned char)*pucBuffer++);
		//
		// Delay
		//
		SysCtlDelay(delay); 
    }
}

char* WR_HELLO_STR = "I'm Walking Robot! What I have to do? : ";

void WRUART0Init(void)
{
    //
    // Enable the peripherals used by this example.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable processor interrupts.
    //
    IntMasterEnable(); 

    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), WR_UART0_BAUD,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
	IntPrioritySet( INT_UART0, 7 );
    IntEnable(INT_UART0);

    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    //
    // Prompt for text to be entered.
    //
    UARTStrSend(UART0_BASE, WR_HELLO_STR);
}

void WRUART1Init(void)
{
    //
    // Enable the peripherals used by this example.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    //
    // Enable processor interrupts.
    //
    IntMasterEnable(); 

    //
    // Set GPIO PD2 and PD3 as UART pins.
    //
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3);

    //
    // Configure the UART for 9,600 8-N-1 operation.
    //
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), WR_UART1_BAUD,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
	IntPrioritySet( INT_UART1, 7 );
    IntEnable(INT_UART1);

    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

    //
    // Prompt for text to be entered.
    //
    UARTStrSend(UART1_BASE, "WR_HELLO_STR");
}