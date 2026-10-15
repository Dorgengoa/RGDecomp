#include "types.h"

/* Same Var-dispatch family, return type u8.  Tags 1-8 all fold to the
   identical `lbu $2,0x8($4)` (u8 truncation of any width, including
   the SIGNED s8 field, is a plain zero-extending byte load -- the
   output type's signedness picks the load, not the source's).
   Float(tag9): the float->uint32 dance plus a trailing `andi 0xFF`.
   Double(tag10) forwards DoubleToUInt_13bb78 (same real symbol as the u32/u16
   siblings) declared u8 at this call site. */

extern u8 DoubleToUInt_13bb78(s64);

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

u8 VariantGetU8_36fd70(struct Var *p0)
{
    switch (p0->tag) {
    case 1:
        return (u8)p0->u.vs8;
    case 2:
        return p0->u.vu8;
    case 3:
        return (u8)p0->u.vs16;
    case 4:
        return (u8)p0->u.vu16;
    case 5:
        return (u8)p0->u.vs32;
    case 6:
        return (u8)p0->u.vu32;
    case 7:
        return (u8)p0->u.vs64;
    case 8:
        return (u8)p0->u.vu64;
    case 9:
        return (u8)p0->u.vf32;
    case 10:
        return DoubleToUInt_13bb78(p0->u.vs64);
    case 0:
    default:
        return 0;
    }
}
