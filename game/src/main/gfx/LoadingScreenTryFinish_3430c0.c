/* rgp:protos */
#define RGP_SELF_LoadingScreenTryFinish_3430c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482D78;
extern s32 D_004E897C;
extern s32 D_004E8988;
extern s32 D_004E8990;
extern s32 D_004E8D84;

s32 LoadingScreenTryFinish_3430c0(void)
{
    s32 t0;
    s32 t1;

    t0 = D_004E8990;
    t1 = D_004E8D84;
    if (t0 == t1) {
        *(s32 *)&D_004E897C = 0x3F800000;
        *(s32 *)&D_004E8988 = 0x3F800000;
        D_00482D78 = 7;
        return 1;
    }
    return 0;
}
