VPATH = src
OBJECTS = kernel.o
CXX=x86_64-w64-mingw32-g++
LD=x86_64-w64-mingw32-ld

CXXFLAGS = -Wall -Wextra -std=c++11 -ffreestanding -fno-rtti -fno-exceptions -O2
LDFLAGS = -nostdlib --oformat pei-x86-64 --subsystem 10 -pie -e kmain

all: simplix.efi

simplix.efi: $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o simplix.efi	
