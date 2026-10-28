/* rgp:protos */
#define RGP_SELF_LightStatePush_1429f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Snapshot copy.  The two 8-iteration lw/lw/sw/sw loops are 64-byte,
   4-byte-aligned struct assignments; the 6-iteration lq/lq/sq/sq loop is a
   192-byte 16-byte-aligned one; the 0x10 and 0xA0..0xD0 groups are batched
   lwc1x4/swc1x4 = one 4-float struct assignment each.
   Returns the PREVIOUS 0x36B4 slot value (still live in $2). */

typedef rg_u128 u128;

typedef struct F4 { f32 x, y, z, w; } F4;

struct B64 { s32 w[16]; };
struct B192 { u128 q[12]; };

struct Rec {
    s32 m00;          /* 0x00 */
    s32 m04;          /* 0x04 */
    u8  pad008[8];
    F4  m10;          /* 0x10 */
    struct B64 m20;   /* 0x20 */
    struct B64 m60;   /* 0x60 */
    F4  mA0;
    F4  mB0;
    F4  mC0;
    F4  mD0;
    struct B192 mE0;  /* 0xE0 */
};

struct Ctx {
    u8 pad000[0xF20];
    void *m0F20;        /* 0x0F20 */
    u8 pad0F24[0x2790];
    struct Rec *m36B4;  /* 0x36B4 */
    u8 pad36B8[4];
    s32 m36BC;          /* 0x36BC */
    s32 m36C0;          /* 0x36C0 */
};

struct Rec *LightStatePush_1429f0(struct Ctx *a, struct Rec *dst, s32 flag)
{
    struct Rec *old;
    s32 id;

    if (dst == 0) {
        return 0;
    }
    if (a->m0F20 == 0) {
        return 0;
    }
    old = a->m36B4;
    id = a->m36C0;
    a->m36C0 = id + 1;
    dst->m00 = id;
    a->m36BC = id;
    if (flag != 0) {
        dst->m00 = old->m00;
        dst->m04 = old->m04;
        dst->m10 = old->m10;
        dst->m20 = old->m20;
        dst->m60 = old->m60;
        dst->mA0 = old->mA0;
        dst->mB0 = old->mB0;
        dst->mC0 = old->mC0;
        dst->mD0 = old->mD0;
        dst->mE0 = old->mE0;
        dst->m04 = 0;
    }
    a->m36B4 = dst;
    return old;
}
