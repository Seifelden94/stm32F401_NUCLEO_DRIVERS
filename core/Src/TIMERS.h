#ifndef TIMERS_H_
#define TIMERS_H_
#include<stdint.h>


#define APB2_clock_HZ       84000000


//// time2

#define clock_time2_period

/*
 * 13.2 TIM2 to TIM5 main features
General-purpose TIMx timer features include:
• 16-bit (TIM3 and TIM4) or 32-bit (TIM2 and TIM5) up, down, up/down auto-reload
counter.
• 16-bit programmable prescaler used to divide (also “on the fly”) the counter clock
frequency by any factor between 1 and 65536.
• Up to 4 independent channels for:
– Input capture
– Output compare
– PWM generation (Edge- and Center-aligned modes)
– One-pulse mode output
• Synchronization circuit to control the timer with external signals and to interconnect
several timers.
• Interrupt/DMA generation on the following events:
– Update: counter overflow/underflow, counter initialization (by software or
internal/external trigger)
– Trigger event (counter start, stop, initialization or count by internal/external trigger)
– Input capture
– Output compare
• Supports incremental (quadrature) encoder and hall-sensor circuitry for positioning
purposes
• Trigger input for external clock or cycle-by-cycle current management


The time-base unit includes:
• Counter Register (TIMx_CNT)
• Prescaler Register (TIMx_PSC):
• Auto-Reload Register (TIMx_ARR)

 */


#define TIME_INTERRUPT_priorety  2                /// from 0 to 15 the lower the number the higher the priority



// TIMx control register 1 (TIMx_CR1)
#define   TIMx_CR1_OFFSET      0x00

//  TIMx control register 2 (TIMx_CR2)
#define       TIMx_CR2_OFFSET  0x04

//TIMx slave mode control register (TIMx_SMCR)
#define TIMx_SMCR_OFFSET    0x08

//TIMx DMA/Interrupt enable register (TIMx_DIER)
#define   TIMx_DIER_OFFSET   0x0c

///TIMx status register (TIMx_SR)
#define   TIMx_SR_OFFSET       0x10

///TIMx event generation register (TIMx_EGR)
#define    TIMx_EGR_OFFSET           0x14


//TIMx capture/compare mode register 1 (TIMx_CCMR1)
#define   TIMx_CCMR1_OFFSET          0x18

//TIMx capture/compare mode register 2 (TIMx_CCMR2)
#define    TIMx_CCMR2_OFFSET        0x1c

//TIMx capture/compare enable register (TIMx_CCER)
#define    TIMx_CCER_OFFSET       0x20

//TIMx counter (TIMx_CNT)
#define    TIMx_CNT      0x24


//13.4.11 TIMx prescaler (TIMx_PSC)
#define      TIMx_PSC_OFFSET              0x28

//TIMx auto-reload register (TIMx_ARR)  Reset value: 0xFFFF FFFF
#define    TIMx_ARR_OFFSET        0x2c

//TIMx capture/compare register 1 (TIMx_CCR1)
#define   TIMx_CCR1_OFFSET     0x34

//TIMx capture/compare register 2 (TIMx_CCR2)
#define      TIMx_CCR2_OFFSET    0x34

//TIMx capture/compare register 3 (TIMx_CCR3)
#define   TIMx_CCR3_OFFSET     0x3c

//TIMx capture/compare register 4 (TIMx_CCR4)
#define   TIMx_CCR4_OFFSET    0x40

// dead-time register (TIMx_BDTR)
#define  TIMx_BDTR_OFFSET 0x44

//TIMx DMA control register (TIMx_DCR)
#define   TIMx_DCR_OFFSET   0x48

//TIMx DMA address for full transfer (TIMx_DMAR)
#define TIMx_DMAR_OFFSET    0x4c

//TIM2 option register (TIM2_OR)
#define   TIM2_OR_OFFSET   0x50

//TIM5 option register (TIM5_OR)
#define  TIM5_OR_OFFSET   0x50


#define TIM1_BDTR         (*((volatile uint16_t *) (0x40010000+ TIMx_BDTR_OFFSET)))  /// 16 bits

//// Timer2  0x4000 0000 - 0x4000 03FF

#define  TIMER2_BASE_ADDRESE   0x40000000





