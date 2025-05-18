######################################################################
#  Project
######################################################################

BINARY		= Usart
SRCFILES	= main.c
SRCFILES	+= oled.c
SRCFILES	+= irq.c
SRCFILES	+= uart.c


SRCFILES	+= Hal/Src/stm32f1xx_hal.c
SRCFILES	+= Cmiss/Device/ST/STM32F1xx/Source/system_stm32f1xx.c
SRCFILES	+= Cmiss/Device/ST/STM32F1xx/Source/gcc/startup_stm32f103xb.s

SRCFILES	+= Hal/Src/stm32f1xx_hal_gpio.c
SRCFILES	+= Hal/Src/stm32f1xx_hal_rcc.c
SRCFILES	+= Hal/Src/stm32f1xx_hal_flash.c
SRCFILES	+= Hal/Src/stm32f1xx_hal_cortex.c
SRCFILES	+= Hal/Src/stm32f1xx_hal_i2c.c
SRCFILES	+= Hal/Src/stm32f1xx_hal_exti.c


all: elf bin

include ./Makefile.incl

DEFS		+= -DSTM32F103xB

# End