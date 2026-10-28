/* rgp:protos */
#define RGP_SELF_UiSlideInWidgetPair_28d010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void UiSlideInWidgetPair_28d010(s32 p0, s32 p1, s32 p2)
{
    if (p2 != 0) {
        UiSetWidgetPos_290f60(p2, p0, -0x12, 0xC);
        UiSetWidgetPos_290f60(p2, p1, -0xF, 0xF);
        UiMoveWidgetUniform_290f50(p2, p0, 0x5A, 0xC, 0.25f, 0);
        UiMoveWidgetUniform_290f50(p2, p1, 0x5D, 0xF, 0.25f, 0);
        return;
    }
}
