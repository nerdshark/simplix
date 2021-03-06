simplix
=======

A simple x86-64 UEFI operating system written in C++11.

Simplix is an UEFI application. That means that we have to use some implementation of the UEFI API as specified by the
UEFI specification.  
Currently, two popular implementations exist: Intel's reference implementation called 'TianoCore', and gnu-efi.  
TianoCore is a massive UEFI environment and cross-platform. Sadly, it's also a bitch to set up, and the current
stable release doesn't have support for GCC newer than 4.6. Additionally, it's not available in the package repositories of any major Linux distribution.  
In constrast to that, gnu-efi is available in all major distros. However, UEFI functions have to be called through a weird type-unsafe wrapper to ensure ABI correctness (SysV AMD64 and Microsoft x64). Furthermore, the UEFI application is created by converting an ELF shared library to a PE/COFF executable, where it would make much more sense to simply directly compile it as a PE/COFF file.

Considering all that, I thought it would be easier to just implement the UEFI interfaces (mostly a bunch of typedefs) myself. That also means that simplix got no dependencies except on a MinGW gcc/ld, but more of that below.  


### How to Build
The following assumes a x86-64/AMD64 Linux distribution.  
The only thing required is a working MinGW x86-64 g++ and linker.  
If you're on Ubuntu, run:  
`sudo apt-get install mingw-w64`  
If you're on Fedora, run:  
`sudo yum install mingw64-gcc-c++`  
Then, assuming you're in the cloned directory, just do 'make' and a UEFI application called 'simplix.efi' should be in the directory.  

### How to Test
Assuming you already build simplix, the only requirements for testing are a working qemu installation and a copy of OVMF UEFI firmware.  
If you're on Ubuntu, you can get it by running:  
`sudo apt-get install ovmf`  
The firmware will be installed to "/usr/share/ovmf/OVMF.fd".  
For any other distribution, download it from here: http://sourceforge.net/apps/mediawiki/tianocore/index.php?title=OVMF.  
So, how to actually run simplix in qemu? Simply run the following commands:  
`qemu-img create disk 512M # Create a 512MB virtual disk.`  
`gdisk disk # Create 1 partition with filesystem code 'ef00'`  
`mkfs.vfat -F32 disk`   
`sudo mount disk /mnt`  
`sudo mkdir /mnt/EFI`  
`sudo mkdir /mnt/EFI/BOOT`  
`sudo cp simplix.efi /mnt/EFI/BOOT/BOOTx64.EFI`  
`sudo umount /mnt`  

Then start qemu with:  
`qemu-system-x86-64 -bios <path-to-OVMF.fd> -cdrom disk`
