#include "wr_pwmtimer.h"

#include "inc/lm3s811.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"


#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/timer.h"


unsigned long ulPeriod;

//
// In thss case ratio mean period of signel in tacts
//
void WRPWMRatioSet(long pwm_out, long pulse_duration)
{	
  	//http://en.wikipedia.org/wiki/Duty_cycle
	//Duty cycle == signal_period / period 
  	//signel_period usually from 3000 to 15000
	//cause ulPeriod = SysCtlClockGet() / WR_PWMTIMER_RATE;
	//6M / 100hz = 60000 (ticks/10ms)
    //so length of usual signal is (0.3, 2.5)ms
    
	unsigned long duration = pulse_duration;
	long PWM_OUT = PWM_OUT_0;
	
	switch(pwm_out){
		case 0: PWM_OUT = PWM_OUT_0; break;
		case 1: PWM_OUT = PWM_OUT_1; break;
		case 2: PWM_OUT = PWM_OUT_2; break;		
		case 3: PWM_OUT = PWM_OUT_3; break;
		case 4: PWM_OUT = PWM_OUT_4; break;		
		case 5: PWM_OUT = PWM_OUT_5; break;
	}
	
    PWMPulseWidthSet(PWM_BASE, PWM_OUT, duration );	
}

void WRTimerRatioSet(long timer_out, long pulse_duration)
{
	unsigned long duration = pulse_duration;
	
  	if( timer_out == 6 )
		TimerMatchSet(TIMER0_BASE, TIMER_A, duration );  
	if( timer_out == 7 )
		TimerMatchSet(TIMER0_BASE, TIMER_B, duration );  	
        if( timer_out == 8 )
		TimerMatchSet(TIMER1_BASE, TIMER_A, duration );  	

}



void WRPWMInit(void)
{
    //
    // Set the clocking to run directly from the crystal.
    //
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    //
    // Enable the peripherals used by this example.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    //
    // Set GPIO D0 and D1 as PWM pins.  They are used to output the PWM0 and
    // PWM1 signals.
    //
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1);	

    //
    // Compute the PWM period based on the system clock.
    //
    ulPeriod = SysCtlClockGet() / WR_PWMTIMER_RATE;

    //
    // Set the PWM period to ulRate Hz.
    //
    PWMGenConfigure(PWM_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM_BASE, PWM_GEN_0, ulPeriod);
	PWMGenConfigure(PWM_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM_BASE, PWM_GEN_1, ulPeriod);
	PWMGenConfigure(PWM_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM_BASE, PWM_GEN_2, ulPeriod);

	
    //
    // Set PWM0 to a duty cycle of 25% and PWM1 to a duty cycle of 75%.
    //
    //PWMPulseWidthSet(PWM_BASE, PWM_OUT_0, ulPeriod / 4);
    //PWMPulseWidthSet(PWM_BASE, PWM_OUT_1, ulPeriod * 3 / 4);

    //
    // Enable the PWM0 and PWM1 output signals.
    //
    PWMOutputState(PWM_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);
    PWMOutputState(PWM_BASE, PWM_OUT_2_BIT | PWM_OUT_3_BIT, true);
    PWMOutputState(PWM_BASE, PWM_OUT_4_BIT | PWM_OUT_5_BIT, true);	

    //
    // Enable the PWM generator.
    //
    PWMGenEnable(PWM_BASE, PWM_GEN_0);
    PWMGenEnable(PWM_BASE, PWM_GEN_1);
    PWMGenEnable(PWM_BASE, PWM_GEN_2);	
}

void WRTimerInit(void)
{	
    //
    // Enable the peripherals used by this example.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	
	GPIOPinTypeTimer(GPIO_PORTD_BASE, GPIO_PIN_4 ); //PD4
	GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_5 );	//PC5

    //
    // Enable processor interrupts.
    //
    //IntMasterEnable();

    //
    // Configure the two 16-bit periodic timers.
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_16_BIT_PAIR 
				   				| TIMER_CFG_A_PWM | TIMER_CFG_B_PWM  );
  //  TimerConfigure(TIMER1_BASE, TIMER_CFG_16_BIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM  );   
	TimerControlLevel( TIMER0_BASE, TIMER_BOTH, true );
        //TimerControlLevel( TIMER1_BASE, TIMER_BOTH, true );
	
    //
    // Compute the PWM period based on the system clock.
    //	
    ulPeriod = SysCtlClockGet() / WR_PWMTIMER_RATE;	
	
    TimerLoadSet(TIMER0_BASE, TIMER_BOTH, ulPeriod );
   // TimerLoadSet(TIMER1_BASE, TIMER_BOTH, ulPeriod );
    //
    // Setup the interrupts for the timer timeouts.
    //
    //IntEnable(INT_TIMER0A);
    //IntEnable(INT_TIMER1A);
    //TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Enable the timers.
    //
    TimerEnable( TIMER0_BASE, TIMER_BOTH );	
    //TimerEnable( TIMER1_BASE, TIMER_BOTH );	
}

void WRPWMTimerEnable()
{
	TimerEnable( TIMER0_BASE, TIMER_BOTH );		
        TimerEnable( TIMER1_BASE, TIMER_BOTH );
//    PWMGenEnable(PWM_BASE, PWM_GEN_0);
//    PWMGenEnable(PWM_BASE, PWM_GEN_1);
//    PWMGenEnable(PWM_BASE, PWM_GEN_2);	
}

void WRPWMTimerDisable()
{
  	TimerDisable( TIMER0_BASE, TIMER_BOTH );	
	TimerDisable( TIMER1_BASE, TIMER_BOTH );
//    PWMGenDisable(PWM_BASE, PWM_GEN_0);
//    PWMGenDisable(PWM_BASE, PWM_GEN_1);
//    PWMGenDisable(PWM_BASE, PWM_GEN_2);	

}