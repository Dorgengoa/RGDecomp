#include "types.h"

/* Same Var-dispatch family, return type s16 this time.  Tags 3-8
   (s16,u16,s32,u32,s64,u64) all emit the IDENTICAL `lh $2,0x8($4)` --
   truncating a load to s16 folds to a 16-bit load at the same
   little-endian address regardless of source width.  Float (tag9)
   explicit-casts to int (cvt.w.s+mfc1) then narrows via the known
   (s16)-cast dsll32/dsra32-by-16 idiom.  Double (tag10) forwards a
   helper call's s32 result directly as the s16 return with NO
   narrowing code -- an untested guess that mwcc skips return-type
   narrowing specifically for a directly-forwarded call result. */

extern s16 dptoli(s64);

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

s16 VariantGetS16_36fcc0(struct Var *p0)
{
    switch (p0->tag) {
    case 1:
        return p0->u.vs8;
    case 2:
        return p0->u.vu8;
    case 3:
        return p0->u.vs16;
    case 4:
        return (s16)p0->u.vu16;
    case 5:
        return (s16)p0->u.vs32;
    case 6:
        return (s16)p0->u.vu32;
    case 7:
        return (s16)p0->u.vs64;
    case 8:
        return (s16)p0->u.vu64;
    case 9:
        return (s16)(s32)p0->u.vf32;
    case 10:
        return dptoli(p0->u.vs64);
    case 0:
    default:
        return 0;
    }
}
