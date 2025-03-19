MCU = atmega128
F_CPU = 8000000UL

CC = avr-gcc
CFLAGS = -std=c11 -Wall -Wextra -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)
LDFLAGS = -mmcu=$(MCU)
VPATH = libs

SRCS = $(wildcard *.c) $(wildcard libs/*.c)
OBJS = $(SRCS:.c=.o)

PROGRAMMER = stk500v2
PORT = /dev/ttyUSB1
BAUD = 115200

all: firmware.hex

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

firmware.elf: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

firmware.hex: firmware.elf
	avr-objcopy -O ihex -R .eeprom $< $@

flash: firmware.hex
	avrdude -p m128 -P $(PORT) -c $(PROGRAMMER) -b $(BAUD) -U flash:w:$<
clean:
	rm -f $(OBJS) firmware.elf firmware.hex