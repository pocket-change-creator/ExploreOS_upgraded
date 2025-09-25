
#include "apps.hpp"
#include "vfs.hpp"
#include "util.hpp"
#include <stdio.h>
static char shell_buf[256]; static int shell_pos=0; static int shell_line=0;
static void browser_paint(Framebuffer& fb, Window& w){
    const char* page = vfs_read("index.html");
    if(page) fb.text(w.x+8, w.y+28, "Loaded: index.html", 0xFFE6EDF3);
    else fb.text(w.x+8, w.y+28, "No page found", 0xFFE6EDF3);
}
static void browser_event(int ev,int x,int y,char c){ (void)ev;(void)x;(void)y;(void)c; }
void create_browser(Window* w){ w->on_paint = [](Framebuffer& fb, Window& win){ browser_paint(fb, win); }; w->on_event = [](int ev,int x,int y,char c){ browser_event(ev,x,y,c); }; }

static void filemgr_paint(Framebuffer& fb, Window& w){
    int y = w.y + 28;
    for(int i=0;i<vfs_file_count;i++){
        fb.text(w.x+8, y + i*12, vfs_files[i].name, 0xFFE6EDF3);
    }
}
void create_filemgr(Window* w){ w->on_paint = [](Framebuffer& fb, Window& win){ filemgr_paint(fb, win); }; w->on_event = nullptr; }

static void shell_paint(Framebuffer& fb, Window& w){
    fb.text(w.x+8, w.y+28, shell_buf, 0xFFE6EDF3);
}
static void shell_event(int ev,int x,int y,char c){
    if(ev==1){
        if(c=='\n'){ shell_line++; shell_pos=0; shell_buf[0]=0; }
        else if(c=='\b'){ if(shell_pos>0){ shell_pos--; shell_buf[shell_pos]=0; } }
        else { if(shell_pos<250){ shell_buf[shell_pos++]=c; shell_buf[shell_pos]=0; } }
    }
}
void create_shell(Window* w){ w->on_paint = [](Framebuffer& fb, Window& win){ shell_paint(fb, win); }; w->on_event = [](int ev,int x,int y,char c){ shell_event(ev,x,y,c); }; }
