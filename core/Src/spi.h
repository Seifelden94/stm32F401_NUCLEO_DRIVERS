#ifndef SPI_H_
#define SPI_H_
#include<stdint.h>
#include"CLOCK.h"
#include "DIO.h"





//SPI control register 1 (SPI_CR1)
#define SPI_CR1_OFFSET    0x00

//SPI control register 2 (SPI_CR2)
#define SPI_CR2_OFFSET    0x04

//SPI status register (SPI_SR)
#define   SPI_SR_OFFSET  0x08

//SPI data register (SPI_DR)
#define   SPI_DR_OFFSET  0x0C


/////////spi 1
#define SPI1_BASE_ADDRESS    0x40013000

#define  SPI1_CR1    (*((volatile uint16_t *) (SPI1_BASE_ADDRESS+SPI_CR1_OFFSET )))  /// 16 bits

#define TIM4_DCR         (*((volatile uint16_t *) (TIMER4_BASE_ADDRESE+TIMx_DCR_OFFSET )))  /// 16 bits
/*
 * Bit 11 DFF: Data frame format
0: 8-bit data frame format is selected for transmission/reception
1: 16-bit data frame format is selected for transmission/reception
Note: This bit should be written only when SPI is disabled (SPE = ‘0’) for correct operation.
It is not used in I2S mode.
 */

#define     DFF_OFFSET 11
#define     DFF         0

/*
 * Bit 10 RXONLY: Receive only
This bit combined with the BIDImode bit selects the direction of transfer in 2-line
unidirectional mode. This bit is also useful in a multislave system in which this particular
slave is not accessed, the output from the accessed slave is not corrupted.
0: Full duplex (Transmit and receive)
1: Output disabled (Receive-only mode)
Note: This bit is not used in I2S mode
 */
#define RXONLY_OFFSET   10
#define RXONLY   0


/*
 * Bit 9 SSM: Software slave management
When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
0: Software slave management disabled
1: Software slave management enabled
Note: This bit is not used in I2S mode and SPI TI mode
 */
#define  SSM_OFFSET   9
#define  SSM           1

/*
Bit 8 SSI: Internal slave select
This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the
NSS pin and the IO value of the NSS pin is ignored.
Note: This bit is not used in I2S mode and SPI TI mode
 */
#define SSI_OFFSET    8
#define SSI           0
/*
 * Bit 7 LSBFIRST: Frame format
0: MSB transmitted first
1: LSB transmitted first
Note: This bit should not be changed when communication is ongoing.
It is not used in I2S mode and SPI TI mode
 */

#define   LSBFIRST_OFFSET    7
#define   LSBFIRST           0
/*
Bit 6 SPE: SPI enable
0: Peripheral disabled
1: Peripheral enabled
Note: This bit is not used in I2S mode.
When disabling the SPI, follow the procedure described in Section 20.3.8.
 */
#define  SPE_OFFSET   6
#define  SPE          1

/*
 * Bits 5:3 BR[2:0]: Baud rate control
000: fPCLK/2
001: fPCLK/4
010: fPCLK/8
011: fPCLK/16
100: fPCLK/32
101: fPCLK/64
110: fPCLK/128
111: fPCLK/256
Note: These bits should not be changed when communication is ongoing.
They are not used in I2S mode.
 */
#define BR_OFFSET 3
#define BR       100  // devide the clock frequency for spi with BR to get the communication speed
/*
 *Bit 2 MSTR: Master selection
0: Slave configuration
1: Master configuration
Note: This bit should not be changed when communication is ongoing.
It is not used in I2S mode
 */
#define MSTR_OFFSET  2
#define MSTR         1  ///1 for master


/*
 * Bit1 CPOL: Clock polarity
0: CK to 0 when idle
1: CK to 1 when idle
Note: This bit should not be changed when communication is ongoing.
It is not used in I2S mode and SPI TI mode.
 */
