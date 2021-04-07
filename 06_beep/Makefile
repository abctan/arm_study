TARGET ?= beep
CROSS_COMPILE ?= arm-linux-gnueabihf-
OUTPUT ?= ./obj
# 资源文件准备
SOURCE_DIR  += driver/clock \
               driver/delay \
               driver/led   \
			   driver/beep  \
               project

INCLUDE_DIR += driver/clock \
               driver/delay \
	           driver/led   \
			   driver/beep  \
	           imx6ull

VPATH := $(SOURCE_DIR)
# 指定gcc要找头文件路径
INCLUDE := $(patsubst %, -I %, $(INCLUDE_DIR))

SOURCE_C     := $(foreach path, $(SOURCE_DIR), $(wildcard $(path)/*.c))
SOURCE_S     := $(foreach path, $(SOURCE_DIR), $(wildcard $(path)/*.S))
SOURCE_s     := $(foreach path, $(SOURCE_DIR), $(wildcard $(path)/*.s))
OBJ_C        := $(patsubst %.c, %.o, $(notdir $(SOURCE_C)))
OBJ_S        := $(patsubst %.S, %.o, $(notdir $(SOURCE_S)))
OBJ_s        := $(patsubst %.s, %.o, $(notdir $(SOURCE_s)))
OUTPUT_OBJ_C := $(patsubst %, $(OUTPUT)/%, $(OBJ_C))
OUTPUT_OBJ_S := $(patsubst %, $(OUTPUT)/%, $(OBJ_S))
OUTPUT_OBJ_s := $(patsubst %, $(OUTPUT)/%, $(OBJ_s))
OUTPUT_OBJS  := $(OUTPUT_OBJ_C) $(OUTPUT_OBJ_S) $(OUTPUT_OBJ_s)

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


$(TARGET).bin:$(OUTPUT_OBJS)
	$(LD) -Timx6ul.lds $^ -o $(OUTPUT)/$(TARGET).elf
	$(OBJCOPY) -O binary -S -g $(OUTPUT)/$(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -D $(OUTPUT)/$(TARGET).elf > $(OUTPUT)/$(TARGET).dis

$(OUTPUT_OBJ_S):$(OUTPUT)/%.o:%.S
	$(CC) -g -c $< $(INCLUDE) -o $@
$(OUTPUT_OBJ_s):$(OUTPUT)/%.o:%.s
	$(CC) -g -c $< $(INCLUDE) -o $@
$(OUTPUT_OBJ_C):$(OUTPUT)/%.o:%.c
	$(CC) -g -c $< $(INCLUDE) -o $@

clean:
	rm -rf *.o $(OUTPUT)/*.o $(TARGET).bin $(OUTPUT)/$(TARGET).elf $(OUTPUT)/$(TARGET).dis
