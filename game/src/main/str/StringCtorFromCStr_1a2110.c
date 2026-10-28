/* rgp:protos */
#define RGP_SELF_StringCtorFromCStr_1a2110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strlen(s32);
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 StringCtorFromCStr_1a2110(s32 p0, s32 p1)
{
    s8 v4C[4];
    s32 l0;
    s32 r1;
    s8 t0;

    l0 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l0 << 2)) = 0;
        l0 = (l0 + 1);
    } while ((u32)l0 < 3);
    r1 = strlen(p1);
    StringReserve_107e80(p0, r1);
    t0 = v4C[0];
    StringReplace_106f90(p0, 0, 0, p1, (p1 + r1), t0);
    return p0;
}
