
SECTION .multiboot
align 8
MB2_HEADER_MAGIC      equ 0xE85250D6
MB2_ARCH_X86_64       equ 0
MB2_HEADER_LENGTH     equ header_end - header_start
MB2_CHECKSUM          equ -(MB2_HEADER_MAGIC + MB2_ARCH_X86_64 + MB2_HEADER_LENGTH)

header_start:
    dd MB2_HEADER_MAGIC
    dd MB2_ARCH_X86_64
    dd MB2_HEADER_LENGTH
    dd MB2_CHECKSUM

    dw 0
    dw 0
    dd 8
header_end:

SECTION .text
global _start
extern kmain

_start:
    mov rdi, rbx
    call kmain
.hang:
    cli
    hlt
    jmp .hang