#define TIM2_CR1         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+ TIMx_CR1_OFFSET)))  /// 16 bits


/*Bits 6:5 CMS: Center-aligned mode selection
00: Edge-aligned mode. The counter counts up or down depending on the direction bit
(DIR).
01: Center-aligned mode 1. The counter counts up and down alternatively. Output compare
interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
only when the counter is counting down.
10: Center-aligned mode 2. The counter counts up and down alternatively. Output compare
interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
only when the counter is counting up.
11: Center-aligned mode 3. The counter counts up and down alternatively. Output compare
interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
both when the counter is counting up or down.
Note: It is not allowed to switch from edge-aligned mode to center-aligned mode as long as
the counter is enabled (CEN=1)*/

#define  Edge_aligned_mode    0b00

#define CMS_OFFSET            5

#define CMS                Edge_aligned_mode

/*
 * Bit 4 DIR: Direction
0: Counter used as upcounter
1: Counter used as downcounter
Note: This bit is read only when the timer is configured in Center-aligned mode or Encoder
mode.
 */
#define UPCOUNTER     0
#define DOWNCOUNTER   1
#define  DIR_OFFSET      4
#define  DIR             UPCOUNTER

/*
 *Bit 7 ARPE: Auto-reload preload enable
0: TIMx_ARR register is not buffered
1: TIMx_ARR register is buffered*/

#define ARPE_OFFSET  7
#define ARPE    1
/*
Bit 0 CEN: Counter enable
0: Counter disabled
1: Counter enabled
Note: External clock, gated mode and encoder mode can work only if the CEN bit has been
previously set by software. However trigger mode can set the CEN bit automatically by
hardware.
CEN is cleared automatically in one-pulse mode, when an update event occurs.
 */
#define CEN_OFFSET         0

#define CEN_ON         1




#define TIM2_CR2         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+TIMx_CR2_OFFSET )))  /// 16 bits

#define TIM2_SMCR         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+ TIMx_SMCR_OFFSET)))  /// 16 bits





#define TIM2_DIER         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+TIMx_DIER_OFFSET )))  /// 16 bits

/*
Bit 1 CC1IE: Capture/Compare 1 interrupt enable
0: CC1 interrupt disabled
1: CC1 interrupt enabled
 */
#define CC1IE_OFFSET     1
#define CC1IE            1

/*
Bit 4 DIR: Direction
0: Counter used as upcounter
1: Counter used as downcounter
Note: This bit is read only when the timer is configured in Center-aligned mode or Encoder
mode.*/

#define   UIE_OFFSET   0
#define   UIE_ON        1





#define TIM2_SR         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+TIMx_SR_OFFSET )))  /// 16 bits

/*
 * Bit 4 CC4IF: Capture/Compare 4 interrupt flag
 *Bit 3 CC3IF: Capture/Compare 3 interrupt flag
refer to CC1IF description
Bit 2 CC2IF: Capture/Compare 2 interrupt flag
refer to CC1IF description

Bit 1 CC1IF: Capture/compare 1 interrupt flag
If channel CC1 is configured as output:
This flag is set by hardware when the counter matches the compare value, with some
exception in center-aligned mode (refer to the CMS bits in the TIMx_CR1 register
description). It is cleared by software.
0: No match
1: The content of the counter TIMx_CNT matches the content of the TIMx_CCR1 register.
When the contents of TIMx_CCR1 are greater than the contents of TIMx_ARR, the CC1IF bit
goes high on the counter overflow (in upcounting and up/down-counting modes) or underflow
(in downcounting mode)
If channel CC1 is configured as input:
This bit is set by hardware on a capture. It is cleared by software or by reading the
TIMx_CCR1 register.
0: No input capture occurred
1: The counter value has been captured in TIMx_CCR1 register (An edge has been detected
on IC1 which matches the selected polarity)
 */

#define CC1IF_OFFSET       1



