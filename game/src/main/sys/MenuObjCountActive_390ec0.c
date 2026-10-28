/* rgp:protos */
#define RGP_SELF_MenuObjCountActive_390ec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004832AC;

s32 MenuObjCountActive_390ec0(void)
{
    s32 t0;
    s32 l0;
    s32 l1;
    s8 t1;
    s32 rv2;

    t0 = D_004832AC;
    l0 = 0;
    l1 = 0;
    do {
        t1 = *(s8 *)((u8 *)t0 + (l1 * 0x9D0) + 0x985);
        rv2 = l0;
        if (t1 != 0) {
            rv2 = (l0 + 1);
        }
        l0 = rv2;
        l1 = (l1 + 1);
    } while (l1 < 5);
    return l0;
}
