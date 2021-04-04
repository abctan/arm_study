TARGET := led
OBJS := start.o main.o

CROSS_COMPILE := arm-linux-gnueabihf-


# Make variables (CC, etc...)
AS		    = $(CROSS_COMPILE)as
LD		    = $(CROSS_COMPILE)ld
CC		    = $(CROSS_COMPILE)gcc
CPP		    = $(CC) -E
AR		    = $(CROSS_COMPILE)ar
NM		    = $(CROSS_COMPILE)nm
LDR		    = $(CROSS_COMPILE)ldr
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

$(TARGET).bin:$(OBJS)
	$(LD) -Timx6ul.lds $^ -o $(TARGET).elf
	$(OBJCOPY) -O binary -S -g $(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -D $(TARGET).elf > $(TARGET).dis

%.o:%.S
	$(CC) -g -c $< -o $@
%.o:%.s
	$(CC) -g -c $< -o $@
%.o:%.c
	$(CC) -g -c $< -o $@

clean:
	rm -rf *.o $(TARGET).bin $(TARGET).elf $(TARGET).dis
