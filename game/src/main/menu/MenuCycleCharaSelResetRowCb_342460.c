/* rgp:protos */
#define RGP_SELF_MenuCycleCharaSelResetRowCb_342460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482364;

struct Obj0;

struct Obj0 {
    u8 pad000[0x1A];
    s16 m1A;
};

s32 MenuCycleCharaSelResetRowCb_342460(s32 p0)
{
    s32 t0;
    struct Obj0 *r1;

    MenuCycleCharaSel_341220(p0, 1);
    t0 = D_00482364;
    r1 = UiEntryListFindByTag_28ea40(t0, 0x19);
    r1->m1A = 0;
    return 1;
}
