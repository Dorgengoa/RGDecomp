#include "types.h"

extern s32 ArenaAllocAligned_370330(void *, s32, s32, s32);
extern void memset(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x7A];
    u8 m7A;
    u8 pad07B[0x5];
    s16 m80;
    u16 m82;
};

s32 DataTableAllocIndex_368640(struct Obj0 *p0)
{
    u8 t0;
    u16 t1;
    s16 t2;
    s32 r0;
    s32 rv2;
    u16 t3;

    t0 = p0->m7A;
    if ((((u64)(((s64)t0) << 0x3D)) >> 0x3F) == 0) {
        return 0;
    }
    t1 = p0->m82;
    t2 = p0->m80;
    r0 = ArenaAllocAligned_370330((struct Obj0 *)((u8 *)p0 + 0x6C), (t1 << 2), t2, -1);
    if (r0 == 0) {
        return 0;
    }
    t3 = p0->m82;
    memset(r0, 0, (t3 << 2));
    return r0;
}
