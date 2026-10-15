#include "types.h"

typedef struct Blk_FUN_0042fac0 {
    u8 pad000[0x4];
    s32 f04;
} Blk_FUN_0042fac0;

typedef struct Obj_FUN_0042fac0 {
    u8 pad000[0x408];
    s32 f408;
    s32 f40C;
    Blk_FUN_0042fac0 *f410;
    s32 f414;
    s32 f418;
    s32 f41C;
} Obj_FUN_0042fac0;

s32 CfgVmLoad_42fac0(Obj_FUN_0042fac0 *o, s32 a, s32 b)
{
    o->f408 = a;
    o->f40C = b;
    o->f410 = (Blk_FUN_0042fac0 *)o->f408;
    o->f414 = o->f408 + 0x10;
    o->f418 = o->f408 + o->f410->f04;
    o->f41C = 0;
    return 1;
}
