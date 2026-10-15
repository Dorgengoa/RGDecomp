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

extern s32 VariantPromoteTypes_36e510(struct Var *, s32, s32);
extern s8  VariantGetS8_36fe50(struct Var *);
extern u8  VariantGetU8_36fd70(struct Var *);
extern s16 VariantGetS16_36fcc0(struct Var *);
extern u16 VariantGetU16_36fbe0(struct Var *);
extern s32 VariantGetS32_36fb30(struct Var *);
extern u32 VariantGetU32_36fa50(struct Var *);
extern s64 VariantGetS64_36f9a0(struct Var *);
extern u64 VariantGetU64_36f8f0(struct Var *);
extern f32 VariantGetFloat_36f7a0(struct Var *);
extern s64 VariantGetDouble_36f6c0(struct Var *);
extern s32 DoubleNotEqual_1002d0(s64, s64);

struct Var *VariantNotEqual_36df40(struct Var *a, struct Var *b)
{
    s32 r32;

    if (a->get != 0) {
        a->get(a, &a->a018, 0, 0);
        a->get = 0;
    }
    if (b != 0) {
        if (b->get != 0) {
            b->get(b, &b->a018, 0, 0);
            b->get = 0;
        }
    }
    switch (VariantPromoteTypes_36e510(a, a->tag, b->tag)) {
    case 1: {
        s32 x = VariantGetS8_36fe50(a);
        s32 y = VariantGetS8_36fe50(b);
        r32 = x != y;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 2: {
        s32 x = VariantGetU8_36fd70(a);
        s32 y = VariantGetU8_36fd70(b);
        r32 = x != y;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 3: {
        s32 x = VariantGetS16_36fcc0(a);
        s32 y = VariantGetS16_36fcc0(b);
        r32 = x != y;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 4: {
        s32 x = VariantGetU16_36fbe0(a);
        s32 y = VariantGetU16_36fbe0(b);
        r32 = x != y;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 5: {
        s32 x = VariantGetS32_36fb30(a);
        s32 y = VariantGetS32_36fb30(b);
        r32 = x != y;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 6: {
        u32 x = VariantGetU32_36fa50(a);
        u32 y = VariantGetU32_36fa50(b);
        r32 = x != y;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 7: {
        s64 x = VariantGetS64_36f9a0(a);
        s64 y = VariantGetS64_36f9a0(b);
        r32 = x != y;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 8: {
        u64 x = VariantGetU64_36f8f0(a);
        u64 y = VariantGetU64_36f8f0(b);
        r32 = x != y;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 9: {
        f32 x = VariantGetFloat_36f7a0(a);
        f32 y = VariantGetFloat_36f7a0(b);
        r32 = x != y;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 10: {
        s64 x = VariantGetDouble_36f6c0(a);
        s64 y = VariantGetDouble_36f6c0(b);
        r32 = DoubleNotEqual_1002d0(x, y);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 0:
        break;
    }
    return a;
}
