# @copyright: Abdallah

# Toolchain variables
CC=arm-none-eabi-
CFLAGS=-g -mcpu=arm926ej-s
LIBS=
TARGET=learn-in-depth

# Source and object file lists
SRC = $(wildcard *.c)
ASM_SRC = $(wildcard *.s)
OBJ = $(SRC:.c=.o) $(ASM_SRC:.s=.o)

# Default target
all: $(TARGET).bin
	@echo "Build is done"

# Rule to build object files from C source
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $< -o $@

# Rule to build object files from assembly source
%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

# Rule to build the ELF file
$(TARGET).elf: $(OBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) -o $@ -Map=Map_file.map

# Rule to build the binary file
$(TARGET).bin: $(TARGET).elf
	$(CC)objcopy.exe -O binary $< $@

# Clean rule to remove build artifacts
clean:
	del /Q *.o *.elf *.bin
