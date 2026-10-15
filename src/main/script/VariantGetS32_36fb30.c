#include "types.h"

/* Same Var-dispatch family as VariantGetS64_36f9a0/VariantGetDouble_36f6c0, but this one
   returns s32 (a truncating "get as int" accessor): the s64/u64 arms
   (tags 7,8) collapse to the SAME `lw` as the s32/u32 arms (tags 5,6) --
   truncating a 64-bit load to s32 folds to a 32-bit load at the same
   (little-endian) address, so all four tags emit `lw $2,0x8($4)`.
   Float (tag9) casts via cvt.w.s+mfc1; double (tag10) goes through a
   helper taking the double's raw bits in $4 (soft-double convention).
   Needs a crodata slot like its siblings: jtbl_004636F0, 11 entries. */

extern s32 dptoli(s64);

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

s32 VariantGetS32_36fb30(struct Var *p0)
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
        return (s32)p0->u.vu32;
    case 7:
        return (s32)p0->u.vs64;
    case 8:
        return (s32)p0->u.vu64;
    case 9:
        return (s32)p0->u.vf32;
    case 10:
        return dptoli(p0->u.vs64);
    case 0:
    default:
        return 0;
    }
}
