
# Build for Explore OS Upgraded
TARGET    ?= x86_64-elf
CC        ?= $(TARGET)-g++
AS        ?= nasm
LD        ?= $(TARGET)-ld

CXXFLAGS  := -std=c++17 -ffreestanding -fno-exceptions -fno-rtti -O2 -Wall -Wextra -mno-red-zone -nostdlib -fno-builtin -m64
LDFLAGS   := -nostdlib -z max-page-size=0x1000

OBJDIR    := build
SRCDIR    := kernel
ISODIR    := iso
ISO       := explore-upgraded.iso

SOURCES := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

all: $(ISO)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/arch/x86_64

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/arch/x86_64/boot.o: $(SRCDIR)/arch/x86_64/boot.s | $(OBJDIR)
	$(AS) -f elf64 $< -o $@

kernel.elf: $(OBJDIR)/arch/x86_64/boot.o $(OBJS) linker.ld
	$(TARGET)-ld -T linker.ld $(LDFLAGS) $(OBJDIR)/arch/x86_64/boot.o $(OBJS) -o $@

$(ISO): kernel.elf grub/grub.cfg
	mkdir -p $(ISODIR)/boot/grub
	cp kernel.elf $(ISODIR)/boot/kernel.elf
	cp grub/grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) $(ISODIR)

run: $(ISO)
	qemu-system-x86_64 -cdrom $(ISO) -m 256 -serial stdio -display sdl -usbdevice mouse

qemu-kernel: kernel.elf
	qemu-system-x86_64 -kernel kernel.elf -m 256 -serial stdio -display sdl -usbdevice mouse

clean:
	rm -rf $(OBJDIR) kernel.elf $(ISODIR) $(ISO)

.PHONY: all clean run qemu-kernel
