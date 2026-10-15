#include "types.h"

/* Same Var-dispatch family, return type f32.  Signed integer tags
   (1,3,5) use the plain int->float `mtc1;cvt.s.w` (tag5/s32 loads
   straight into the FPR via `lwc1` instead of `lw`+`mtc1`, the usual
   direct-memory-load optimization).  Unsigned tags (2,4,6) use the
   classic no-native-uitof "halve + OR back the low bit, cvt, double"
   trick.  s64(tag7)/u64(tag8) forward to existing library helpers
   S64ToFloat_13aa40/U64ToFloat_1003c0 (both already `f32(s64)` in src/s31a).
   f32(tag9) is a straight identity load.  f64(tag10) forwards to
   `dptofp` (double, raw bits in $4 -> f32), the mirror of the already-
   documented `fptodp` used in the sibling VariantGetDouble_36f6c0. */

extern f32 S64ToFloat_13aa40(s64);
extern f32 U64ToFloat_1003c0(s64);
extern f32 dptofp(s64);

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

f32 VariantGetFloat_36f7a0(struct Var *p0)
{
    switch (p0->tag) {
    case 1:
        return (f32)p0->u.vs8;
    case 2:
        return (f32)p0->u.vu8;
    case 3:
        return (f32)p0->u.vs16;
    case 4:
        return (f32)p0->u.vu16;
    case 5:
        return (f32)p0->u.vs32;
    case 6:
        return (f32)p0->u.vu32;
    case 7:
        return S64ToFloat_13aa40(p0->u.vs64);
    case 8:
        return U64ToFloat_1003c0(p0->u.vu64);
    case 9:
        return p0->u.vf32;
    case 10:
        return dptofp(p0->u.vs64);
    case 0:
    default:
        return 0.0f;
    }
}
