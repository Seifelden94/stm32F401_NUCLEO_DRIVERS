#include "spi.h"


uint8_t spi_recive[10];


//// do not forgot to choose the alternate function in the crosponding GPIO pins. and declear the pin that will be used to control another slave as output
// Also you could make the GPIO pin to be the fasts by typing to the speed register

void spi1_master_confegration(void)  //configure this spi as a master
{    //
	/// RCC APB2 peripheral clock enable register (RCC_APB2ENR))


	RCC_APB2ENR=RCC_APB2ENR|(1<<12);  // put 1 in spi1 enable bit which is  number 12 to enable the clock

	SPI1_CR1=SPI1_CR1&(~(0b1<<DFF_OFFSET))|(DFF<<DFF_OFFSET);  //0: 8-bit data frame format is selected for transmission/reception
	                                                           //when 0: 8-bit data frame format is selected for transmission/reception

	SPI1_CR1=SPI1_CR1&(~(0b1<<RXONLY_OFFSET))|(RXONLY<<RXONLY_OFFSET);  // when 0: Full duplex (Transmit and receive)

	SPI1_CR1=SPI1_CR1&(~(0b1<<SSM_OFFSET))|(SSM<<SSM_OFFSET);   //Software slave management

	SPI1_CR1=SPI1_CR1&(~(0b1<<SSI_OFFSET ))|(SSI <<SSI_OFFSET );        //Internal slave select

	SPI1_CR1=SPI1_CR1&(~(0b1<<LSBFIRST_OFFSET))|(LSBFIRST<<LSBFIRST_OFFSET); //LSBFIRST: Frame format




	SPI1_CR1=SPI1_CR1&(~(0b111<<BR_OFFSET))|(BR<<BR_OFFSET);  //Bits 5:3 BR[2:0]: Baud rate control

	SPI1_CR1=SPI1_CR1&(~(0b1<<MSTR_OFFSET))|(MSTR<<MSTR_OFFSET);// Master or slave selection

	SPI1_CR1=SPI1_CR1&(~(0b1<<CPOL_OFFSET))|(CPOL<<CPOL_OFFSET); ///Clock polarity

	SPI1_CR1=SPI1_CR1&(~(0b1<<CPHA_OFFSET))|(CPHA<<CPHA_OFFSET);/// CPHA: Clock phase

	SPI1_CR1=SPI1_CR1&(~(0b1<<SPE_OFFSET))|(SPE<<SPE_OFFSET);   //SPI enable

	////////will have to configere SPI1_CR2 to use the interrupt or DMA



	//GPIO pin configuration

//for spi 1 the pin used is pin   PA5 is SPI1_SCK,   PA6  is SPI1_MISO, PA7 is SPI1_MOSI, PB6 is SPI1_CS, CS is chip select, in master any gpio pin can be used as chip select .

	/// use the alternate function option in GPIO mode for PA5,PA6,PA7
	//0b01: General purpose output mode
	//   0b10: Alternate function mode
	*GPIOa.MODER = ((*GPIOa.MODER) &(~(0b11<<5*2)))  |(0b10  <<5*2) ;//PA5 is SPI1_SCK
	*GPIOa.MODER = ((*GPIOa.MODER) &(~(0b11<<6*2)))  |(0b10  <<6*2) ;//PA6
	*GPIOa.MODER = ((*GPIOa.MODER) &(~(0b11<<7*2)))  |(0b10  <<7*2) ;//PA7
	//GPIOa.MODER = ((*GPIOa.MODER) &(~(0b11<<0)))  |(0b01  <<5*2) ;// in master I can choose any pin to be chip select

	/// choose the alternate function to be spi for the three pins PA5 is SPI1_SCK,   PA6  is SPI1_MISO, PA7 is SPI1_MOSI


	 // AF5 is spi which is  0101
   /// do that by writing  0101 to the locations of pin 5,6,7   to  GPIOA_AFRL

	    *GPIOa.MODER = ((*GPIOa.MODER) &(~(0b1111<<5*4)))  |(0b0101  <<5*4) ;//PA5 is SPI1_SCK
		*GPIOa.MODER = ((*GPIOa.MODER) &(~(0b1111<<6*4)))  |(0b0101  <<6*4) ;//PA6
		*GPIOa.MODER = ((*GPIOa.MODER) &(~(0b1111<<7*4)))  |(0b0101  <<7*4) ;//PA7
}