/*
 * Bit 0 UIF: Update interrupt flag
″ This bit is set by hardware on an update event. It is cleared by software.
0: No update occurred.
1: Update interrupt pending. This bit is set by hardware when the registers are updated:
″ At overflow or underflow (for TIM2 to TIM5) and if UDIS=0 in the TIMx_CR1 register.
″ When CNT is reinitialized by software using the UG bit in TIMx_EGR register, if URS=0
and UDIS=0 in the TIMx_CR1 register.
When CNT is reinitialized by a trigger event (refer to the synchro control register description),
if URS=0 and UDIS=0 in the TIMx_CR1 register.
 */

#define UIF_OFFSET   0




#define TIM2_EGR        (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+TIMx_EGR_OFFSET )))  /// 16 bits

/*
Bit 0 UG: Update generation
This bit can be set by software, it is automatically cleared by hardware.
0: No action
1: Re-initialize the counter and generates an update of the registers. Note that the prescaler
counter is cleared too (anyway the prescaler ratio is not affected). The counter is cleared if
the center-aligned mode is selected or if DIR=0 (upcounting), else it takes the auto-reload
value (TIMx_ARR) if DIR=1 (downcounting).*/

#define UG_OFFSET           0


#define TIM2_CCMR1         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+ TIMx_CCMR1_OFFSET)))  /// 16 bits



/*
 * Bit 7 OC1CE: Output compare 1 clear enable
OC1CE: Output Compare 1 Clear Enable
0: OC1Ref is not affected by the ETRF input
1: OC1Ref is cleared as soon as a High level is detected on ETRF input
 */

#define  OC1CE_OFFSET    7
#define  OC1CE            0      //// it is very imporatant to make it 0 otherwise OC1Ref is cleared as soon as a High level
                                 //// is detected on ETRF input which caused the pwm to always be 0



/*
 * Bits 6:4 OC1M: Output compare 1 mode
These bits define the behavior of the output reference signal OC1REF from which OC1 and
OC1N are derived. OC1REF is active high whereas OC1 and OC1N active level depends
on CC1P and CC1NP bits.
000: Frozen - The comparison between the output compare register TIMx_CCR1 and the
counter TIMx_CNT has no effect on the outputs.(this mode is used to generate a timing
base).
001: Set channel 1 to active level on match. OC1REF signal is forced high when the counter
TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
010: Set channel 1 to inactive level on match. OC1REF signal is forced low when the
counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
011: Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1.
100: Force inactive level - OC1REF is forced low.
101: Force active level - OC1REF is forced high.
110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as
TIMx_CNT>TIMx_CCR1 else active (OC1REF=1).
111: PWM mode 2 - In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1
else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else
inactive.
Note: In PWM mode 1 or 2, the OCREF level changes only when the result of the
comparison changes or when the output compare mode switches from “frozen” mode
to “PWM” mode.
 */

#define    PWM_MODE1  110
#define    PWM_MODE2 111

#define   OC1M_OFFSET       4
#define    OC1M            PWM_MODE1               /// choose the mood


/*
 * Bit 3 OC1PE: Output compare 1 preload enable
0: Preload register on TIMx_CCR1 disabled. TIMx_CCR1 can be written at anytime, the
new value is taken in account immediately.
1: Preload register on TIMx_CCR1 enabled. Read/Write operations access the preload
register. TIMx_CCR1 preload value is loaded in the active register at each update event.
Note: 1: These bits can not be modified as long as LOCK level 3 has been programmed
(LOCK bits in TIMx_BDTR register) and CC1S=00 (the channel is configured in
output).
2: The PWM mode can be used without validating the preload register only in onepulse
mode (OPM bit set in TIMx_CR1 register). Else the behavior is not guaranteed.
 */
#define OC1PE_OFFSET     3
#define OC1PE             1
#define TIM2_CCMR2         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+ TIMx_CCMR2_OFFSET)))  /// 16 bits

#define TIM2_CCER         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+TIMx_CCER_OFFSET )))  /// 16 bits

/*
 * Bit 3 CC1NP: Capture/Compare 1 output Polarity.
CC1 channel configured as output:
CC1NP must be kept cleared in this case.
CC1 channel configured as input:
This bit is used in conjunction with CC1P to define TI1FP1/TI2FP1 polarity. refer to CC1P
description.
*/

