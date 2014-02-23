VPATH = src:src/lib:src/uefi
OBJECTS = kernel.o error.o string.o ctype.o math.o stdlib.o stdio.o uefi.o

CXX = x86_64-w64-mingw32-g++
LD = x86_64-w64-mingw32-ld

CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -ffreestanding -fshort-wchar \
	-fno-exceptions -fno-rtti -O2 -I src/include
LDFLAGS = -nostdlib --oformat pei-x86-64 --subsystem 10 -pie -e kmain

all: simplix.efi

simplix.efi: $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o simplix.efi	
