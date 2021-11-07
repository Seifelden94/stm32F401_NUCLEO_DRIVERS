#include "TIMERS.h"
#include"CLOCK.h"
#include "INTERRUPT.h"


////time2 interrupt


void  time2_interrupt_intialise(void) //////make sure not to use the same timer2 interrupt and  delay2 at the same time
                                        ///becuase in the delay function I put zero in the counter register, unlese you changed

{   RCC_APB1ENR  = (((RCC_APB1ENR  ) &(~(0b1<<TIM2EN_OFFSET ))) |(TIM2EN_ON    <<TIM2EN_OFFSET )) ;  //enable the clock for time2

TIM2_CR1 = (((TIM2_CR1 ) &(~(0b1<<CEN_OFFSET))) |(CEN_ON <<CEN_OFFSET)) ;  /// put one in CEN to enable the count in the time counter
    ////////////////////////// write the bit for count

	 TIM2_PSC= PSC_VALUE;                             //// Set the desired prescaler in my case I can choose it to give me
	                                            ////1 microsecond in every count if the input clock is 84 M
	                                         ///  I will choose it to be 83  fcount= 84MHz/(83+1) = 1 Mega HZ, every count will= 1 microsecond


	 TIM2_DIER  = (((TIM2_DIER  ) &(~(0b1<<UIE_OFFSET))) |(UIE_ON <<UIE_OFFSET)) ; ///Update interrupt enable


	 TIM2_EGR=(((TIM2_EGR ) &(~(0b1<<UG_OFFSET ))) |( 1<<UG_OFFSET )) ; //  without this line the register will not be updated until an overflow or underflow happen


	  while(!(TIM2_SR&(1<<UIF_OFFSET)));     ////! is general true or fales not a bit operation this is very important to make sure that registers got the new values.
	                                                   // it give me an error and it took me while to figure it out


	    TIM2_SR=((TIM2_SR) &(~(0b1<<UIF_OFFSET)));  //clear the UIF flag

	    NVIC_EnableIRQ(TIM2_IRQn);    /// to enable the time2 interrupt.
	 	       	   NVIC_SetPriority(TIM2_IRQn,TIME_INTERRUPT_priorety); /// priorety is from 0 to 15 the lower the number the higher the priority

}


void time2_interrupt_msecond(int msecond)
{
	TIM2_CNT=0;                 ///  Put zero in the count register to start count from zero

	TIM2_ARR= 1000*msecond;          /// set the auto reload register. becuse I am using up count which is the intial state.
	                           ///when the count in tim2_cnt reach  TIM2_ARR an overflow will happen and interrupt will occur.
                               //// I multiply by 1000 becuse every count is 1 microsecond 1msec=1000microsec

}









void TIM2_IRQHandler (void) ////  I got the function TIM2_IRQHandler  name from the startup file// coud use saame function if I want a compare and capture interrupt to occur

{
	 GPIO_toggle_atomic( &GPIOa, PIN5  );        ///

  TIM2_SR=((TIM2_SR) &(~(0b1<<UIF_OFFSET)));  //clear the UIF( updated interrupt flag)
	   TIM2_SR=((TIM2_SR) &(~(0b1<<CC1IF_OFFSET ))); ////flag of compare and capture clear it if I am using pwm and enabled interrupt in chanel one, I need to clear it
}
