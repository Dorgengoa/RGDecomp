/* rgp:protos */
#define RGP_SELF_StringReplaceCStr_106f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strlen(s32);
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void * StringReplaceCStr_106f20(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s8 v5C[4];
    s32 r0;
    s8 t0;

    r0 = strlen(p3);
    t0 = v5C[0];
    return StringReplace_106f90(p0, p1, p2, p3, (p3 + r0), t0);
}

/* ⚠ `v5C` is read before it is written -- and so is retail's `lb $9, 0x5C($29)`,
   which has no preceding store to that slot anywhere in the function.  The
   uninitialised read is in the reference, not an artefact of this spelling;
   mwcc reports it as a warning, and the bytes match. */
