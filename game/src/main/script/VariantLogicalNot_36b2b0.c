/* rgp:protos */
#define RGP_SELF_VariantLogicalNot_36b2b0 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Var *VariantLogicalNot_36b2b0(struct Var *a)
{
    s32 r32;

    if (a->get != 0) {
        a->get(a, &a->a018, 0, 0);
        a->get = 0;
    }
    switch (a->tag) {
    case 1: {
        s32 x = ((signed char)VariantGetS8_36fe50(a));
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 2: {
        s32 x = ((unsigned char)VariantGetU8_36fd70(a));
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 3: {
        s32 x = ((short)VariantGetS16_36fcc0(a));
        r32 = !(x != 0);
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 4: {
        s32 x = ((unsigned short)VariantGetU16_36fbe0(a));
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
        r32 = ((unsigned char)DoubleNotEqual_1002d0(__builtin_bit_cast(double, (long long)(VariantGetDouble_36f6c0(a))), __builtin_bit_cast(double, (long long)(0)))) ^ 1;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    case 0:
        break;
    }
    return a;
}
