
#include "INTERRUPT.h"
#include "DIO.h"
#include "stm32f4xx.h"
////
/*
The input parameter IRQn is the IRQ number, see Table 17: Properties of the different
exception types on page 38. For more information about these functions see the CMSIS
documentation.



Table 48. CMSIS functions for NVIC control
CMSIS interrupt control function Description
void NVIC_SetPriorityGrouping(uint32_t priority_grouping) Set the priority grouping

void NVIC_EnableIRQ(IRQn_t IRQn) Enable IRQn
void NVIC_DisableIRQ(IRQn_t IRQn) Disable IRQn

uint32_t NVIC_GetPendingIRQ (IRQn_t IRQn)   Return true (IRQ-Number) if IRQn is  pending

void NVIC_SetPendingIRQ (IRQn_t IRQn) Set IRQn pending

void NVIC_ClearPendingIRQ (IRQn_t IRQn) Clear IRQn pending status

uint32_t NVIC_GetActive (IRQn_t IRQn) Return the IRQ number of the active interrupt

void NVIC_SetPriority (IRQn_t IRQn, uint32_t priority) Set priority for IRQn

uint32_t NVIC_GetPriority (IRQn_t IRQn) Read priority of IRQn

void NVIC_SystemReset (void) Reset the system
 */
/*
typedef void func(void);
func* f = (func*)0xdeadbeef;
int i = f();*/

void external_interrupt_init(void)   /// I tried 6 pin all works fin except pin 2 and 3

{
	 //// enable the clock
	RCC_APB2ENR  = ((RCC_APB2ENR   ) &(~(0b1<<SYSCFGEN_BIT_OFFSET))) |(SYSCFGEN_CLOCK_ENABLE <<SYSCFGEN_BIT_OFFSET ) ;  /// I wanted to make sure that I cleared the first four bit befor I write 0010

/*  decide what pin I will be using for external interrupt and if i will use it as rising faling or both,
 * and set the priority from 0 to 15 the lower the number the higher the priority.
example if I want to use PA0  I can choose RISING_EDGE , FALLING_EDGE, or BOTH_RISING_FALLING_EDGE, and priority of 2
 I will type

 choose_interrupt_pins(PA,0,RISING_EDGE,2);  or if I want PB1  to be at falling edge and priority 1 ->choose_interrupt_pins(PB,1,FALLING_EDGE,1)

 the avaliable port is PA,PB,PC,PD,PE,PH. from pin 0 to 15
 !!!! YOU CAN NOT CHOOSE SAME NUMBER FOR DIFFRENT PORTS >> EXAMPLE   PA0,PB0. THE LAST ONE YOU INTIALISED WILL BE USED the first one will not be used as interrupt


*/

	choose_interrupt_pins(PA,0,FALLING_EDGE,1);
	choose_interrupt_pins(PA,3,FALLING_EDGE,2); /// issue
	choose_interrupt_pins(PA,2,FALLING_EDGE,1);  ////there is an issue to be fixed
	choose_interrupt_pins(PA,6,FALLING_EDGE,1);
	choose_interrupt_pins(PA,8,FALLING_EDGE,2);

	//// from the stertup file   EXTI1_IRQHandler
	//EXTI1_IRQHandler has IRQ number of 7 got it from vector table

           ///// first argument is the IRQnumber the second is the priorety from 0 to 15 the lower the number the higher the priority




	//NVIC_ISER0 |=  1<<7;


}


void EXTI0_IRQHandler(void) ///// choose the interrupt function just like the names in the startup file. this for EXITI1

{
	 if(EXTI_PR&(1<<0))
	 {
		 interrupt_handler();

	  EXTI_PR =1<<0  ;  /// I need to erase the pending bit, I do that by writing a one to the crossbonding bit



	  /*
 should not use   or EXTI_PR |=1<<1 because it is a write only register,
 reading yeilds “1” for all bits so you are reading the register (all ones) then ORing a 1 to bit 1 and writing it back.
	   */
	 }
	 }



void EXTI2_IRQHandler(void) ///// choose the interrupt function just like the names in the startup file. this for EXITI1

{
	 if(EXTI_PR&(1<<2))
	 {
		 interrupt_handler();

	  EXTI_PR =1<<2  ;  /// I need to erase the pending bit, I do that by writing a one to the crossbonding bit



	  /*
 should not use   or EXTI_PR |=1<<1 because it is a write only register,
 reading yeilds “1” for all bits so you are reading the register (all ones) then ORing a 1 to bit 1 and writing it back.
	   */
	 }
	 }



void EXTI3_IRQHandler (void) ///// choose the interrupt function just like the names in the startup file.this for EXITI3

{
	 if(EXTI_PR&(1<<3))     ///EXIT3
	 {
		 interrupt_handler();

	  EXTI_PR =1<<3  ;  /// I need to erase the pending bit, I do that by writing a one to the crossbonding bit



	  /*
 should not use   or EXTI_PR |=1<<3 because it is a write only register,
 reading yeilds “1” for all bits so you are reading the register (all ones) then ORing a 1 to bit 1 and writing it back.
	   */
	 }
	 }


