TARGET = kernel7.img
ELFILE = myos.elf 
CC = arm-none-eabi-gcc
OC = arm-none-eabi-objcopy
EM = qemu-system-arm
CPU = cortex-a7
MEM = 1024


CFLAGS = -mcpu=$(CPU) -fpic -ffreestanding -Wall
EMFLAGS = -m $(MEM) -M raspi2 -serial null -serial stdio -kernel  $(OBJS_DIR)/$(ELFILE)
# EMFLAGS= -m $(MEM) -M raspi2 -serial stdio -kernel  $(OBJS_DIR)/$(ELFILE)
CSRCFLAGS = -g -O2 -Wall -Wextra
LFLAGS = -ffreestanding -O2 -nostdlib

SRC_CMN_DIR = ../src/common
SRC_KER_DIR = ../src/kernel
INC_CMN_DIR = ../include/common
INC_KER_DIR = ../include/kernel
OBJS_DIR = objs

$(OBJS_DIR)/%.o : $(SRC_KER_DIR)/%.s
	@echo Compiling Assembler Source File $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o : $(SRC_CMN_DIR)/%.c $(INC_CMN_DIR)/%.h
	@echo Compiling C Source File $<
	@$(CC) $(CFLAGS) -I$(INC_CMN_DIR) -I$(INC_KER_DIR) -c $< -o $@ $(CSRCFLAGS)


# $(OBJS_DIR)/%.o : $(SRC_CMN_DIR)/%.c
# 	@echo Compiling C Source File $<
# 	@$(CC) $(CFLAGS) -I$(INC_CMN_DIR) -I$(INC_KER_DIR) -c $< -o $@ $(CSRCFLAGS)
$(OBJS_DIR)/%.o : $(SRC_KER_DIR)/%.c $(INC_KER_DIR)/%.h
	@echo Compiling C Source File $<
	@$(CC) $(CFLAGS) -I$(INC_CMN_DIR) -I$(INC_KER_DIR) -c $< -o $@ $(CSRCFLAGS)


# $(OBJS_DIR)/%.o : $(SRC_CMN_DIR)/%.c $(INC_CMN_DIR)/%.h 
# 	@echo Compiling C Source File $<
# 	@$(CC) $(CFLAGS) -I$(INC_CMN_DIR) -I$(INC_KER_DIR) -c $< -o $@ $(CSRCFLAGS)

fuck:
	@echo $(objectc) and $(objectc1) and $(objects)
	@echo $(obj) and $(objc) and $(objs)

$(OBJS_DIR)/$(ELFILE) : $(OBJS_DIR)/boot.o $(OBJS_DIR)/kernel.o $(OBJS_DIR)/stdlib.o $(OBJS_DIR)/stdio.o $(OBJS_DIR)/uart.o $(OBJS_DIR)/i2c.o
	@echo Linking Objects Files: $^
	@$(CC) -T linker.ld -o $(OBJS_DIR)/$(ELFILE) $(LFLAGS) $^
	@echo Extensible Linkable Format File: $@ created

# $(OBJS_DIR)/$(ELFILE) : $(OBJS_DIR)/boot.o $(OBJS_DIR)/uart.o $(OBJS_DIR)/i2c.o $(OBJS_DIR)/stdio.o $(OBJS_DIR)/stdlib.o $(OBJS_DIR)/kernel.o
# # $(OBJS_DIR)/$(ELFILE) : $(OBJS_DIR)/$(notdir $(obj)) $(OBJS_DIR)/$(notdir $(objc)) $(OBJS_DIR)/$(notdir $(objs))
# 	@echo Linking Objects Files: $^
# 	@$(CC) -T linker.ld -o $(OBJS_DIR)/$(ELFILE) $(LFLAGS) $^
# 	@echo Extensible Linkable Format File: $@ created

$(TARGET) : $(OBJS_DIR)/$(ELFILE)
	@$(OC) $(OBJS_DIR)/$(ELFILE) -O binary $(OBJS_DIR)/$(TARGET)
	@echo Kernel Image File: $(TARGET) created

all: $(TARGET)

.PHONY: clean run

clean:
	@echo Removing Object Files $(wildcard $(OBJS_DIR)/*.o)
	@rm $(OBJS_DIR)/*.o
	@echo Removing $(ELFILE)
	@rm $(OBJS_DIR)/$(ELFILE)
	@echo Removing $(TARGET)
	@rm $(OBJS_DIR)/$(TARGET)

run: $(OBJS_DIR)/$(ELFILE)
	$(EM) $(EMFLAGS)

run1: $(OBJS_DIR)/$(ELFILE)
	$(EM) $(EMFLAGS1)
