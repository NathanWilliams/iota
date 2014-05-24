# Author: Nathan Williams
# Copyright: 2014-05-06
#

#Config
DEVICE     = atmega168
CLOCK      = 8000000
PROGRAMMER = -c usbtiny
#PROGRAMMER = -c dragon_isp -Pusb
OBJECTS    = main.o transport.o receive.o nrf24l01.o mqttsn/mqttsn-messages.o hardware/platform.o hardware/RF24.o new.o
#I should write a script to generate the fuses and call it here
FUSES      = -U hfuse:w:0xdf:m -U lfuse:w:0xe2:m
#FUSES      = -U hfuse:w:0x9f:m -U lfuse:w:0xe2:m #enable debugWire


AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -g 
C_FLAGS = -std=c99

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) $(C_FLAGS) -c $< -o $@

.cpp.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c