/* from data sheet
1-
Enable the SPI by setting the SPE bit to 1.
2. Write the first data item to be transmitted into the SPI_DR register (this clears the TXE
flag).
3. Wait until TXE=1 and write the second data item to be transmitted. Then wait until
RXNE=1 and read the SPI_DR to get the first received data item (this clears the RXNE
bit). Repeat this operation for each data item to be transmitted/received until the n–1
received data.
4. Wait until RXNE=1 and read the last received data.
5. Wait until TXE=1 and then wait until BSY=0 before disabling the SPI.
 */

/// when I want to transmit only and ignore the incoming data an over run flag will be set. after I finish sending all the data I will have to rest it

void spi1_master_transmite(uint8_t* data_to_transmite,int size) ///Transmit data only and discard the received data
{
	 /// in case of me wanting to speak to specific slave. I will have to put 0 in the chip select for this slave, because it is active low.
		//this will let the specific slave know that the data that will be send out will be for it


	SPI1_DR = *(data_to_transmite++);

	for(int i=1; i<=(size-1);i++) // Repeat this operation for each data item to be transmitted/received until the n–1
	{
		while(!(SPI1_SR&(1<<TXE_OFFSET)));   //3. Wait until TXE=1 and write the second data item to be transmitted
		SPI1_DR = *(data_to_transmite++);

		//while(!(SPI_SR&(1<<RXNE_OFFSET )));  ///RXNE=1 and read the SPI_DR to get the first received data item (this clears the RXNEbit)

		//	spi1_master_Recive(&spi_recive);


	}
	while(!(SPI1_SR&(1<<TXE_OFFSET)));
	while((SPI1_SR&(1<<BSY_OFFSET)));



	// clearing the over run flag by reading DR and SR registers I do not care about the recived data.
	/*
	 * Overrun flag (OVR)
	This flag is set when data are received and the previous data have not yet been read from
	SPI_DR. As a result, the incoming data are lost. An interrupt may be generated if the ERRIE
	bit is set in SPI_CR2.
	In this case, the receive buffer contents are not updated with the newly received data from
	the transmitter device. A read operation to the SPI_DR register returns the previous
	correctly received data. All other subsequently transmitted half-words are lost.
	Clearing the OVR bit is done by a read operation on the SPI_DR register followed by a read
	access to the SPI_SR register.
	 */

	//If I cared I will have to read the recived data every time

	uint8_t temp = SPI1_DR;

	     temp=SPI1_SR; /// to clear the flag
}

void spi1_master_recive(uint8_t* data_to_recive,int size) //send dummy data to recive. recive only  you send two time before you start to recive
{ /// in case of me wanting to speak to specific slave. I will have to put 0 in the chip select for this slave, because it is active low.
	//this will let the specific slave know that the data that will be send out will be for it

	/* from data sheet
	1-
	Enable the SPI by setting the SPE bit to 1.  did that in spi configration
	2. Write the first data item to be transmitted into the SPI_DR register (this clears the TXE
	flag).
	3. Wait until TXE=1 and write the second data item to be transmitted. Then wait until
	RXNE=1 and read the SPI_DR to get the first received data item (this clears the RXNE
	bit). Repeat this operation for each data item to be transmitted/received until the n–1
	received data.
	4. Wait until RXNE=1 and read the last received data.
	5. Wait until TXE=1 and then wait until BSY=0 before disabling the SPI.
	 */



	SPI1_DR = 0;// send the first dummy. I need to write twice before I receive the first value


	for(int i=1; i<=(size-1);i++) // Repeat this operation for each data item to be transmitted/received until the n–1
	{
	    while(!(SPI1_SR&(1<<TXE_OFFSET)));   //3. Wait until TXE=1 and write the second data item to be transmitted
	    SPI1_DR = 0;// send dummy data

    	while(!(SPI1_SR&(1<<RXNE_OFFSET )));  ///wait until RXNE=1 and read the SPI_DR to get the  received data item (this clears the RXNEbit)
       *(data_to_recive++)=SPI1_DR; /// read the receved data, and increment the pointer to point to the next location where the next data recive will be saved at


	}

	while(!(SPI1_SR&(1<<RXNE_OFFSET )));  ///Wait until RXNE=1 and read the last received data.
       *(data_to_recive)=SPI1_DR; /// save the last received data,


	while(!(SPI1_SR&(1<<TXE_OFFSET)));
	while((SPI1_SR&(1<<BSY_OFFSET)));

// disable spi here If want to, to save energy by disableing its clock
}