#define CPOL_OFFSET   1
#define CPOL          1
/*Bit 0 CPHA: Clock phase
0: The first clock transition is the first data capture edge
1: The second clock transition is the first data capture edge
Note: This bit should not be changed when communication is ongoing.
It is not used in I2S mode and SPI TI mode.
 *
 */
#define CPHA_OFFSET    0
#define CPHA           1

#define  SPI1_CR2    (*((volatile uint16_t *) (SPI1_BASE_ADDRESS+SPI_CR2_OFFSET )))  /// 16 bits

/*
 * Bit 7 TXEIE: Tx buffer empty interrupt enable
0: TXE interrupt masked
1: TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.
*/
/*
Bit 6 RXNEIE: RX buffer not empty interrupt enable
0: RXNE interrupt masked
1: RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is
set.
*/


/*
Bit 5 ERRIE: Error interrupt enable
This bit controls the generation of an interrupt when an error condition occurs )(CRCERR,
OVR, MODF in SPI mode, FRE in TI mode and UDR, OVR, and FRE in I2S mode).
0: Error interrupt is masked
1: Error interrupt is enabled*/

/*
Bit 4 FRF: Frame format
0: SPI Motorola mode
1 SPI TI mode
Note: This bit is not used in I2S mode.
Bit 3 Reserved. Forced to 0 by hardware.
*/
/*Bit 2 SSOE: SS output enable
0: SS output is disabled in master mode and the cell can work in multimaster configuration
1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work
in a multimaster environment.
Note: This bit is not used in I2S mode and SPI TI mode.
 */


/*
 * Bit 1 TXDMAEN: Tx buffer DMA enable
When this bit is set, the DMA request is made whenever the TXE flag is set.
0: Tx buffer DMA disabled
1: Tx buffer DMA enabled*/

/*
Bit 0 RXDMAEN: Rx buffer DMA enable
When this bit is set, the DMA request is made whenever the RXNE flag is set.
0: Rx buffer DMA disabled
1: Rx buffer DMA enabled
 */
#define  SPI1_SR    (*((volatile uint16_t *) (SPI1_BASE_ADDRESS+SPI_SR_OFFSET )))  /// 16 bits
/*
 * Bit 7 BSY: Busy flag
0: SPI(or I2S) not busy
1: SPI(or I2S)is busy in communication or Tx buffer is not empty
This flag is set and cleared by hardware.
Note: BSY flag must be used with caution: refer to Section 20.3.7 and Section 20.3.8.
 */
#define BSY_OFFSET    7


/*
 * Bit 1 TXE: Transmit buffer empty
0: Tx buffer not empty
1: Tx buffer empty*/
#define TXE_OFFSET   1

/*
Bit 0 RXNE: Receive buffer not empty
0: Rx buffer empty
1: Rx buffer not empty
 */
#define   RXNE_OFFSET   0

#define  SPI1_DR    (*((volatile uint16_t *) (SPI1_BASE_ADDRESS+SPI_DR_OFFSET )))  /// 16 bits

/*
 * Bits 15:0 DR[15:0]: Data register
Data received or to be transmitted.
The data register is split into 2 buffers - one for writing (Transmit Buffer) and another one for
reading (Receive buffer). A write to the data register will write into the Tx buffer and a read
from the data register will return the value held in the Rx buffer.
Note: These notes apply to SPI mode:
Depending on the data frame format selection bit (DFF in SPI_CR1 register), the data
sent or received is either 8-bit or 16-bit. This selection has to be made before enabling
the SPI to ensure correct operation.
For an 8-bit data frame, the buffers are 8-bit and only the LSB of the register
(SPI_DR[7:0]) is used for transmission/reception. When in reception mode, the MSB of
the register (SPI_DR[15:8]) is forced to 0.
For a 16-bit data frame, the buffers are 16-bit and the entire register, SPI_DR[15:0] is
used for transmission/reception.
 */











#endif
