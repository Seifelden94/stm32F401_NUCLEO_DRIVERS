#include "TIMERS.h"
#include"CLOCK.h"
#include "DIO.h"
#include "MEMORY.h"
#include "INTERRUPT.h"



/* you do not need all of them becuse some are already intalised to be used as PWm
 * pwtime2 cCR1
 *
 * ARPE, CEN: CMS :Center-aligned mode selection: and  DIR: Direction in TIMx_CR1
 *Bit 0 UIE: Update interrupt enable and Bit 1 CC1IE: Capture/Compare 1 interrupt enable  TIMx DMA/Interrupt enable register (TIMx_DIER)
 * UIF: Update interrupt flag and CC1I(Capture/compare 1 interrupt flag) in TIMx status register (TIMx_SR)
 *Bit 0 UG: Update generation in   TIMx event generation register (TIMx_EGR)
 *Bit
 * Bits 1:0 CC1S, OC1PE: Output compare 1 preload enable : Capture/Compare 1 selection  Bits 6:4 OC1M: in TIMx_CCMR1
 *
 * Bit 0 CC1E: Capture/Compare 1 output enable., Bit 1 CC1P: Capture/Compare 1 output Polarity. in TIMx_CCER
 *
 * Bit 3 CC1NP: Capture/Compare 1 output Polarity.
CC1 channel configured as output:
CC1NP must be kept cleared in this case.
CC1 channel configured as input:
This bit is used in conjunction with CC1P to define TI1FP1/TI2FP1 polarity. refer to CC1P
description.

MOE,OSSR,OSSI in  TIMx_BDTR

TIMx_CNT TIMx_PSC, TIMx_ARR
 */


////////////////////// do not forget to make the mode of the pin to be used as an alternative function 10 in GPIO_MODER: Alternate function mode
// ALSO  GPIO alternate function low register (GPIOx_AFRL)   ,GPIO alternate function high register (GPIOx_AFRH)
void pwm_time2_edge_intialise(void)
{


	RCC_APB1ENR  = (((RCC_APB1ENR  ) &(~(0b1<<TIM2EN_OFFSET ))) |(TIM2EN_ON    <<TIM2EN_OFFSET )) ;  //enable the clock for time2


	RCC_APB2ENR    = (((RCC_APB2ENR    ) &(~(0b1<<TIM1EN_OFFSET ))) |(TIM1EN    <<TIM1EN_OFFSET )) ;  //enable the clock for time2




   ////////////////////////// write the bit for count

	 TIM2_PSC= PSC_VALUE;                                                     //// Set the desired prescaler


	 TIM2_CR1  = (((TIM2_CR1 ) &(~(0b11<<CMS_OFFSET))) |(CMS <<CMS_OFFSET)) ;/// choose edge aligned or center aligned

	 TIM2_CR1  = (((TIM2_CR1 ) &(~(0b1<<DIR_OFFSET))) |(DIR <<DIR_OFFSET));      /// choose if the counter will count up counting or down counting if we use edge aligned

///	 TIM2_CR1  = (((TIM2_CR1 ) &(~(0b1<<ARPE_OFFSET))) |(ARPE <<ARPE_OFFSET)); //  not nessesery, Auto reload preload enable


	 TIM2_CCMR1  = (((TIM2_CCMR1 ) &(~(0b111<<OC1M_OFFSET ))) |(OC1M  <<OC1M_OFFSET ));  /// choose the mode for the edge aligned

	 TIM2_CCMR1  = (((TIM2_CCMR1 ) &(~(0b111<<OC1CE_OFFSET ))) |(OC1CE  <<OC1CE_OFFSET ));  ///



	 // TIM2_CCMR1  = (((TIM2_CCMR1 ) &(~(0b1<<OC1PE_OFFSET ))) |(OC1PE  <<OC1PE_OFFSET ));    /////   not nessesery, Output compare 1 preload enable

	 TIM2_CCER  = (((TIM2_CCER) &(~(0b1<<CC1E_OFFSET ))) |(CC1E<<CC1E_OFFSET ));  ////////Capture/Compare 1 output enable.
		TIM2_CCER  = (((TIM2_CCER ) &(~(0b1<<CC1P_OFFSET ))) |(CC1P <<CC1P_OFFSET ));    /////// Capture/Compare 1 output Polarity


		TIM1_BDTR  = (((TIM1_BDTR ) &(~(0b1<<MOE_OFFSET ))) |(MOE <<MOE_OFFSET  ));  ////Main output enable

		TIM2_BDTR  = (((TIM2_BDTR ) &(~(0b1<<MOE_OFFSET ))) |(MOE <<MOE_OFFSET  ));  ////Main output enable

        *GPIOa.AFRL=(((*GPIOa.AFRL ) &(~(0b1111<<0 ))) |(0b0001 <<0  )); /// time chanel 1 is PA0 and AF01


	 /*
	  * /*
Bit 0 UG: Update generation
This bit can be set by software, it is automatically cleared by hardware.
0: No action
1: Re-initialize the counter and generates an update of the registers. Note that the prescaler
counter is cleared too (anyway the prescaler ratio is not affected). The counter is cleared if
the center-aligned mode is selected or if DIR=0 (upcounting), else it takes the auto-reload
value (TIMx_ARR) if DIR=1 (downcounting).*/

	                                                                   //than UIF will be set and the registers will be updated
	TIM2_CR1 = (((TIM2_CR1 ) &(~(0b1<<CEN_OFFSET))) |(CEN_ON <<CEN_OFFSET)) ;  /// put one in CEN to enable the count in the time counter

	TIM2_EGR=(((TIM2_EGR ) &(~(0b1<<UG_OFFSET ))) |( 1<<UG_OFFSET )) ; //  without this line the register will not be updated until an overflow or underflow happen

   while(!(TIM2_SR&(1<<UIF_OFFSET)));     //// ! is general true or false not a bit operation this is very important to make sure that registers got the new values.
                                                  // it give me an error and it took me while to figure it out
    TIM2_SR=((TIM2_SR) &(~(0b1<<UIF_OFFSET)));  //clear the UIF flag

}


