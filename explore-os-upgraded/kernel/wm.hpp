
#pragma once
#include "framebuffer.hpp"
#include <stdint.h>
struct Window {
    int x,y,w,h;
    const char* title;
    bool dragging;
    int drag_x, drag_y;
    void (*on_paint)(Framebuffer&, Window&);
    void (*on_event)(int ev, int x, int y, char c);
};
void wm_init(Framebuffer* fb);
void wm_add(Window* win);
void wm_run_once();
