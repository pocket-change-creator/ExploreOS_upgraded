
#include "framebuffer.hpp"
void Framebuffer::clear(uint32_t rgb){ if(!ptr) return; uint64_t total=(uint64_t)height*(pitch/4); for(uint64_t i=0;i<total;i++) ptr[i]=rgb; }
void Framebuffer::putPixel(int x,int y,uint32_t rgb){ if(!ptr) return; if(x<0||y<0||(uint32_t)x>=width||(uint32_t)y>=height) return; uint32_t* row=(uint32_t*)((uint8_t*)ptr + (uint64_t)y * pitch); row[x]=rgb; }
void Framebuffer::rect(int x,int y,int w,int h,uint32_t rgb){ for(int i=0;i<w;i++){ putPixel(x+i,y,rgb); putPixel(x+i,y+h-1,rgb);} for(int j=0;j<h;j++){ putPixel(x,y+j,rgb); putPixel(x+w-1,y+j,rgb);} }
void Framebuffer::rectFill(int x,int y,int w,int h,uint32_t rgb){ for(int j=0;j<h;j++){ uint32_t* row=(uint32_t*)((uint8_t*)ptr+(uint64_t)(y+j)*pitch); for(int i=0;i<w;i++){ int xx=x+i; if(xx<0||xx>=(int)width) continue; row[xx]=rgb; } } }
void Framebuffer::text(int x,int y,const char* s,uint32_t rgb){ for(const char* p=s;*p;++p){ unsigned char c=*p; if(c<32||c>127){ x+=font8x8::W; continue; } const uint8_t* g=font8x8::data[c-32]; for(int row=0;row<font8x8::H;++row){ uint8_t bits=g[row]; for(int col=0;col<font8x8::W;++col){ if(bits&(1<<(7-col))) putPixel(x+col,y+row,rgb); } } x+=font8x8::W; } }
void Framebuffer::cursor(int x,int y,uint32_t rgb){ for(int dy=0;dy<10;dy++){ for(int dx=0;dx<8;dx++){ if(dx==0||dy==0||dx==7||dy==9) putPixel(x+dx,y+dy,rgb); } } }