/*
Bit 2 Reserved, must be kept at reset value.

Bit 1 CC1P: Capture/Compare 1 output Polarity.
CC1 channel configured as output:
0: OC1 active high
1: OC1 active low

///
CC1 channel configured as input:
CC1NP/CC1P bits select TI1FP1 and TI2FP1 polarity for trigger or capture operations.
00: noninverted/rising edge
Circuit is sensitive to TIxFP1 rising edge (capture, trigger in reset, external clock or trigger
mode), TIxFP1 is not inverted (trigger in gated mode, encoder mode).
01: inverted/falling edge
Circuit is sensitive to TIxFP1 falling edge (capture, trigger in reset, external clock or trigger
mode), TIxFP1 is inverted (trigger in gated mode, encoder mode).
10: reserved, do not use this configuration.
11: noninverted/both edges
Circuit is sensitive to both TIxFP1 rising and falling edges (capture, trigger in reset, external
clock or trigger mode), TIxFP1 is not inverted (trigger in gated mode). This configuration
must not be used for encoder mode.
*/
#define CC1P_OFFSET          1

#define CC1P                 0               /// it can be 0 or 1

/*
Bit 0 CC1E: Capture/Compare 1 output enable.
CC1 channel configured as output:
0: Off - OC1 is not active
1: On - OC1 signal is output on the corresponding output pin
CC1 channel configured as input:
This bit determines if a capture of the counter value can actually be done into the input
capture/compare register 1 (TIMx_CCR1) or not.
0: Capture disabled
1: Capture enabled
 */

#define CC1E_OFFSET   0

#define CC1E          1     ///


#define TIM2_CNT         (*((volatile uint32_t *) (TIMER2_BASE_ADDRESE+TIMx_CNT )))  /// 32 bits
//Bits 31:16 CNT[31:16]: High counter value (on TIM2 and TIM5).
//Bits 15:0 CNT[15:0]: Counter value


#define TIM2_PSC         (*((volatile uint32_t *) (TIMER2_BASE_ADDRESE+TIMx_PSC_OFFSET )))  /// 16 bits
/*
 * Bits 15:0 PSC[15:0]: Prescaler value
The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
PSC contains the value to be loaded in the active prescaler register at each update event
(including when the counter is cleared through UG bit of TIMx_EGR register or through
trigger controller when configured in “reset mode”).
 */
#define PSC_bit_OFFSET     0
#define PSC_VALUE         (84-1)   //  make the clock divide by 1 and 65536   if I  put 0 the clk will be divided by (1+0)=1

//#define clock_f_time2  ( (APB2_clock_HZ/(PSC_VALUE+1 )))

#define TIME2_F_HZ         (APB2_clock_HZ/(PSC_VALUE+1))  /// might use later


//////////////////

#define TIM2_ARR         (*((volatile uint32_t *) (TIMER2_BASE_ADDRESE+ TIMx_ARR_OFFSET)))  /// 32 bits

#define TIM2_CCR1         (*((volatile uint32_t *) (TIMER2_BASE_ADDRESE+TIMx_CCR1_OFFSET )))  /// 32 bits

/*
 *Bits 31:16 CCR1[31:16]: High Capture/Compare 1 value (on TIM2 and TIM5).
Bits 15:0 CCR1[15:0]: Low Capture/Compare 1 value
If channel CC1 is configured as output:
CCR1 is the value to be loaded in the actual capture/compare 1 register (preload value).
It is loaded permanently if the preload feature is not selected in the TIMx_CCMR1 register
(bit OC1PE). Else the preload value is copied in the active capture/compare 1 register when
an update event occurs.
The active capture/compare register contains the value to be compared to the counter
TIMx_CNT and signaled on OC1 output.
If channel CC1is configured as input:
CCR1 is the counter value transferred by the last input capture 1 event (IC1). The
TIMx_CCR1 register is read-only and cannot be programmed.*/

#define TIM2_CCR2         (*((volatile uint32_t *) (TIMER2_BASE_ADDRESE+ TIMx_CCR2_OFFSET)))  /// 32 bits

#define TIM2_CCR3         (*((volatile uint32_t *) (TIMER2_BASE_ADDRESE+ TIMx_CCR3_OFFSET)))  /// 32 bits

#define TIM2_CCR4         (*((volatile uint32_t *) (TIMER2_BASE_ADDRESE+ TIMx_CCR4_OFFSET)))  /// 32 bits


