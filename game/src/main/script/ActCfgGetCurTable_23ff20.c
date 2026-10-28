/* rgp:protos */
#define RGP_SELF_ActCfgGetCurTable_23ff20 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481EFC;
extern u8 D_004BCDB0[];
extern u8 D_004BCDE0[];

s32 ActCfgGetCurTable_23ff20(void)
{
    s32 t0;

    t0 = D_00481EFC;
    if (t0 == 1) {
        return (s32)D_004BCDB0;
    }
    if (t0 == 2) {
        return (s32)D_004BCDE0;
    }
    return 0;
}
