/* rgp:protos */
#define RGP_SELF_VariantGetU16_36fbe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same Var-dispatch family, return type u16.  Tags 3-8 all fold to the
   identical `lhu $2,0x8($4)` (u16 truncation of any width is a plain
   zero-extending 16-bit load regardless of the source's declared
   signedness).  Float(tag9) is the float->uint32 dance PLUS a trailing
   `andi $2,0xFFFF` in both branches -- a plain `(u16)` cast should
   reproduce both.  Double(tag10) forwards DoubleToUInt_13bb78 (same real
   symbol as the u32 sibling VariantGetU32_36fa50) declared u16 at THIS call
   site, matching the caller's return type (no extra mask needed then,
   per the established lever). */

/*rgp*/

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

u16 VariantGetU16_36fbe0(struct Var *p0)
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
        return (u16)p0->u.vs32;
    case 6:
        return (u16)p0->u.vu32;
    case 7:
        return (u16)p0->u.vs64;
    case 8:
        return (u16)p0->u.vu64;
    case 9:
        return (u16)p0->u.vf32;
    case 10:
        return DoubleToUInt_13bb78(__builtin_bit_cast(double, (long long)(p0->u.vs64)));
    case 0:
    default:
        return 0;
    }
}
