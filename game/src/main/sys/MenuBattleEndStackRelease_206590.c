/* rgp:protos */
#define RGP_SELF_MenuBattleEndStackRelease_206590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481BDC;
extern u8 D_004BBD40[];
extern s32 D_004BBD68;

void MenuBattleEndStackRelease_206590(void)
{
    s32 t0;
    s32 r0;
    s32 t1;

    t0 = D_00481BDC;
    if (t0 != 0) {
        r0 = ((s32)GetLoaderMgr_1f59d0());
        t1 = D_004BBD68;
        HeapHandleFree_1cdae0(r0, t1);
        MemStackClear_14dff0(D_004BBD40);
        D_00481BDC = 0;
    }
}
