/* rgp:protos */
#define RGP_SELF_FileIoUnlock_11b330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void SignalSema(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004462A4;

void FileIoUnlock_11b330(void)
{
    s32 t0;

    t0 = D_004462A4;
    SignalSema(t0);
}
