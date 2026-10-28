/* rgp:protos */
#define RGP_SELF_LeaderSwitchMenuDraw_39d170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s16 D_00483620;
extern u8 D_004E9610[];

void LeaderSwitchMenuDraw_39d170(void)
{
    s16 t0;

    t0 = D_00483620;
    if (t0 != 0) {
        UiDrawWidgets_291910(D_004E9610);
    }
}
