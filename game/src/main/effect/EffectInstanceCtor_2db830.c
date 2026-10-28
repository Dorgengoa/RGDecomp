/* rgp:protos */
#define RGP_SELF_EffectInstanceCtor_2db830 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004716F0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
    s16 m04;
    s16 m06;
    s32 m08;
    s32 m0C;
    u8 pad010[0x4];
    s32 m14;
    s32 m18;
    s32 m1C;
    s16 m20;
    u8 pad022[0xA];
    s32 m2C;
    u8 pad030[0x140];
    u8 m170;
    u8 pad171[0x1F];
    void *m190;
};

struct Obj0 *EffectInstanceCtor_2db830(struct Obj0 *p0)
{
    s32 l0;

    p0->m190 = D_004716F0;
    p0->m2C = 0;
    p0->m0C = -1;
    p0->m04 = -1;
    p0->m08 = -1;
    p0->m02 = -1;
    p0->m06 = 1;
    p0->m14 = 0;
    p0->m18 = -1;
    p0->m170 = 0;
    l0 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l0 << 2) + 0xF0) = 0;
        *(s32 *)((u8 *)p0 + (l0 << 2) + 0x130) = 0;
        l0 = (l0 + 1);
    } while (l0 < 4);
    p0->m1C = 0;
    p0->m20 = 0;
    return p0;
}
