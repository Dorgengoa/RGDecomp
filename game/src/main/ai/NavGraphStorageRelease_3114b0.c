/* rgp:protos */
#define RGP_SELF_NavGraphStorageRelease_3114b0 1
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
    u8 pad000[0x10];
    s32 m10;
    u8 m14;
    u8 pad015[0x3];
    s16 m18;
    s16 m1A;
    s32 m1C;
    s32 m20;
    u8 m24;
    u8 pad025[0x3];
    s16 m28;
    s16 m2A;
    s32 m2C;
    s32 m30;
    u8 m34;
    u8 pad035[0x3];
    s16 m38;
    s16 m3A;
    s32 m3C;
    s32 m40;
    u8 m44;
    u8 pad045[0x3];
    s16 m48;
    s16 m4A;
    s32 m4C;
};

void NavGraphStorageRelease_3114b0(struct Obj0 *p0)
{
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1A = 0;
    p0->m1C = 0;
    p0->m20 = 0;
    p0->m24 = 0;
    p0->m28 = 0;
    p0->m2A = 0;
    p0->m2C = 0;
    p0->m30 = 0;
    p0->m34 = 0;
    p0->m38 = 0;
    p0->m3A = 0;
    p0->m3C = 0;
    p0->m40 = 0;
    p0->m44 = 0;
    p0->m48 = 0;
    p0->m4A = 0;
    p0->m4C = 0;
    HeapBlockRefRelease_42e250(p0);
}
