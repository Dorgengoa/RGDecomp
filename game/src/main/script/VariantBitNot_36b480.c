/* rgp:protos */
#define RGP_SELF_VariantBitNot_36b480 1
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

struct Var *VariantBitNot_36b480(struct Var *a)
{
    s32 r32;
    s64 r64;

    if (a->get != 0) {
        a->get(a, &a->a018, 0, 0);
        a->get = 0;
    }
    switch (a->tag) {
    case 1: {
        s32 x = VariantGetS8_36fe50(a);
        r32 = ~x;
        a->tag = 1;
        a->u.vs8 = r32;
        break;
    }
    case 2: {
        s32 x = VariantGetU8_36fd70(a);
        r32 = ~x;
        a->tag = 2;
        a->u.vu8 = r32;
        break;
    }
    case 3: {
        s32 x = VariantGetS16_36fcc0(a);
        r32 = ~x;
        a->tag = 3;
        a->u.vs16 = r32;
        break;
    }
    case 4: {
        s32 x = VariantGetU16_36fbe0(a);
        r32 = ~x;
        a->tag = 4;
        a->u.vu16 = r32;
        break;
    }
    case 5: {
        s32 x = VariantGetS32_36fb30(a);
        r32 = ~x;
        a->tag = 5;
        a->u.vs32 = r32;
        break;
    }
    case 6: {
        u32 x = VariantGetU32_36fa50(a);
        r32 = ~x;
        a->tag = 6;
        a->u.vu32 = r32;
        break;
    }
    case 7: {
        s64 x = VariantGetS64_36f9a0(a);
        r64 = ~x;
        a->tag = 7;
        a->u.vs64 = r64;
        break;
    }
    case 8: {
        u64 x = VariantGetU64_36f8f0(a);
        r64 = ~x;
        a->tag = 8;
        a->u.vu64 = r64;
        break;
    }
    case 9: {
        s64 x = VariantGetS64_36f9a0(a);
        r64 = ~x;
        a->tag = 7;
        a->u.vs64 = r64;
        break;
    }
    case 10: {
        s64 x = VariantGetS64_36f9a0(a);
        r64 = ~x;
        a->tag = 7;
        a->u.vs64 = r64;
        break;
    }
    case 0:
        break;
    }
    return a;
}
