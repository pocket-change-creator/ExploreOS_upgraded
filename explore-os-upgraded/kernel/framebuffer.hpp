
#pragma once
#include <stdint.h>
#include "font8x8.hpp"
struct Framebuffer {
    uint32_t* ptr; uint32_t width; uint32_t height; uint32_t pitch; uint8_t bpp;
    void clear(uint32_t rgb);
    void putPixel(int x,int y,uint32_t rgb);
    void rect(int x,int y,int w,int h,uint32_t rgb);
    void rectFill(int x,int y,int w,int h,uint32_t rgb);
    void text(int x,int y,const char* s,uint32_t rgb);
    void cursor(int x,int y,uint32_t rgb);
};