void  Spi1_master_transmit_recive(uint8_t* data_to_transmite,uint8_t* data_to_recive,int size)  // transmit and recive at the same time
{  /// in case of me wanting to speak to specific slave. I will have to put 0 in the chip select for this slave, because it is active low.
	//this will let the specific slave know that the data that will be send out will be for it

	/* from data sheet
		1-
		Enable the SPI by setting the SPE bit to 1.   // did that in spi configration
		2. Write the first data item to be transmitted into the SPI_DR register (this clears the TXE
		flag).
		3. Wait until TXE=1 and write the second data item to be transmitted. Then wait until
		RXNE=1 and read the SPI_DR to get the first received data item (this clears the RXNE
		bit). Repeat this operation for each data item to be transmitted/received until the n–1
		received data.
		4. Wait until RXNE=1 and read the last received data.
		5. Wait until TXE=1 and then wait until BSY=0 before disabling the SPI. /// not nesseserly to disable the spi
		 */

	SPI1_DR= *(data_to_transmite++);

	for(int i=1; i<=(size-1);i++) // Repeat this operation for each data item to be transmitted/received until the n–1

	{ while(!(SPI1_SR&(1<<TXE_OFFSET)));
		SPI1_DR= *(data_to_transmite++);   /// increment the pointer every time to point to the next data to be send in the next irretation
		while(!(SPI1_SR&(1<<RXNE_OFFSET )));  ///wait until RXNE=1 and read the SPI_DR to get the  received data item (this clears the RXNEbit)

		*(data_to_recive++)=SPI1_DR; /// increment the pointer every time to point to the next location to save the data that will be recived  next

	}

	while(!(SPI1_SR&(1<<RXNE_OFFSET )));  ///wait until RXNE=1 and read the SPI_DR to get the  last received data item (this clears the RXNEbit)

			*(data_to_recive)=SPI1_DR;


	while(!(SPI1_SR&(1<<TXE_OFFSET)));
	while((SPI1_SR&(1<<BSY_OFFSET)));

	///disable spi if I want





}











void spi1_slave_confegration(void) // when usind spi1 as a slave
{
	SPI1_CR1=SPI1_CR1&(~(0b1<<DFF_OFFSET))|(DFF<<DFF_OFFSET);  //when dff is 0: 8-bit data frame format is selected for transmission/reception


	SPI1_CR1=SPI1_CR1&(~(0b1<<RXONLY_OFFSET))|(RXONLY<<RXONLY_OFFSET);  // when 0: Full duplex (Transmit and receive)

	SPI1_CR1=SPI1_CR1&(~(0b1<<SSM_OFFSET))|(0<<SSM_OFFSET);   //Software slave management nns will be used as input

	//SPI1_CR1=SPI1_CR1&(~(0b1<<SSI_OFFSET ))|(SSI <<SSI_OFFSET );        //Internal slave select

	SPI1_CR1=SPI1_CR1&(~(0b1<<LSBFIRST_OFFSET))|(LSBFIRST<<LSBFIRST_OFFSET); //LSBFIRST: Frame format




//	SPI1_CR1=SPI1_CR1&(~(0b111<<BR_OFFSET))|(BR<<BR_OFFSET);  //Bits 5:3 BR[2:0]: Baud rate control in slave mood Baud rate is ignored

	SPI1_CR1=SPI1_CR1&(~(0b1<<MSTR_OFFSET))|(0<<MSTR_OFFSET);// Master or slave selection   0 means this spi will work as slave

	SPI1_CR1=SPI1_CR1&(~(0b1<<CPOL_OFFSET))|(CPOL<<CPOL_OFFSET); ///Clock polarity

	SPI1_CR1=SPI1_CR1&(~(0b1<<CPHA_OFFSET))|(CPHA<<CPHA_OFFSET);/// CPHA: Clock phase

	SPI1_CR1=SPI1_CR1&(~(0b1<<SPE_OFFSET))|(SPE<<SPE_OFFSET);   //SPI enable

	////////will have to configere SPI1_CR2 to use the interrupt or DMA

}
/*
 * Note: Prior to changing the CPOL/CPHA bits the SPI must be disabled by resetting the SPE bit.
Master and slave must be programmed with the same timing mode.
The idle state of SCK must correspond to the polarity selected in the SPI_CR1 register (by
pulling up SCK if CPOL=1 or pulling down SCK if CPOL=0).
The Data Frame Format (8- or 16-bit) is selected through the DFF bit in SPI_CR1 register,
and determines the data length during transmission/reception.
 */
