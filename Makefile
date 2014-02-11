VPATH = src
OBJECTS = kernel.o

EFIINC = /usr/include/efi
EFIINCS = -I$(EFIINC) -I$(EFIINC)/x86_64 -I$(EFIINC)/protocol
LIB = /usr/lib64
EFILIB = /usr/lib64/gnuefi
EFI_CRT_OBJS = $(EFILIB)/crt0-efi-x86_64.o
EFI_LDS = $(EFILIB)/elf_x86_64_efi.lds

CXXFLAGS = $(EFIINCS) -fno-stack-protector -fpic -fshort-wchar -mno-red-zone \
	-Wall -Wextra -std=c++11 -ffreestanding -fno-rtti -fno-exceptions -O2
LDFLAGS = -nostdlib -znocombreloc -T $(EFI_LDS) -shared -Bsymbolic \
	-L $(EFILIB) -L $(LIB) $(EFI_CRT_OBJS)

all: simplix.efi

simplix.efi: kernel.so
	objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym \
		-j .rel -j .rela -j .reloc --target=efi-app-x86_64 $^ $@

kernel.so: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.so -lefi -lgnuefi
