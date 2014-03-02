VPATH = src:src/lib:src/uefi:src/font:src/framebuffer
OBJECTS = kernel.o error.o string.o ctype.o math.o stdlib.o stdio.o uefi.o \
	  font.o framebuffer.o

CC = x86_64-w64-mingw32-gcc
LD = x86_64-w64-mingw32-ld

CFLAGS = -Wall -Wextra -Werror -std=c11 -ffreestanding -fshort-wchar \
	 -O2 -I src
LDFLAGS = -nostdlib --oformat pei-x86-64 --subsystem 10 -pie -e kmain

all: simplix.efi

simplix.efi: $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o simplix.efi	
