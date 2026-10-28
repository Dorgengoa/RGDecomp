/* rgp:protos */
#define RGP_SELF_MenuCharaSelInputCb_341d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B2570[];

s32 MenuCharaSelInputCb_341d80(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = PadIsTriggered_1839f0(D_004B2570, 0xA000);
    if (r0 != 0) {
        r1 = MenuCycleCharaSel_341220(p0, 0);
    }
    return 1;
}
