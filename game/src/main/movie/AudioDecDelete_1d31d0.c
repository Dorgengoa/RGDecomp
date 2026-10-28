/* rgp:protos */
#define RGP_SELF_AudioDecDelete_1d31d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void sceSifFreeSysMemory_11ea40(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x44];
    s32 m44;
    u8 pad048[0x10];
    s32 m58;
};

s32 AudioDecDelete_1d31d0(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m44;
    sceSifFreeSysMemory_11ea40(t0);
    t1 = p0->m58;
    sceSifFreeSysMemory_11ea40(t1);
    return 1;
}
