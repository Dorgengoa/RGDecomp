/* rgp:protos */
#define RGP_SELF_JudgeObjectResetState_314730 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x80];
    s32 m80;
    u8 pad084[0x30];
    s16 mB4;
    s16 mB6;
    s16 mB8;
    s16 mBA;
    s16 mBC;
    s16 mBE;
    s16 mC0;
    u8 pad0C2[0x2];
    s32 mC4;
    s32 mC8;
    s32 mCC;
};

void JudgeObjectResetState_314730(struct Obj0 *p0)
{
    s32 l0;

    p0->m80 = 0x80000000;
    p0->mC4 = 0;
    p0->mC8 = 0;
    p0->mB4 = -1;
    p0->mB6 = 0;
    p0->mB8 = 0;
    p0->mBA = 0;
    p0->mBC = -1;
    p0->mBE = 0;
    p0->mC0 = 0;
    p0->mCC = 0;
    l0 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l0 << 1) + 0xD0) = 0;
        *(u8 *)((u8 *)p0 + l0 + 0x120) = 0;
        l0 = (l0 + 1);
    } while (l0 < 0x28);
}
