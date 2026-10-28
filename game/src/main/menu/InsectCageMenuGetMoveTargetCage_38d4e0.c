/* rgp:protos */
#define RGP_SELF_InsectCageMenuGetMoveTargetCage_38d4e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E94E0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
};

s16 InsectCageMenuGetMoveTargetCage_38d4e0(void)
{
    struct Obj0 *r0;
    s16 t0;

    r0 = UiEntryListFindDataByTag_28ec30(D_004E94E0, 0x753A);
    t0 = r0->m10;
    return t0;
}
