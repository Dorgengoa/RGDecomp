#include "types.h"

typedef struct Obj_FUN_003f4360 {
    u8 pad000[0x4];
    s32 f04;
    s32 f08;
    s32 f0C;
} Obj_FUN_003f4360;

extern void WorldSubsysLinkIds_3f49c0(s32 a, s32 b);
extern void WorldSubsysLinkIds_3f4590(s32 a, s32 b);

s32 WorldSubsysLinkAll_3f4360(Obj_FUN_003f4360 *o)
{
    if (o->f08 != 0) {
        WorldSubsysLinkIds_3f49c0(o->f08, o->f04);
    }
    if (o->f08 != 0) {
        WorldSubsysLinkIds_3f4590(o->f0C, o->f04);
    }
    return 1;
}