void pwm_frequency_deuty_edge(int dutey, int frequency)
{
   int ARR;

	TIM2_CNT=0;


	 ARR= (TIME2_F_HZ/(frequency))-1  ; //Period =(1+ARR)*CLOCK Period
	 TIM2_ARR =ARR;
	   //// if upcounting
	 if(OC1M==PWM_MODE1) {
	TIM2_CCR1 = (dutey*0.01)*(ARR+1);     /// 0.01 indicat that it is float
	 } else if (OC1M==PWM_MODE2)
	 {
		 TIM2_CCR1 = (1- (100/dutey))*(ARR+1);  //Dutey cycle= 1-CCR/(ARR+1)   // the prcentage of the signal that is high from all the period

	 }

	//TIM2_EGR=(((TIM2_EGR ) &(~(0b1<<UG_OFFSET ))) |( 1<<UG_OFFSET )) ; //  without this line the register will not be updated until an overflow or underflow happen

	 ///  while(!(TIM2_SR&(1<<UIF_OFFSET)));     //// ! is general true or false not a bit operation this is very important to make sure that registers got the new values.

}



void pwm_centeraligned_intialise(void)
{





}


void pwm_interrupt_enable(void)
{

	TIM2_DIER = (((TIM2_DIER ) &(~(0b1<<CC1IE_OFFSET ))) |(CC1IE  <<CC1IE_OFFSET )) ;

	 TIM2_DIER  = (((TIM2_DIER  ) &(~(0b1<<UIE_OFFSET))) |(UIE_ON <<UIE_OFFSET)) ; ///Update interrupt enable


		 TIM2_EGR=(((TIM2_EGR ) &(~(0b1<<UG_OFFSET ))) |( 1<<UG_OFFSET )) ; //  without this line the register will not be updated until an overflow or underflow happen


		  while(!(TIM2_SR&(1<<UIF_OFFSET)));     ////! is general true or fales not a bit operation this is very important to make sure that registers got the new values.
		                                                   // it give me an error and it took me while to figure it out


		    TIM2_SR=((TIM2_SR) &(~(0b1<<UIF_OFFSET)));  //clear the UIF flag

		    NVIC_EnableIRQ(TIM2_IRQn);    /// to enable the time2 interrupt.
		 	       	   NVIC_SetPriority(TIM2_IRQn,TIME_INTERRUPT_priorety); /// priorety is from 0 to 15 the lower the number the higher the priority


}







