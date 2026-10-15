#include "types.h"

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
    s32 tag;                                        /* 0x00 */
    u8 pad004[0x4];
    union Val u;                                    /* 0x08 */
    void (*get)(struct Var *, void *, s32, s32);    /* 0x10 */
    u8 pad014[0x4];
    u8 a018[0x8];                                   /* 0x18 */
    void (*set)(struct Var *, void *, s32, s32);    /* 0x20 */
    u8 pad024[0x4];
    u8 a028[0x8];                                   /* 0x28 */
};

extern s32 VariantGetS8_36fe50(struct Var *);
extern s32 VariantGetU8_36fd70(struct Var *);
extern s32 VariantGetS16_36fcc0(struct Var *);
extern s32 VariantGetU16_36fbe0(struct Var *);
extern s32 VariantGetS32_36fb30(struct Var *);
extern s32 VariantGetU32_36fa50(struct Var *);
extern s64 VariantGetS64_36f9a0(struct Var *);
extern s64 VariantGetU64_36f8f0(struct Var *);
extern f32 VariantGetFloat_36f7a0(struct Var *);
extern s64 VariantGetDouble_36f6c0(struct Var *);
extern s32 DoubleNotEqual_1002d0(s64, s64);

struct Var *VariantLogicalNot_36b2b0(struct Var *a)
{
    s32 r32;

    if (a->get != 0) {
        a->get(a, &a->a018, 0, 0);
        a->get = 0;
    }
    switch (a->tag) {
    case 1: {
        s32 x = VariantGetS8_36fe50(a);
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 2: {
        s32 x = VariantGetU8_36fd70(a);
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 3: {
        s32 x = VariantGetS16_36fcc0(a);
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 4: {
        s32 x = VariantGetU16_36fbe0(a);
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 5: {
        s32 x = VariantGetS32_36fb30(a);
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 6: {
        s32 x = VariantGetU32_36fa50(a);
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 7: {
        s64 x = VariantGetS64_36f9a0(a);
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 8: {
        s64 x = VariantGetU64_36f8f0(a);
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 9: {
        f32 x9 = VariantGetFloat_36f7a0(a);
        f32 z9 = 0.0f;
        r32 = (x9 != z9) ^ 1;
    }
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    case 10:
        r32 = DoubleNotEqual_1002d0(VariantGetDouble_36f6c0(a), 0) ^ 1;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    case 0:
        break;
    }
    return a;
}
