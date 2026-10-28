/* rgp:protos */
#define RGP_SELF_MenuReadBufRelease_206410 1
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

extern s32 D_00481BEC;
extern u8 D_004BBE60[];
extern s32 D_004BBE88;

void MenuReadBufRelease_206410(void)
{
    s32 t0;
    s32 r0;
    s32 t1;

    t0 = D_00481BEC;
    if (t0 != 0) {
        r0 = ((s32)GetLoaderMgr_1f59d0());
        t1 = D_004BBE88;
        HeapHandleFree_1cdae0(r0, t1);
        MemStackClear_14dff0(D_004BBE60);
        D_00481BEC = 0;
    }
}
