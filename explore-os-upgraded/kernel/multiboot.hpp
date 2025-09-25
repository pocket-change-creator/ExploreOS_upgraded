
#pragma once
#include <stdint.h>
namespace mb2 {
    struct tag { uint32_t type; uint32_t size; } __attribute__((packed));
    struct framebuffer {
        uint64_t addr; uint32_t pitch; uint32_t width; uint32_t height; uint8_t bpp; uint8_t type; uint16_t reserved;
    } __attribute__((packed));
    constexpr uint32_t TAG_FRAMEBUFFER = 8;
    constexpr uint32_t TAG_END = 0;
}
