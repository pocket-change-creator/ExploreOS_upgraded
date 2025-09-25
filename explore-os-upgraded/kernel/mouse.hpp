
#pragma once
#include <stdint.h>
namespace psm { void init(); bool hasPacket(); void readPacket(int &dx,int &dy,bool &left); }
