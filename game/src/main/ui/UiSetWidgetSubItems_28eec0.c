/* rgp:protos */
#define RGP_SELF_UiSetWidgetSubItems_28eec0 1
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
    u8 pad000[0x24];
    s32 m24;
};

s32 UiSetWidgetSubItems_28eec0(s32 p0, s32 p1, s32 p2)
{
    struct Obj0 *r0;
    s32 rv1;

    r0 = UiFindWidget_290460(p0, p1);
    rv1 = 1;
    if (r0 == 0) {
        rv1 = 0;
    } else {
        r0->m24 = p2;
        rv1 = 1;
    }
    return rv1;
}
