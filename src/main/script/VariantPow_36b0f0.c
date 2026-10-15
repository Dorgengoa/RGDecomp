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

extern s32 VariantGetS32_36fb30(struct Var *);
extern u8 VariantHasValue_36e9f0(struct Var *);
extern s64 VariantGetS64_36f9a0(struct Var *);
extern s64 VariantGetDouble_36f6c0(struct Var *);
extern void VariantSetS8_36f300(struct Var *, s32, s32);
extern s64 dpmul(s64, s64);
extern s64 dpdiv(s64, s64);

struct Var *VariantPow_36b0f0(struct Var *a, struct Var *b)
{
    s32 n;
    s32 i;
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
    n = VariantGetS32_36fb30(b);
    if (n > 0) {
        if (VariantHasValue_36e9f0(a)) {
            s64 x = VariantGetS64_36f9a0(a);
            s64 r = x;
            for (i = 0; i < n; i++) r *= x;
            a->tag = 7;
            a->u.vs64 = r;
        } else {
            s64 x = VariantGetDouble_36f6c0(a);
            s64 r = x;
            for (i = 0; i < n; i++) r = dpmul(r, x);
            a->tag = 10;
            a->u.vs64 = r;
        }
    } else if (n < 0) {
        s64 x = VariantGetDouble_36f6c0(a);
        s64 r = 0x3FF0000000000000LL;
        for (i = 0; i > n; i--) r = dpdiv(r, x);
        a->tag = 10;
        a->u.vs64 = r;
    } else {
        VariantSetS8_36f300(a, 1, 1);
    }
    return a;
}
