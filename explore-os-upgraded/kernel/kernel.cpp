
#include "multiboot.hpp"
#include "framebuffer.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "wm.hpp"
#include "apps.hpp"
#include "vfs.hpp"
#include <stdint.h>

extern "C" void kmain(uint64_t mb2_info_ptr){
    Framebuffer fb={};
    uint8_t* info = (uint8_t*)(uintptr_t)mb2_info_ptr;
    uint32_t total_size = *(uint32_t*)info;
    uint32_t off=8;
    while(off<total_size){
        mb2::tag* t = (mb2::tag*)(info+off);
        if(t->type==mb2::TAG_FRAMEBUFFER){
            auto* ft=(mb2::framebuffer*)((uint8_t*)t+8);
            fb.ptr=(uint32_t*)(uintptr_t)ft->addr; fb.pitch=ft->pitch; fb.width=ft->width; fb.height=ft->height; fb.bpp=ft->bpp;
        }
        if(t->type==mb2::TAG_END) break;
        off += (t->size +7)&~7;
    }
    if(!fb.ptr || fb.bpp!=32){ for(;;) asm volatile("hlt"); }

    const uint32_t bg=0xFF08121B, panel=0xFF16233A, textcol=0xFFE6EDF3;
    fb.clear(bg);
    fb.rectFill(0,0,fb.width,28,panel);
    fb.text(8,10,"Explore OS (upgraded)",textcol);

    // initialize drivers
    psm::init();

    // init WM and create windows
    wm_init(&fb);
    static Window w1; w1.x=80; w1.y=80; w1.w=540; w1.h=360; w1.title="Explore Browser"; create_browser(&w1); wm_add(&w1);
    static Window w2; w2.x=160; w2.y=160; w2.w=420; w2.h=260; w2.title="File Manager"; create_filemgr(&w2); wm_add(&w2);
    static Window w3; w3.x=240; w3.y=240; w3.w=420; w3.h=180; w3.title="Shell"; create_shell(&w3); wm_add(&w3);

    int mx=200,my=200; bool left=false;
    for(;;){
        // poll keyboard
        if(kbd::hasByte()){
            uint8_t sc=kbd::read();
            if(!(sc&0x80)){
                char ch=kbd::translate(sc);
                if(ch){ wm_send_key(ch); }
            }
        }
        // poll mouse
        if(psm::hasPacket()){
            int dx,dy; bool l;
            psm::readPacket(dx,dy,l);
            mx += dx; my += dy;
            if(mx<0) mx=0; if(my<0) my=0; if(mx>=(int)fb.width) mx=fb.width-1; if(my>=(int)fb.height) my=fb.height-1;
            wm_handle_mouse(mx,my,l);
        }
        // draw cycle
        wm_run_once();
    }
}
