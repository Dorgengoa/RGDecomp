#pragma opt_propagation off
#include "types.h"
extern "C" s32 *ObjRecTableGet_1c3fa0(void*,s32);
static inline s32 eq(s32 a,s32 b){return a==b;}
static inline s32 empty(s32*p){return eq(*p,0);}
extern "C" s32 ObjRecTableFindFree_1c5320(void*p){s32 i;s32*q;for(i=0;i<*(s32*)((u8*)p+0x3c58);i++){q=ObjRecTableGet_1c3fa0(p,i);if(q && empty(q))return i;}return -1;}
