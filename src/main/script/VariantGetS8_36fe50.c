#include "types.h"

/* Same Var-dispatch family, return type s8 this time.  Tags 1-8 all
   fold to the identical `lb $2,0x8($4)`.  Float narrows via the (s8)
   dsll32/dsra32-by-24 idiom.  Double forwards dptoli directly;
   per the s16 sibling's lever, declare the callee s8 at THIS call site
   to avoid a spurious narrowing word. */

extern s8 dptoli(s64);

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

s8 VariantGetS8_36fe50(struct Var *p0)
{
    switch (p0->tag) {
    case 1:
        return p0->u.vs8;
    case 2:
        return (s8)p0->u.vu8;
    case 3:
        return (s8)p0->u.vs16;
    case 4:
        return (s8)p0->u.vu16;
    case 5:
        return (s8)p0->u.vs32;
    case 6:
        return (s8)p0->u.vu32;
    case 7:
        return (s8)p0->u.vs64;
    case 8:
        return (s8)p0->u.vu64;
    case 9:
        return (s8)(s32)p0->u.vf32;
    case 10:
        return dptoli(p0->u.vs64);
    case 0:
    default:
        return 0;
    }
}
