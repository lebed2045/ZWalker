#include "wr_uart.h"

#include "inc\lm3s811.h"
#include "inc\hw_types.h"
#include "inc\hw_memmap.h"
#include "inc\hw_ints.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

volatile int Status=0;
/*
0- nothing
1- waiting for sonar answer
2- distance is ready to read
*/
int Distance=0;
volatile int count =0;

void SonarInterrupt(void)
{
  GPIOPinIntClear(GPIO_PORTD_BASE, GPIO_PIN_7);
  count++;

  if (Status==1)
  {
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xFF);
    TimerLoadSet(TIMER2_BASE, TIMER_A,6000000);
    TimerEnable(TIMER2_BASE, TIMER_A);
    Status=2;
  }

 else if (Status==2)
 {
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);
    //Distance=((5995500-TimerValueGet(TIMER2_BASE, TIMER_A))*17)/600000;
    Distance=TimerValueGet(TIMER2_BASE, TIMER_A);
    TimerDisable(TIMER2_BASE, TIMER_A);
    Status=3;
 }

}


int GetDistFromSonar()
{
  if (Status==3)
  {
    Status=0;
    return Distance;
  }
  else return 0;
}

int GetStatus()
{
  return Status;
}
void SendPingToSonar()
{
    Status=1;
    IntDisable(INT_GPIOD);
    
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_7);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0xFF);
    for(int i=0;i<=6;i++);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0);
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_7);
    
    IntEnable(INT_GPIOD);

    
}

void SonarInit()
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
  GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_7);
  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0);
  TimerConfigure(TIMER2_BASE, TIMER_CFG_32_BIT_PER);
  GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_7,GPIO_RISING_EDGE);
  GPIOPinIntEnable(GPIO_PORTD_BASE,GPIO_PIN_7);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_4);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);
  
}


 