/*
 * ARR is auto reload register,  RCR
 *
 *
 *
 *  2-if down counting >> count from ARR value until 0 then counter underflow event; then counter get the ARR value
 *
 *
 *3-center aligned > the counter count until ARR,then counter overflow event, then start count down to Zero,then counter underflow event
 * period =2 *ARR*clockPeriod
 */
// every timer have one ARR and upto CCR. so all the OCxREF will have same period and cam have diffrent dutey cycle

/* CCR capture and compare register
 *1-if upcounting >> count until ARR value then counter overflow event; then counter get rest
 *
 *
 *
 * PWM MODE 1(LOW-True)
 * timer output can be
 * 1-High if counter <CCR
 * 2- Low if counter >=CCR
* Period =(1+ARR)*CLOCK Period
 * Dutey cycle= CCR/(ARR+1)
 *all the rising edge is aligned>so it is left aligned
 *
 * PWM mode2(HIGH TRUE)
 * timer output can be
 * 1-LOW if counter<CCR
 * 2- HIGH if counter >= CCR
 *
 ** Period =(1+ARR)*CLOCK Period
 * Dutey cycle= 1-CCR/(ARR+1)   // the prcentage of the signal that is high from all the period
 *
 * all falling edge accur at the same time -> Righ edge aligned
 */

/* center aligned in mode 2(HIGH TRUE)
 *period =2 *ARR*clockPeriod
 *period duty cycle= 1-(CCR/ARR)
 *
 */

 /* you can change the polarity of the output by writing to CCxP bit in TIMX_CCER register
   so if the output was going to be high it will be inverted to be low
  the output to the pin OCx=OCxRef xor polarity

   */



/*ARR can be updated syn is ARPE=1 it will by trigered by update EVENT(UEV)
 * UEV is disabled if UDIS in TIMX_CR1 is 1
 *
 * ARPE=0 asyncrounis update happend
 */

/*  UDIS=0
 * RCR-> repetition counter iRegister
 *if RCR =3 update event occur every four overflow or underflow event
 *if RCR=1 update event occur every two overflow or underflow event
 *
 *
 */

/*
 * PWM mode
Pulse Width Modulation mode allows generating a signal with a frequency determined by
the value of the TIMx_ARR register and a duty cycle determined by the value of the
TIMx_CCRx register.
The PWM mode can be selected independently on each channel (one PWM per OCx
output) by writing ‘110’ (PWM mode 1) or ‘111’ (PWM mode 2) in the OCxM bits in the
TIMx_CCMRx register. The corresponding preload register must be enabled by setting the
OCxPE bit in the TIMx_CCMRx register, and eventually the auto-reload preload register (in
upcounting or center-aligned modes) by setting the ARPE bit in the TIMx_CR1 register.
As the preload registers are transferred to the shadow registers only when an update event
occurs, before starting the counter, the user must initialize all the registers by setting the UG
bit in the TIMx_EGR register.
OCx polarity is software programmable using the CCxP bit in the TIMx_CCER register. It
can be programmed as active high or active low. OCx output is enabled by a combination of
the CCxE, CCxNE, MOE, OSSI and OSSR bits (TIMx_CCER and TIMx_BDTR registers).
Refer to the TIMx_CCER register description for more details.
In PWM mode (1 or 2), TIMx_CNT and TIMx_CCRx are always compared to determine
whether TIMx_CCRx ≤TIMx_CNT or TIMx_CNT ≤TIMx_CCRx (depending on the direction
of the counter).
The timer is able to generate PWM in edge-aligned mode or center-aligned mode
depending on the CMS bits in the TIMx_CR1 register.
 */