/*
 * Note: When a master is communicating with SPI slaves which need to be de-selected between
transmissions, the NSS pin must be configured as GPIO or another GPIO must be used and
toggled by software.
 */



/*
 * Note: The software must ensure that the TXE flag is set to 1 before attempting to write to the Tx
buffer. Otherwise, it overwrites the data previously written to the Tx buffer.
The RXNE flag (Rx buffer not empty) is set on the last sampling clock edge, when the data
are transferred from the shift register to the Rx buffer. It indicates that data are ready to be
read from the SPI_DR register. An interrupt can be generated if the RXNEIE bit in the
SPI_CR2 register is set. Clearing the RXNE bit is performed by reading the SPI_DR
register.
For some configurations, the BSY flag can be used during the last data transfer to wait until
the completion of the transfer.
Full-duplex transmit and receive procedure in master or slave mode (BIDIMODE=0 and
RXONLY=0)
The software has to follow this procedure to transmit and receive data (see Figure 199 and
Figure 200):





/*
 *
 *Tx buffer empty flag (TXE)
When it is set, this flag indicates that the Tx buffer is empty and the next data to be
transmitted can be loaded into the buffer. The TXE flag is cleared when writing to the
SPI_DR register.
Rx buffer not empty (RXNE)
When set, this flag indicates that there are valid received data in the Rx buffer. It is cleared
when SPI_DR is read.
BUSY flag
This BSY flag is set and cleared by hardware (writing to this flag has no effect). The BSY
flag indicates the state of the communication layer of the SPI.
When BSY is set, it indicates that the SPI is busy communicating. There is one exception in
master mode / bidirectional receive mode (MSTR=1 and BDM=1 and BDOE=0) where the
BSY flag is kept low during reception.
The BSY flag is useful to detect the end of a transfer if the software wants to disable the SPI
and enter Halt mode (or disable the peripheral clock). This avoids corrupting the last
transfer. For this, the procedure described below must be strictly respected.
The BSY flag is also useful to avoid write collisions in a multimaster system.
The BSY flag is set when a transfer starts, with the exception of master mode / bidirectional
receive mode (MSTR=1 and BDM=1 and BDOE=0).
It is cleared:
• when a transfer is finished (except in master mode if the communication is continuous)
• when the SPI is disabled
• when a master mode fault occurs (MODF=1)
When communication is not continuous, the BSY flag is low between each communication.
When communication is continuous:
• in master mode, the BSY flag is kept high during all the transfers
• in slave mode, the BSY flag goes low for one SPI clock cycle between each transfer
Note: Do not use the BSY flag to handle each data transmission or reception. It is better to use the
TXE and RXNE flags instead.
 */

/*
 * To avoid any of those effects, it is recommended to respect the following procedure when
disabling the SPI:
In master or slave full-duplex mode (BIDIMODE=0, RXONLY=0)
1. Wait until RXNE=1 to receive the last data
2. Wait until TXE=1
3. Then wait until BSY=0
4. Disable the SPI (SPE=0) and, eventually, enter the Halt mode (or disable the peripheral
clock)
 */
