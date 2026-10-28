/* rgp:protos */
#define RGP_SELF_CharaAimCtrlUpdate_1d81b0 1
#define RGP_SELF_clr 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: m2c draft has 2 M2C_ERROR sites (adda.s/madd.s accumulator,
 * ps2-float-accumulator lever applies) plus several s128 (quadword struct
 * copy) locals; 0 round trips spent this session -- needs the accumulator
 * operands read off asm/matchings/main/CharaAimCtrlUpdate_1d81b0.s and the s128 locals
 * turned into a 4-word struct (see EvTargetCarryPosMaybe_3527f0.c in this lane for the
 * Quad/{u32 w[4]} pattern that compiles). Not attempted further. */
/* s49m: 16-bad */
#include "types.h"

typedef rg_u128 u128;
typedef struct { f32 x, y, z, w; } V4;
typedef struct { V4 r[4]; } M4;

typedef struct Obj {
    V4 q;
    s16 unk10;
    s16 unk12;
    u8 pad14[4];
    u8 *unk18;
    s32 unk1C;
    f32 unk20;
} Obj;

extern f32 D_0047D1F4;
extern f32 D_0047D278;
extern f32 D_0047D1E8;
extern f32 D_0047D32C;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline void clr(u8 *p, s32 n)
{
    if (p != NULL) {
        do {
            *p++ = 0;
        } while (--n != 0);
    }
}

void CharaAimCtrlUpdate_1d81b0(Obj *o)
{
    M4 a __attribute__((aligned(16)));
    M4 b __attribute__((aligned(16)));
    V4 q __attribute__((aligned(16)));
    f32 t;
    u8 *p;
    s32 n;

    if (o->unk18 == NULL) {
        return;
    }
    if (o->unk1C == 0) {
        return;
    }
    if (o->unk10 == 0) {
        return;
    }
    *(u128 *)&q = *(u128 *)&o->q;
    ((u128 *)&a)[0] = ((u128 *)(o->unk18 + 0x60))[0];
    ((u128 *)&a)[1] = ((u128 *)(o->unk18 + 0x60))[1];
    ((u128 *)&a)[2] = ((u128 *)(o->unk18 + 0x60))[2];
    ((u128 *)&a)[3] = ((u128 *)(o->unk18 + 0x60))[3];
    FrameAimAxisAt_1d8070(o->unk18, &q, o->unk12, o->unk1C);
    ((u128 *)&b)[0] = ((u128 *)(o->unk18 + 0x60))[0];
    ((u128 *)&b)[1] = ((u128 *)(o->unk18 + 0x60))[1];
    ((u128 *)&b)[2] = ((u128 *)(o->unk18 + 0x60))[2];
    ((u128 *)&b)[3] = ((u128 *)(o->unk18 + 0x60))[3];
    {
    u8 z[16] __attribute__((aligned(16))) = {0};
    t = 0.0f;
    AxisAngleBetweenVecs_1d7da0(z, &t, &a.r[o->unk12], &b.r[o->unk12]);
    if (t == 0.0f) {
        return;
    }
    if (D_0047D1F4 < t) {
        o->unk20 = o->unk20 * D_0047D278;
    } else {
        o->unk20 = o->unk20 + D_0047D1E8 * (1.0f - o->unk20);
    }
    if (D_0047D32C < t) {
        t = D_0047D32C;
    }
    t = t * o->unk20;
    VecRotateAxisPair_1d78a0(&b, &a, z, t);
    ModelFrameSetMatrix_14a190(o->unk18, &b);
    }
}
