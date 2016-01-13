SRC_DIR = ./src_files
INC_DIR = ./inc_files
OBJ_DIR = ./obj_files
BIN_DIR = ./bin_files

CC = ../i386-elf/bin/i386-elf-gcc

_OBJS = kernel.o io.o malloc.o stdlib.o idt.o gdt.o main.o isr.o irq.o keyboard.o screen.o
OBJS = $(patsubst %, $(OBJ_DIR)/%, $(_OBJS))
SRCS = src_files/kernel.c src_files/io.c src_files/malloc.c src_files/stdlib.c src_files/gdt.c src_files/idt.c src_files/isr.c src_files/irq.c src_files/main.c src_files/keyboard.c src_files/screen.c
#pre merge CFLAGS <this is where I foresee most issues with compatibility appearing>
CFLAGS = -g -I$(INC_DIR) -O2 -std=gnu99 -ffreestanding -Wall -Wextra -nostdlib
#following CFLAGS are what the gdt etc compile successfully off of, here's to hoping
#CFLAGS = -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
#following is trying to combine two CFLAG statements by brute force
#CFLAGS = -g -I$(INC_DIR) -O2 -std=gnu99 -ffreestanding -Wall -Wextra -nostdlib -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
#still having issues...
# currently pops up with errors from io.h including <stdbool.h> and such


all: $(OBJS)

#$(BIN_DIR)/main.o: $(OBJS) 
#	$(CC) $^ $(CFLAGS) -o $@ 
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
dependencies:  $(SRCS)
	$(CC) -I$(INC_DIR) -MM $^ | sed '/^.*.o:/ s#^#$(OBJ_DIR)/#' > $@
	
include dependencies

clean:
	rm $(OBJ_DIR)/*.o
	rm $(BIN_DIR)/*.o
