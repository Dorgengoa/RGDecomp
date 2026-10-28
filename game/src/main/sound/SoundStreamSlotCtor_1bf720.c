/* rgp:protos */
#define RGP_SELF_SoundStreamSlotCtor_1bf720 1
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
    u8 pad000[0x4];
    s16 m04;
    s16 m06;
    u8 pad008[0x4];
    s32 m0C;
    u8 pad010[0x40];
    u8 m50;
    u8 pad051[0x3];
    s32 m54;
    s32 m58;
    u8 pad05C[0x20];
    u8 m7C;
    u8 pad07D[0x3];
    s32 m80;
    s32 m84;
};

struct Obj0 *SoundStreamSlotCtor_1bf720(struct Obj0 *p0)
{
    s32 r0;

    p0->m04 = 0;
    p0->m06 = 0;
    p0->m0C = -1;
    p0->m50 = 1;
    p0->m54 = 0;
    p0->m58 = 0;
    p0->m7C = 1;
    p0->m80 = 0;
    p0->m84 = 0;
    r0 = (SoundStreamSlotInit_1be9f0(p0), (s32)0);
    return p0;
}
