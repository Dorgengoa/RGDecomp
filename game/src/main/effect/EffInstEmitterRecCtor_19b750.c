/* rgp:protos */
#define RGP_SELF_EffInstEmitterRecCtor_19b750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    u8 pad010[0xA0];
    s32 mB0;
    s32 mB4;
    u8 pad0B8[0x8];
    s32 mC0;
    s32 mC4;
    s32 mC8;
    u8 pad0CC[0x34];
    s32 m100;
    s32 m104;
    s32 m108;
    s32 m10C;
};

struct Obj0 *EffInstEmitterRecCtor_19b750(struct Obj0 *p0)
{
    s32 r0;

    p0->m04 = 0;
    p0->m00 = 0;
    p0->m0C = 0;
    p0->mB0 = -1;
    r0 = (XformPairInit_19a240(p0), (s32)0);
    p0->m08 = 0;
    p0->mB4 = 0;
    p0->mC8 = 0;
    p0->mC0 = 0;
    p0->m100 = 0;
    p0->m104 = 0;
    p0->m108 = 0;
    p0->m10C = 0;
    p0->mC4 = 0;
    return p0;
}
