#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include<stdint.h>



#define  RISING_EDGE       1


#define  FALLING_EDGE      2

#define  BOTH_RISING_FALLING_EDGE      3

//////////////////RCC clock interrupt register (RCC_CIR)

#define RCC_BASE_ADDRESE      0x40023800

#define RCC_APB2ENR         (*((volatile uint32_t *) (RCC_BASE_ADDRESE+ 0x44)))

/*
 * Bit 14 SYSCFGEN: System configuration controller clock enable
Set and cleared by software.
0: System configuration controller clock disabled
1: System configuration controller clock enabled
 */

#define SYSCFGEN_BIT_OFFSET     14

#define SYSCFGEN_CLOCK_ENABLE    1
/////////////////////


#define  SYSCFG_BASE_ADDRESS               0x40013800



/*
 * SYSCFG external interrupt configuration register 1
(SYSCFG_EXTICR1)
Address offset: 0x08
Reset value: 0x0000 0000



Bits 31:16 Reserved, must be kept at reset value.
Bits 15:0 EXTIx[3:0]: EXTI x configuration (x = 0 to 3)
These bits are written by software to select the source input for the EXTIx
external interrupt.
0000: PA[x] pin
0001: PB[x] pin
0010: PC[x] pin
0011: PD[x] pin
0100: PE[x] pin
0101: Reserved
0110: Reserved
0111: PH[x] pin
 */
#define PA    0000                         //// THESE VALUE WHEN WRITING IN  SYSCFG_EXTICR REGISTER HELP CHOOSE THE INTERRUPT pORT NAME AND NUMBER

#define PB    0001

#define PC    0010

#define PD    0011

#define PE    0100

#define PH    0111



///SYSCFG external interrupt configuration register 1 (SYSCFG_EXTICR1)
#define SYSCFG_EXTICR1_OFFSET        0x08



#define SYSCFG_EXTICR1         (*((volatile uint32_t *) (SYSCFG_BASE_ADDRESS+ SYSCFG_EXTICR1_OFFSET)))  /// 32 bits


/*
 * SYSCFG external interrupt configuration register 2
(SYSCFG_EXTICR2)
Bits 15:0 EXTIx[3:0]: EXTI x configuration (x = 4 to 7)
These bits are written by software to select the source input for the EXTIx
external interrupt.
0000: PA[x] pin
0001: PB[x] pin
0010: PC[x] pin
0011: PD[x] pin
0100: PE[x] pin
0101: Reserved
0110: Reserved
0111: PH[x] pin
 */
///SYSCFG external interrupt configuration register 2 (SYSCFG_EXTICR2)
#define SYSCFG_EXTICR2_OFFSET        0x0c



#define SYSCFG_EXTICR2         (*((volatile uint32_t *) (SYSCFG_BASE_ADDRESS+ SYSCFG_EXTICR2_OFFSET)))  /// 32 bits

///////////



/*
 *Bits 31:16 Reserved, must be kept at reset value.
Bits 15:0 EXTIx[3:0]: EXTI x configuration (x = 8 to 11)
These bits are written by software to select the source input for the EXTIx external
interrupt.
0000: PA[x] pin
0001: PB[x] pin
0010: PC[x] pin
0011: PD[x] pin
0100: PE[x] pin
0101: Reserved
0110: Reserved
0111: PH[x] pin
 */
///SYSCFG external interrupt configuration register 3 (SYSCFG_EXTICR3)
#define SYSCFG_EXTICR3_OFFSET        0x10



#define SYSCFG_EXTICR3         (*((volatile uint32_t *) (SYSCFG_BASE_ADDRESS+ SYSCFG_EXTICR3_OFFSET)))  /// 32 bits




/*
 * Bits 31:16 Reserved, must be kept at reset value.
Bits 15:0 EXTIx[3:0]: EXTI x configuration (x = 12 to 15)
These bits are written by software to select the source input for the EXTIx external
interrupt.
0000: PA[x] pin
0001: PB[x] pin
0010: PC[x] pin
0011: PD[x] pin
0100: PE[x] pin
0101: Reserved
0110: Reserved
0111: PH[x] pin
 */

