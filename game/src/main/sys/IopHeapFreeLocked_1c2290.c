/* rgp:protos */
#define RGP_SELF_IopHeapFreeLocked_1c2290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 WaitSema(s32);
extern s32 sceSifFreeSysMemory_11ea40(s32);
extern void SignalSema(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481514;

s32 IopHeapFreeLocked_1c2290(s32 p0)
{
    s32 t0;
    s32 r0;
    s32 r1;
    s32 t1;

    t0 = D_00481514;
    r0 = WaitSema(t0);
    r1 = sceSifFreeSysMemory_11ea40(p0);
    t1 = D_00481514;
    SignalSema(t1);
    return r1;
}
