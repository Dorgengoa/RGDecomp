#include "types.h"

/* Var COPY: dst->tag = src->tag; then copy the union payload at the
   width the tag selects (same width matrix as the other Var-family
   units, but here BOTH load and store are emitted, one pair per tag,
   with the identical `lw;b;sw`-shaped body reused for signed/unsigned
   pairs of the same width). Tag 0 copies nothing (uninitialized/void
   variant). Tag 10 (last case) falls straight through with no branch,
   an 8-byte raw copy (same idiom as the accessor family's "double
   forwards raw bits" case, but here just a copy, no helper call).
   After the copy, if p2 != 0 and dst has a callback set at +0x20, it is
   invoked as `cb(dst, (u8*)dst + 0x28, 0, 0)`. */

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

typedef struct Var Var;
typedef void (*NotifyFn)(Var *, void *, s32, s32);

struct Var {
    s32 tag;
    u8 pad004[0x4];
    union Val u;
    u8 pad010[0x20 - 0x10];
    NotifyFn cb;
    u8 pad024[0x28 - 0x24];
};

void VariantCopy_36f5e0(Var *p0, Var *p1, s32 p2)
{
    s32 tag;

    tag = p1->tag;
    p0->tag = tag;
    switch (tag) {
    case 0:
        break;
    case 1:
        p0->u.vs8 = p1->u.vs8;
        break;
    case 2:
        p0->u.vu8 = p1->u.vu8;
        break;
    case 3:
        p0->u.vs16 = p1->u.vs16;
        break;
    case 4:
        p0->u.vu16 = p1->u.vu16;
        break;
    case 5:
        p0->u.vs32 = p1->u.vs32;
        break;
    case 6:
        p0->u.vu32 = p1->u.vu32;
        break;
    case 7:
        p0->u.vs64 = p1->u.vs64;
        break;
    case 8:
        p0->u.vu64 = p1->u.vu64;
        break;
    case 9:
        p0->u.vf32 = p1->u.vf32;
        break;
    case 10:
        p0->u.vs64 = p1->u.vs64;
        break;
    }
    if (p2 != 0) {
        if (p0->cb != 0) {
            p0->cb(p0, (u8 *)p0 + 0x28, 0, 0);
        }
    }
}