void EXTI9_5_IRQHandler  (void) ///// choose the interrupt function just like the names in the startup file.this for EXITI3

{
	 if(EXTI_PR&(1<<6))     ///EXIT3
	 {
		 interrupt_handler();

	  EXTI_PR =1<<6  ;  /// I need to erase the pending bit, I do that by writing a one to the crossbonding bit



	  /*
 should not use   or EXTI_PR |=1<<3 because it is a write only register,
 reading yeilds “1” for all bits so you are reading the register (all ones) then ORing a 1 to bit 1 and writing it back.
	   */
	 }
	 if(EXTI_PR&(1<<8))     ///EXIT3
		 {
			 interrupt_handler();

		  EXTI_PR =1<<8  ;  /// I need to erase the pending bit, I do that by writing a one to the crossbonding bit



		  /*
	 should not use   or EXTI_PR |=1<<3 because it is a write only register,
	 reading yeilds “1” for all bits so you are reading the register (all ones) then ORing a 1 to bit 1 and writing it back.
		   */
		 }
	 }



void interrupt_handler(void)
{
	GPIO_toggle_atomic( &GPIOa,PIN5); /// using GPIOA which is  #define GPIOA       &GPIOa
	                               // took me t an interrupt error becuse from some reasons the address of BSRR did not got the value I assigned
	                                  //probaly becuse there is other #define GPIOA that was already writen in another file



}




void choose_interrupt_pins(int port_name, int pin_number, int rising_falling_or_both,int priority)   //// I could add , int priority   so in this function Also, I choose the priorety.


