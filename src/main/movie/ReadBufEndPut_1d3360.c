#include "types.h"

#pragma divbyzerocheck on

typedef struct Obj_FUN_001d3360 {
    u8 pad000[0x14000];
    s32 f14000;
    s32 f14004;
    s32 f14008;
} Obj_FUN_001d3360;

s32 ReadBufEndPut_1d3360(Obj_FUN_001d3360 *o, s32 n)
{
    o->f14000 = (o->f14000 + n) % o->f14008;
    o->f14004 = o->f14004 + n;
    return n;
}
