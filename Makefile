VPATH = src:src/lib:src/uefi:src/font:src/framebuffer:src/descriptors
OBJECTS = kernel.o error.o string.o ctype.o math.o stdlib.o stdio.o uefi.o \
	  font.o framebuffer.o

CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -ffreestanding -fshort-wchar \
	   -fno-exceptions -fno-rtti -O2 -I src -ggdb3
LDFLAGS = -nostdlib --oformat pei-x86-64 --subsystem 10 -pie -e kmain

all: simplix.efi

simplix.efi: $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o simplix.efi	
