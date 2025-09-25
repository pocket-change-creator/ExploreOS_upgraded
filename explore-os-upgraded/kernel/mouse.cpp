
#include "mouse.hpp"
#include "io.hpp"
static bool enabled=false;
static uint8_t phase=0;
static int packet[3];
static int idx=0;
void psm::init(){
    outb(0x64,0xA8); // enable aux device
    outb(0x64,0xD4); // write to aux
    outb(0x60,0xF4); // enable packet streaming
    enabled=true;
    phase=0; idx=0;
}
bool psm::hasPacket(){ return (inb(0x64)&1)!=0; }
void psm::readPacket(int &dx,int &dy,bool &left){
    dx=0; dy=0; left=false;
    if(!enabled) return;
    while((inb(0x64)&1)!=0){
        uint8_t v=inb(0x60);
        packet[idx++]=v;
        if(idx==3){
            idx=0;
            int x=(int8_t)packet[1]; int y=(int8_t)packet[2];
            dx=x; dy=-y; // PS/2 Y is negative for up
            left = (packet[0] & 0x1) != 0;
            return;
        }
    }
}
