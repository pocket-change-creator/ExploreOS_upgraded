
#pragma once
#include <stdint.h>
#include <stddef.h>
static inline size_t strlen_(const char* s){ size_t n=0; while(s[n]) ++n; return n; }
static inline void memcpy_(void* d,const void* s,size_t n){ auto dst=(uint8_t*)d; auto src=(const uint8_t*)s; for(size_t i=0;i<n;i++) dst[i]=src[i]; }
static inline void memset_(void* d,uint8_t v,size_t n){ auto dst=(uint8_t*)d; for(size_t i=0;i<n;i++) dst[i]=v; }
