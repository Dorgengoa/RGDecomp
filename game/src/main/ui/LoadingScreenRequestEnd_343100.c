/* rgp:protos */
#define RGP_SELF_LoadingScreenRequestEnd_343100 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482D78;
extern s32 D_004E897C;

s32 LoadingScreenRequestEnd_343100(void)
{
    s32 t0;

    t0 = D_00482D78;
    if ((u32)(t0 + -3) < 2) {
        *(s32 *)&D_004E897C = 0x3F800000;
        D_00482D78 = 5;
        return 1;
    }
    return 0;
}
