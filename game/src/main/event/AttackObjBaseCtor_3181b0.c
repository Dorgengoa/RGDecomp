/* rgp:protos */
#define RGP_SELF_AttackObjBaseCtor_3181b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

extern u8 D_00471C20[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xB0];
    void *mB0;
    u8 pad0B4[0xCC];
    u128 m180;
    s32 m190;
};

struct Obj0 *AttackObjBaseCtor_3181b0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, f32 fa0)
{
    s32 r0;

    r0 = ((s32)JudgeObjectCtor_3145a0(p0, p1, p2, p3, fa0));
    p0->mB0 = D_00471C20;
    p0->m180 = 0;
    p0->m190 = 0;
    return p0;
}
