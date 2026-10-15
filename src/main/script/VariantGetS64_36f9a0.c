#include "types.h"

/* Sibling of src/wf/main/VariantGetDouble_36f6c0.c (Var -> double converter, same
   tag-dispatch idiom).  This one is Var -> s64 raw widen: integer arms
   just load-and-extend (no helper call), only the float/double arms call
   a helper.  jtbl_00463690 is 11 entries; index 0 (tag 0) points at the
   SAME body as the out-of-range default ($2 = 0), the case-0-shares-
   -default idiom from VariantGetDouble_36f6c0.

   NEEDS a .rodata slot: config/crodata.txt VariantGetS64_36f9a0 00463690 <size>
   (orchestrator to add -- read-only from this lane). */

extern s64 FloatToS64_13ade0(f32);
extern s64 DoubleToS64_13ac40(s64);

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

s64 VariantGetS64_36f9a0(struct Var *p0)
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
        return FloatToS64_13ade0(p0->u.vf32);
    case 10:
        return DoubleToS64_13ac40(p0->u.vs64);
    case 0:
    default:
        return 0;
    }
}