{

	EXTI_IMR |=(0b1<<pin_number);  // put 1 the to disable mask for this specific interrupt, so it can work



/*	if(0<=pin_number<=3)
	{

		SYSCFG_EXTICR1 = ((SYSCFG_EXTICR1  ) &(~(0b1111<<(pin_number*4)))) |(port_name <<(pin_number*4) );       ///
	}else if(4<=pin_number<=7)
	{

		SYSCFG_EXTICR2 = ((SYSCFG_EXTICR2  ) &(~(0b1111<<((pin_number-4)*4)))) |(port_name <<((pin_number-4)*4) );         /////// ex if pin number 7  ->  (7-4)4 =12   which mean the four bits start at offset 12

	}else if(8<=pin_number<=11)
	{

		SYSCFG_EXTICR3 = ((SYSCFG_EXTICR3  ) &(~(0b1111<<((pin_number-8)*4)))) |(port_name <<((pin_number-8)*4) );
	}else if(12<=pin_number<=15)
	{

		SYSCFG_EXTICR4 = ((SYSCFG_EXTICR4  ) &(~(0b1111<<((pin_number-12)*4)))) |(port_name <<((pin_number-12)*4) );
	}*/

	 switch(pin_number) {


   case 0 :
	         SYSCFG_EXTICR1 = ((SYSCFG_EXTICR1  ) &(~(0b1111<<(pin_number*4)))) |(port_name <<(pin_number*4) );
	         NVIC_EnableIRQ(EXTI0_IRQn);
	         NVIC_SetPriority(EXTI0_IRQn,priority);
	     break;
   case 1 :
	   	   	 SYSCFG_EXTICR1 = ((SYSCFG_EXTICR1  ) &(~(0b1111<<(pin_number*4)))) |(port_name <<(pin_number*4) );
	   	   	 NVIC_EnableIRQ(EXTI1_IRQn);
	   	   	 NVIC_SetPriority(EXTI1_IRQn,priority);
	     break;
   case 2 :
	   	     SYSCFG_EXTICR1 = ((SYSCFG_EXTICR1  ) &(~(0b1111<<(pin_number*4)))) |(port_name <<(pin_number*4) );
	   	     NVIC_EnableIRQ(EXTI2_IRQn);
	   	     NVIC_SetPriority(EXTI2_IRQn,priority);
	     break;
   case 3 :
	   	   	 SYSCFG_EXTICR1 = ((SYSCFG_EXTICR1  ) &(~(0b1111<<(pin_number*4)))) |(port_name <<(pin_number*4) );
             NVIC_EnableIRQ(EXTI3_IRQn);
             NVIC_SetPriority(EXTI3_IRQn,priority);

         break;

   case 4 :
	          SYSCFG_EXTICR2 = ((SYSCFG_EXTICR2  ) &(~(0b1111<<((pin_number-4)*4)))) |(port_name <<((pin_number-4)*4) );
	          NVIC_EnableIRQ(EXTI4_IRQn);
	          NVIC_SetPriority(EXTI4_IRQn,priority);

         break;



                  //// EXTI9_5_IRQn    feom EXIT5 to EXIT9
   case 5 :
	   	   	  SYSCFG_EXTICR2 = ((SYSCFG_EXTICR2  ) &(~(0b1111<<((pin_number-4)*4)))) |(port_name <<((pin_number-4)*4) );
	          NVIC_EnableIRQ(EXTI9_5_IRQn);
	          NVIC_SetPriority(EXTI9_5_IRQn,priority);

         break;
   case 6 :
	          SYSCFG_EXTICR2 = ((SYSCFG_EXTICR2  ) &(~(0b1111<<((pin_number-4)*4)))) |(port_name <<((pin_number-4)*4) );
	          NVIC_EnableIRQ(EXTI9_5_IRQn);
	          NVIC_SetPriority(EXTI9_5_IRQn,priority);

	     break;
   case 7 :
              SYSCFG_EXTICR2 = ((SYSCFG_EXTICR2  ) &(~(0b1111<<((pin_number-4)*4)))) |(port_name <<((pin_number-4)*4) );         /////// ex if pin number 7  ->  (7-4)4 =12   which mean the four bits start at offset 12
              NVIC_EnableIRQ(EXTI9_5_IRQn);
              NVIC_SetPriority(EXTI9_5_IRQn,priority);

          break;

   case 8 :
	          SYSCFG_EXTICR3 = ((SYSCFG_EXTICR3  ) &(~(0b1111<<((pin_number-8)*4)))) |(port_name <<((pin_number-8)*4) );
	          NVIC_EnableIRQ(EXTI9_5_IRQn);
	          NVIC_SetPriority(EXTI9_5_IRQn,priority);

	       break;
   case 9 :
	          SYSCFG_EXTICR3 = ((SYSCFG_EXTICR3  ) &(~(0b1111<<((pin_number-8)*4)))) |(port_name <<((pin_number-8)*4) );
	   	      NVIC_EnableIRQ(EXTI9_5_IRQn);
	   	      NVIC_SetPriority(EXTI9_5_IRQn,priority);

	   	    break;


   ////// EXTI15_10_IRQn      from EXITI10 to EXITI15

   case 10 :
	           SYSCFG_EXTICR3 = ((SYSCFG_EXTICR3  ) &(~(0b1111<<((pin_number-8)*4)))) |(port_name <<((pin_number-8)*4) );
	   	       NVIC_EnableIRQ(EXTI15_10_IRQn);
	   	       NVIC_SetPriority(EXTI15_10_IRQn,priority);

	   	    break;
   case 11 :
	           SYSCFG_EXTICR3 = ((SYSCFG_EXTICR3  ) &(~(0b1111<<((pin_number-8)*4)))) |(port_name <<((pin_number-8)*4) );
	           NVIC_EnableIRQ(EXTI15_10_IRQn);
	           NVIC_SetPriority(EXTI15_10_IRQn,priority);

 	   	    break;

	case 12 :
			   SYSCFG_EXTICR4 = ((SYSCFG_EXTICR4  ) &(~(0b1111<<((pin_number-12)*4)))) |(port_name <<((pin_number-12)*4) );
			   NVIC_EnableIRQ(EXTI15_10_IRQn);
			   NVIC_SetPriority(EXTI15_10_IRQn,priority);

			 break;

   case 13 :
	           SYSCFG_EXTICR4 = ((SYSCFG_EXTICR4  ) &(~(0b1111<<((pin_number-12)*4)))) |(port_name <<((pin_number-12)*4) );
	  		   NVIC_EnableIRQ(EXTI15_10_IRQn);
	  		   NVIC_SetPriority(EXTI15_10_IRQn,priority);

	  		 break;

   case 14 :
	           SYSCFG_EXTICR4 = ((SYSCFG_EXTICR4  ) &(~(0b1111<<((pin_number-12)*4)))) |(port_name <<((pin_number-12)*4) );
	   	  	   NVIC_EnableIRQ(EXTI15_10_IRQn);
	   	  	   NVIC_SetPriority(EXTI15_10_IRQn,priority);

	   	  	 break;

   case 15 :
	           SYSCFG_EXTICR4 = ((SYSCFG_EXTICR4  ) &(~(0b1111<<((pin_number-12)*4)))) |(port_name <<((pin_number-12)*4) );
	           NVIC_EnableIRQ(EXTI15_10_IRQn);
	       	   NVIC_SetPriority(EXTI15_10_IRQn,priority);

	   	  	 break;

}




	switch(rising_falling_or_both)

	{
	case   RISING_EDGE:    /// to enable pin number 0 as rising edge but 1   in  bit number 0  and so one

		EXTI_RTSR |=  (1<<pin_number);  //enable the rising edge interrupt

		EXTI_FTSR = (EXTI_FTSR  ) &(~(0b1<<pin_number)) ;      // make sure falling edge interrupt is not be activated
		 break;


	case  FALLING_EDGE:   /// to enable pin number 0 as falling edge but 1   in  bit number 0  and so one
		EXTI_FTSR |= (1 <<pin_number );
		EXTI_RTSR = (EXTI_RTSR  ) &(~(0b1<<((pin_number))));  // make sure raising edge interrupt is not be activated
		 break;

	case  BOTH_RISING_FALLING_EDGE:

		EXTI_RTSR = ((EXTI_RTSR  ) &(~(0b1<<((pin_number))) |(1<<pin_number)));

		EXTI_FTSR = ((EXTI_FTSR  ) &(~(0b1<<pin_number)) |(1 <<pin_number ));

	}
}

