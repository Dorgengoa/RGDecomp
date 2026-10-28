/* rgp:protos */
#define RGP_SELF_EventResHandlesFreeAll_26a650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482074;
extern u8 D_004BE170[];

void EventResHandlesFreeAll_26a650(void)
{
    s32 r0;
    s32 l1;
    s32 t0;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    l1 = 0;
    while (l1 < D_00482074) {
        t0 = *(s32 *)((u8 *)D_004BE170 + (l1 * 0x84));
        LoaderReleaseById_1cd340(r0, t0);
        l1 = (l1 + 1);
    }
    D_00482074 = 0;
}
