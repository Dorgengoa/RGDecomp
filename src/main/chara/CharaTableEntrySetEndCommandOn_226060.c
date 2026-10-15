#include "types.h"

typedef struct O {
    u8  pad000[0x3A];
    s16 m3A;
    s32 m3C;
    s32 m40;
} O;

void CharaTableEntrySetEndCommandOn_226060(O *o, u64 v)
{
    o->m3A = 2;
    o->m3C = (s32)v;
    o->m40 = (s32)(v >> 32);
}
