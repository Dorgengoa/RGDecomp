#include "types.h"

typedef struct Obj_FUN_003f9e60 {
    u8 pad000[0x4];
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
} Obj_FUN_003f9e60;

extern void WorldSubsysLinkIds_3fae60(s32 a, s32 b);
extern void WorldSubsysLinkIds_3fa780(s32 a, s32 b);
extern void WorldSubsysLinkIds_3fa460(s32 a, s32 b);

s32 WorldSubsysLinkAll_3f9e60(Obj_FUN_003f9e60 *o)
{
    if (o->f08 != 0) {
        WorldSubsysLinkIds_3fae60(o->f08, o->f04);
    }
    if (o->f0C != 0) {
        WorldSubsysLinkIds_3fa780(o->f0C, o->f04);
    }
    if (o->f10 != 0) {
        WorldSubsysLinkIds_3fa460(o->f10, o->f04);
    }
    return 1;
}
