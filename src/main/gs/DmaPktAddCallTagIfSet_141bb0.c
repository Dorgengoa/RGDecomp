#include "types.h"
typedef unsigned __int128 u128;typedef struct {u8 pad[4];u8*p;}Obj;extern u128 D_0047DE40 __attribute__((section(".sdata")));
void *DmaPktAddCallTagIfSet_141bb0(Obj*s,s32 v){if(!v)return 0;*(u128*)s->p=D_0047DE40;*(u32*)(s->p+4)=v & 0xFFFFFFF;s->p+=16;return s->p;}
