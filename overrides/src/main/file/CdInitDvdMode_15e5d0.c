/* rg-override: replaces game/src/main/file/CdInitDvdMode_15e5d0.c sha256 60a0c438a2fb6d1b38ee536e6c642a52d238b08234639e1d93bfd5ee973bfb29
 * why: native files (docs/NATIVE-FS.md, PLAN.md D9): no drive to initialise (sceCdInit) or set
 *      to DVD media (sceCdMmode); the runtime mounts data/ before the game starts. */
/* rgp:protos */
#define RGP_SELF_CdInitDvdMode_15e5d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"


/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CdInitDvdMode_15e5d0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    /* rg-override: was sceCdInit_12a008(0, p1, p2, p3); sceCdMmode_12ada0(2); */
    (void)p0, (void)p1, (void)p2, (void)p3;
}
