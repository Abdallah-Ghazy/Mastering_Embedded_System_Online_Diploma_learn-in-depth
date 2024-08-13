# Toolchain variables
CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m3 -mthumb -std=c99 -gdwarf-2
LIBS=
TARGET=Pressure_Controller_CortexM3
INCS=-I .

# Source and object file lists
SRC = $(wildcard *.c)
ASM_SRC = $(wildcard *.s)
OBJ = $(SRC:.c=.o) $(ASM_SRC:.s=.o)

# Default target
all: $(TARGET).bin
	@echo "Build is done"

# Rule to build object files from C source
%.o: %.c
	$(CC)gcc -c $(CFLAGS) $(INCS) $< -o $@

# Rule to build object files from assembly source
%.o: %.s
	$(CC)as $(CFLAGS) $(INCS) $< -o $@

# Rule to build the ELF file
$(TARGET).elf: $(OBJ)
	$(CC)ld -T linker_script.ld $(LIBS) $(OBJ) -o $@ -Map=Map_file.map
	cp $(TARGET).elf $(TARGET).axf

# Rule to build the binary file
$(TARGET).bin: $(TARGET).elf
	$(CC)objcopy -O binary $< $@

# Clean rule to remove build artifacts
clean:
	rm -f *.o *.elf *.bin *.axf *.map
