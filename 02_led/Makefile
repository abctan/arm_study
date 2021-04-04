TARGET := led
OBJ := start.o main.o

$(TARGET).bin:$(OBJ)
	arm-linux-gnueabihf-ld -Timx6ul.lds $^ -o $(TARGET).elf
	arm-linux-gnueabihf-objcopy -O binary -S -g $(TARGET).elf $(TARGET).bin
	arm-linux-gnueabihf-objdump -D $(TARGET).elf > $(TARGET).dis

%.o:%.S
	arm-linux-gnueabihf-gcc -g -c $< -o $@
%.o:%.s
	arm-linux-gnueabihf-gcc -g -c $< -o $@
%.o:%.c
	arm-linux-gnueabihf-gcc -g -c $< -o $@

clean:
	rm -rf *.o $(TARGET).bin $(TARGET).elf $(TARGET).dis
