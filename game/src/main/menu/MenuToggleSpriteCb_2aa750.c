/* rgp:protos */
#define RGP_SELF_MenuToggleSpriteCb_2aa750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482360;

s32 MenuToggleSpriteCb_2aa750(s32 p0)
{
    s32 r;

    r = MenuSetToggleSprite_2b3aa0(p0, D_00482360, 0x13E);
    return 1;
}