#define TIM2_BDTR         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+ TIMx_BDTR_OFFSET)))  /// 16 bits

/*
 * Bit 15 MOE: Main output enable
This bit is cleared asynchronously by hardware as soon as the break input is active. It is set
by software or automatically depending on the AOE bit. It is acting only on the channels
which are configured in output.
0: OC and OCN outputs are disabled or forced to idle state.
1: OC and OCN outputs are enabled if their respective enable bits are set (CCxE, CCxNE in
TIMx_CCER register).
See OC/OCN enable description for more details (Section 12.4.9: TIM1 capture/compare
enable register (TIMx_CCER)).
 */

#define MOE_OFFSET   15
#define MOE           1

/*\
 * Bit 11 OSSR: Off-state selection for Run mode
This bit is used when MOE=1 on channels having a complementary output which are
configured as outputs. OSSR is not implemented if no complementary output is implemented
in the timer.
See OC/OCN enable description for more details (Section 12.4.9: TIM1 capture/compare
enable register (TIMx_CCER)).
0: When inactive, OC/OCN outputs are disabled (OC/OCN enable output signal=0).
1: When inactive, OC/OCN outputs are enabled with their inactive level as soon as CCxE=1
or CCxNE=1. Then, OC/OCN enable output signal=1
Note: This bit can not be modified as soon as the LOCK level 2 has been programmed (LOCK
bits in TIMx_BDTR register).*/

#define OSSR_OFFSET        11
#define OSSR               1

/*
Bit 10 OSSI: Off-state selection for Idle mode
This bit is used when MOE=0 on channels configured as outputs.
See OC/OCN enable description for more details (Section 12.4.9: TIM1 capture/compare
enable register (TIMx_CCER)).
0: When inactive, OC/OCN outputs are disabled (OC/OCN enable output signal=0).
1: When inactive, OC/OCN outputs are forced first with their idle level as soon as CCxE=1 or
CCxNE=1. OC/OCN enable output signal=1)
Note: This bit can not be modified as soon as the LOCK level 2 has been programmed (LOCK
bits in TIMx_BDTR register).*/
#define OSSI_OFFSET        10
#define OSSI               1

/*
Bits 9:8 LOCK[1:0]: Lock configuration
These bits offer a write protection against software errors.
00: LOCK OFF - No bit is write protected.
01: LOCK Level 1 = DTG bits in TIMx_BDTR register, OISx and OISxN bits in TIMx_CR2
register and BKE/BKP/AOE bits in TIMx_BDTR register can no longer be written.
10: LOCK Level 2 = LOCK Level 1 + CC Polarity bits (CCxP/CCxNP bits in TIMx_CCER
register, as long as the related channel is configured in output through the CCxS bits) as well
as OSSR and OSSI bits can no longer be written.
11: LOCK Level 3 = LOCK Level 2 + CC Control bits (OCxM and OCxPE bits in
TIMx_CCMRx registers, as long as the related channel is configured in output through the
CCxS bits) can no longer be written.
Note: The LOCK bits can be written only once after the reset. Once the TIMx_BDTR register
has been written, their content is frozen until the next reset.
 */

#define TIM2_DCR         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+TIMx_DCR_OFFSET )))  /// 16 bits

#define TIM2_DMAR         (*((volatile uint16_t *) (TIMER2_BASE_ADDRESE+TIMx_DMAR_OFFSET )))  /// 16 bits














/////////////////////////////////////////////////////////////timer4



#define  TIMER4_BASE_ADDRESE   0x40000800


#define TIM4_CR1         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+ TIMx_CR1_OFFSET)))  /// 16 bits

/*
 * ARPE: Auto-reload preload enable
0: TIMx_ARR register is not buffered
1: TIMx_ARR register is buffered

 Bit 4 DIR: Direction
0: Counter used as upcounter
1: Counter used as downcounter
Note: This bit is read only when the timer is configured in Center-aligned mode or Encoder
mode.

Bit 0 CEN: Counter enable
0: Counter disabled
1: Counter enabled
Note: External clock, gated mode and encoder mode can work only if the CEN bit has been
previously set by software. However trigger mode can set the CEN bit automatically by
hardware.
CEN is cleared automatically in one-pulse mode, when an update event occurs.
 */
