
#include "wm.hpp"
#include "util.hpp"
#include "vfs.hpp"
#include <stddef.h>
static Framebuffer* gfb = nullptr;
static Window* windows[8]; static int win_count=0;
static int mouse_x=200, mouse_y=200; static bool mouse_left=false;
void wm_init(Framebuffer* fb){ gfb = fb; }
void wm_add(Window* win){ if(win_count<8) windows[win_count++]=win; }
static void draw_titlebar(Window* w){
    gfb->rectFill(w->x, w->y, w->w, 20, 0xFF0F2649);
    gfb->text(w->x+6, w->y+4, w->title, 0xFFFFFFFF);
    gfb->rect(w->x, w->y, w->w, w->h, 0xFF1F6FEB);
}
void wm_run_once(){
    // clear desktop background a bit (leave top bar)
    // draw windows in order
    for(int i=0;i<win_count;i++){
        Window* w = windows[i];
        // window body
        gfb->rectFill(w->x, w->y+20, w->w, w->h-20, 0xFF0E1A2F);
        draw_titlebar(w);
        if(w->on_paint) w->on_paint(*gfb, *w);
    }
    // draw mouse cursor
    gfb->cursor(mouse_x, mouse_y, 0xFFFFFFFF);
}
// Simple event dispatch - mouse coords and clicks should be set externally via globals
void wm_handle_mouse(int mx,int my,bool left){
    mouse_x = mx; mouse_y = my;
    // dispatch to topmost window under cursor
    for(int i=win_count-1;i>=0;i--){
        Window* w = windows[i];
        if(mx >= w->x && mx < w->x + w->w && my >= w->y && my < w->y + w->h){
            // title bar drag
            if(left && my < w->y + 20){
                w->dragging = true;
                w->drag_x = mx - w->x; w->drag_y = my - w->y;
                // bring to front
                for(int j=i;j<win_count-1;j++) windows[j]=windows[j+1];
                windows[win_count-1]=w;
                return;
            } else if(!left){
                w->dragging = false;
            }
            if(w->dragging){
                w->x = mx - w->drag_x;
                w->y = my - w->drag_y;
            }
            return;
        }
    }
}
void wm_send_key(char c){
    // send to focused window (topmost)
    if(win_count>0 && windows[win_count-1]->on_event) windows[win_count-1]->on_event(1, 0,0, c);
}
