/* rgp:protos */
#define RGP_SELF_UiSetSpriteX_28fcd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

struct Obj0 *UiSetSpriteX_28fcd0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    struct Obj0 *r0;

    r0 = UiGetWidgetSprite_28fe10(p0, p1, p3);
    if (r0 != 0) {
        if (p2 != -0x270F) {
            r0->m00 = p2;
        }
    }
    return r0;
}
