#include "types.h"

typedef struct P { u8 pad0[0xB5C]; u32 fB5C; s16 fB60; s16 fB62; } P;

s32 CharaEvObjContactFlag2Related_2148e0(P *p)
{
    return p->fB60 >= 0 && p->fB5C != 0 && (p->fB62 & 0x2) != 0;
}
