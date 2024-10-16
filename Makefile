MCU = atmega328p
F_CPU = 16000000UL
BAUD = 9600

# AVRDUDE settings
PROGRAMMER = arduino
PORT = /dev/ttyUSB0
BAUD_RATE = 115200  # Default baud rate for Arduino bootloader

# Compiler settings
CC = avr-gcc
CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -DBAUD=$(BAUD)

# Name of your source file (change it if your source file is not named 'main.c')
TARGET = main

all: upload

# Compile the program
$(TARGET).hex: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).elf $(TARGET).c
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

# Upload the program to the Arduino
upload: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD_RATE) -D -U flash:w:$(TARGET).hex:i

# Clean up generated files
clean:
	rm -f $(TARGET).elf $(TARGET).hex

