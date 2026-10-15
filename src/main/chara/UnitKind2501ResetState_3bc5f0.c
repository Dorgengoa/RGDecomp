#include "types.h"

/* Known-positive sibling shape of CharaKind1002ResetState_3a99a0 (byte-identical, in cunits). */

extern s32 UnitResetState_3beb60(void *);

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

s32 UnitKind2501ResetState_3bc5f0(struct Obj0 *p0)
{
    s32 r0;
    s32 rv1;

    r0 = UnitResetState_3beb60(p0);
    rv1 = 1;
    if ((r0 & 0xFF) == 0) {
        rv1 = 0;
    } else {
        p0->m08 = 0x9C5;
        rv1 = 1;
    }
    return rv1;
}
