/* rgp:protos */
#define RGP_SELF_FileIoLock_11b300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void FioSemaCreate_11b2a8(void);
extern void WaitSema(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004462A4;

s32 FileIoLock_11b300(void)
{
    s32 t0;

    FioSemaCreate_11b2a8();
    t0 = D_004462A4;
    WaitSema(t0);
    return 0;
}
