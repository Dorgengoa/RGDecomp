/* rgp:protos */
#define RGP_SELF_ViBufEndPut_1d4450 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 WaitSema(s32);
extern void SignalSema(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    u8 pad018[0x28];
    s32 m40;
    u8 pad044[0x4];
    s64 m48;
};

void ViBufEndPut_1d4450(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s64 t2;
    s64 w;
    s32 t3;

    t0 = p0->m40;
    r0 = WaitSema(t0);
    w = (s64)p1;
    t1 = p0->m14;
    p0->m14 = (t1 + p1);
    t2 = p0->m48;
    p0->m48 = (t2 + w);
    t3 = p0->m40;
    SignalSema(t3);
}
