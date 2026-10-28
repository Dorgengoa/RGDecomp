/* rgp:protos */
#define RGP_SELF_EventPendingPacketSet_3e2610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 memcpy(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048399C;
extern u8 D_004E9740[];

s32 EventPendingPacketSet_3e2610(s32 p0, s32 p1)
{
    s32 rv2;
    s32 t0;
    s32 rv1;
    s32 r0;

    rv2 = rv1;
    if (p0 == 0) {
        rv2 = 0;
    } else {
        t0 = D_0048399C;
        rv1 = 1;
        if (t0 != 0) {
            rv1 = 0;
        } else {
            D_0048399C = p0;
            r0 = ((s32)memcpy(D_004E9740, p1, 0x28));
            rv1 = 1;
        }
        rv2 = rv1;
    }
    return rv2;
}