///SYSCFG external interrupt configuration register 4 (SYSCFG_EXTICR4)
#define SYSCFG_EXTICR4_OFFSET        0x14

#define SYSCFG_EXTICR4        (*((volatile uint32_t *) (SYSCFG_BASE_ADDRESS+ SYSCFG_EXTICR4_OFFSET)))  /// 32 bits








/*
 * Interrupt mask register (EXTI_IMR)
Address offset: 0x00
Reset value: 0x0000 0000

Bits 31:23 Reserved, must be kept at reset value.
Bits 22:0 MRx: Interrupt mask on line x

0: Interrupt request from line x is masked
1: Interrupt request from line x is not masked
 */
///0x4001 3C00 - 0x4001 3FFF EXTI
#define EXTI_BASE_ADDRESS    0x40013C00



#define EXTI_IMR_OFFSET                 0x00
#define EXTI_IMR       (*((volatile uint32_t *) (EXTI_BASE_ADDRESS+ EXTI_IMR_OFFSET )))  /// 32 bits



/*
 * Rising trigger selection register (EXTI_RTSR)
 * Bits 22:0 TRx: Rising trigger event configuration bit of line x
0: Rising trigger disabled (for Event and Interrupt) for input line
1: Rising trigger enabled (for Event and Interrupt) for input line
 *
 * Note: The external wakeup lines are edge triggered, no glitch must be generated on these lines.
If a rising edge occurs on the external interrupt line while writing to the EXTI_RTSR register,
the pending bit is be set.
Rising and falling edge triggers can be set for the same interrupt line. In this configuration,
both generate a trigger condition.
 */

#define EXTI_RTSR_OFFSET  0x08
#define EXTI_RTSR       (*((volatile uint32_t *) (EXTI_BASE_ADDRESS+ EXTI_RTSR_OFFSET )))  /// 32 bits


/*
 * Falling trigger selection register (EXTI_FTSR)
Address offset: 0x0C
Reset value: 0x0000 0000
 */
#define EXTI_FTSR_OFFSET  0x0c
#define EXTI_FTSR       (*((volatile uint32_t *) (EXTI_BASE_ADDRESS+ EXTI_FTSR_OFFSET )))  /// 32 bits


/*
 * Software interrupt event register (EXTI_SWIER)
Address offset: 0x10
Reset value: 0x0000 0000

Bits 31:23 Reserved, must be kept at reset value.
Bits 22:0 SWIERx: Software Interrupt on line x
If interrupt are enabled on line x in the EXTI_IMR register, writing '1' to SWIERx bit when it is
set at '0' sets the corresponding pending bit in the EXTI_PR register, thus resulting in an
interrupt request generation.
This bit is cleared by clearing the corresponding bit in EXTI_PR (by writing a 1 to the bit).
 */

#define EXTI_SWIER_OFFSET    0x10
#define EXTI_SWIER       (*((volatile uint32_t *) (EXTI_BASE_ADDRESS+ EXTI_SWIER_OFFSET )))  /// 32 bits




/*
 * Pending register (EXTI_PR)
Address offset: 0x14
Reset value: undefined
 */
#define EXTI_PR_OFFSET   0x14
#define EXTI_PR       (*((volatile uint32_t *) (EXTI_BASE_ADDRESS+ EXTI_PR_OFFSET )))  /// 32 bits



/*0xE000E100-
0xE000E11F
NVIC_ISER0-

*/
#define NVIC_ISERx_BASE_ADDRESS     0xE000E100


#define NVIC_ISER0  (*((volatile uint32_t *) (0xE000E100+ 0x00 )))



//function prottype
void choose_interrupt_pins(int port_name, int pin_number, int rising_falling_or_both,int priority) ;
void EXTI0_IRQHandler(void);
void external_interrupt_init(void);
void interrupt_handler(void);
void EXTI2_IRQHandler(void);

#endif
