# stm32F401_NUCLEO_DRIVERS
# In This repo I am writing Low level Drivers for stm32F401_NUCLEO64
# I am dealing with the microcontroller at the register level without using HAl
# Writing Drivers that could be used seperatly in any future project

## First: I configured the CLOCK for the system clock, I will only need to turn on or off the individual clock for the Prepheral when I am using it and off when I am not using it
## example the individual clock for GPIO, Timer, PWM
## second: I wrote the drivers for GPIO, General Purpose Input Output
## Third: I wrote the Drivers for the timers 16 and 32 bit registers
## Fourth: I wrote the driver for external interrupt
## Fifith: I wrote the drivers for edge aligned PWM, Pulse Width Modelation
## Six: I wrote the drivers for SPI, Serial Peripheral Interface