#define CEN_OFFSET         0

#define CEN_ON         1

#define TIM4_CR2         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+TIMx_CR2_OFFSET )))  /// 16 bits


#define TIM4_SMCR         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+ TIMx_SMCR_OFFSET)))  /// 16 bits

#define TIM4_DIER         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+TIMx_DIER_OFFSET )))  /// 16 bits



#define TIM4_SR         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+TIMx_SR_OFFSET )))  /// 16 bits

/*
 * Bit 0 UIF: Update interrupt flag
″ This bit is set by hardware on an update event. It is cleared by software.
0: No update occurred.
1: Update interrupt pending. This bit is set by hardware when the registers are updated:
″ At overflow or underflow (for TIM2 to TIM5) and if UDIS=0 in the TIMx_CR1 register.
″ When CNT is reinitialized by software using the UG bit in TIMx_EGR register, if URS=0
and UDIS=0 in the TIMx_CR1 register.
When CNT is reinitialized by a trigger event (refer to the synchro control register description),
if URS=0 and UDIS=0 in the TIMx_CR1 register.
 */

#define UIF_OFFSET   0




#define TIM4_EGR        (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+TIMx_EGR_OFFSET )))  /// 16 bits

#define TIM4_CCMR1         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+ TIMx_CCMR1_OFFSET)))  /// 16 bits

#define TIM4_CCMR2         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+ TIMx_CCMR2_OFFSET)))  /// 16 bits

#define TIM4_CCER         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+TIMx_CCER_OFFSET )))  /// 16 bits

#define TIM4_CNT         (*((volatile uint32_t *) (TIMER4_BASE_ADDRESE+TIMx_CNT )))  /// 32 bits
//Bits 31:16 CNT[31:16]: High counter value (on TIM2 and TIM5).
//Bits 15:0 CNT[15:0]: Counter value



#define TIM4_PSC         (*((volatile uint32_t *) (TIMER4_BASE_ADDRESE+TIMx_PSC_OFFSET )))  /// 16 bits
/*
 * Bits 15:0 PSC[15:0]: Prescaler value
The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
PSC contains the value to be loaded in the active prescaler register at each update event
(including when the counter is cleared through UG bit of TIMx_EGR register or through
trigger controller when configured in “reset mode”).
 */

#define PSC_bit_OFFSET     0
#define PSC_time4_VALUE        (84-1)   //  make the clock divide by 1 and 65536   if I  put 0 the clk will be divided by (1+0)=1
// F for timers = F cl/(1+prescaler)

#define TIME4_F_KHZ         (APB1_clock_KH/(PSC_VALUE+1))



#define TIM4_ARR         (*((volatile uint32_t *) (TIMER4_BASE_ADDRESE+ TIMx_ARR_OFFSET)))  /// 32 bits

#define TIM4_CCR1         (*((volatile uint32_t *) (TIMER4_BASE_ADDRESE+TIMx_CCR1_OFFSET )))  /// 32 bits

#define TIM4_CCR2         (*((volatile uint32_t *) (TIMER4_BASE_ADDRESE+ TIMx_CCR2_OFFSET)))  /// 32 bits

#define TIM4_CCR3         (*((volatile uint32_t *) (TIMER4_BASE_ADDRESE+ TIMx_CCR3_OFFSET)))  /// 32 bits

#define TIM4_CCR4         (*((volatile uint32_t *) (TIMER4_BASE_ADDRESE+ TIMx_CCR4_OFFSET)))  /// 32 bits

#define TIM4_DCR         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+TIMx_DCR_OFFSET )))  /// 16 bits

#define TIM4_DMAR         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+TIMx_DMAR_OFFSET )))  /// 16 bits
//////////////////////////////////////////
void timer2_initi(void);

void delaytime2_msec(int msec);

void timer4_initi(void);
void delaytime4_msec(int msec);
void delaytime4_micro_sec(int microsec);


/////////////////////

void  time2_interrupt_intialise(void);
void time2_interrupt_msecond(int msecond);




////PWM
void pwm_time2_edge_intialise(void)    ;
void pwm_frequency_deuty_edge(int dutey, int frequency);
void pwm_interrupt_enable(void);

#endif
