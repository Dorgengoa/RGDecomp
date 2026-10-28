/* rgp:protos */
#define RGP_SELF_MenuStateTableForId_42c950 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00468550[];
extern u8 D_00468554[];

s32 MenuStateTableForId_42c950(s32 p0, s32 p1)
{
    s32 l0;
    s32 l1;
    s32 t0;

    l0 = -1;
    l1 = 0;
    while (*(s32 *)((u8 *)D_00468550 + (l1 << 3)) != l0) {
        if (p1 == *(s32 *)((u8 *)D_00468550 + (l1 << 3))) {
            t0 = *(s32 *)((u8 *)D_00468554 + (l1 << 3));
            return t0;
        }
        l1 = (l1 + 1);
    }
    return 0;
}
