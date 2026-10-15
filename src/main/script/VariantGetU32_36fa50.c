#include "types.h"

/* Same Var-dispatch family, return type u32.  Tags 5-8 (s32,u32,s64,u64)
   all fold to the identical `lw $2,0x8($4)`.  Float(tag9) is the classic
   MIPS float->uint32 no-native-instruction idiom (subtract 2^31, cvt,
   OR in the sign bit if out of int32 range) -- a plain `(u32)` cast
   should reproduce it verbatim.  Double(tag10) forwards a helper
   returning u32 directly (per the s16/s8 siblings' lever: match the
   callee's declared return type to THIS caller's). */

extern u32 DoubleToUInt_13bb78(s64);

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

u32 VariantGetU32_36fa50(struct Var *p0)
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
        return (u32)p0->u.vs64;
    case 8:
        return (u32)p0->u.vu64;
    case 9:
        return (u32)p0->u.vf32;
    case 10:
        return DoubleToUInt_13bb78(p0->u.vs64);
    case 0:
    default:
        return 0;
    }
}
