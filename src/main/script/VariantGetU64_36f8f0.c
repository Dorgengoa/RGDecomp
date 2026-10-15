#include "types.h"

/* Byte-shape clone of already-merged VariantGetS64_36f9a0 (src/s35b/VariantGetS64_36f9a0.c),
   found via CENSUS open-vs-CLOSED signature search -- same tag-dispatch
   switch idiom, only the float/double helper callees differ
   (FloatToU64_13acb8/DoubleToU64_13ab28 instead of FloatToS64_13ade0/DoubleToS64_13ac40).

   NEEDS a .rodata slot: config/crodata.txt VariantGetU64_36f8f0 00463660 <size>
   (orchestrator to add -- read-only from this lane; jtbl_00463660 is a
   FRESH jump-table symbol distinct from the donor's jtbl_00463690). */

extern s64 FloatToU64_13acb8(f32);
extern s64 DoubleToU64_13ab28(s64);

union Val {
    s8 vs8;
    u8 vu8;
    s16 vs16;
    u16 vu16;
    s32 vs32;
    u32 vu32;
    s64 vs64;
    u64 vu64;
    f32 vf32;
};

struct Var {
    s32 tag;
    u8 pad004[0x4];
    union Val u;
};

s64 VariantGetU64_36f8f0(struct Var *p0)
{
    switch (p0->tag) {
    case 1:
        return p0->u.vs8;
    case 2:
        return p0->u.vu8;
    case 3:
        return p0->u.vs16;
    case 4:
        return p0->u.vu16;
    case 5:
        return p0->u.vs32;
    case 6:
        return p0->u.vu32;
    case 7:
        return p0->u.vs64;
    case 8:
        return p0->u.vu64;
    case 9:
        return FloatToU64_13acb8(p0->u.vf32);
    case 10:
        return DoubleToU64_13ab28(p0->u.vs64);
    case 0:
    default:
        return 0;
    }
}
