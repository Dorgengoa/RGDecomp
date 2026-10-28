/* rgp:protos */
#define RGP_SELF_SaveUiHideWidget_37b460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004831D4;

void SaveUiHideWidget_37b460(s32 p0)
{
    s32 t0;

    t0 = D_004831D4;
    if (t0 != 0) {
        UiSetWidgetsVisibleById_291110(t0, p0, 0, 1);
        return;
    }
}
