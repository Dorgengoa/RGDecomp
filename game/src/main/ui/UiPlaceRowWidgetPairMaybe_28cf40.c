/* rgp:protos */
#define RGP_SELF_UiPlaceRowWidgetPairMaybe_28cf40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Five integer parameters ($4..$8) plus a gp float constant in $f12.
   beql INTO each arm => switch, case order reversed in the chain. */

extern f32 D_0047D5D0;

/*rgp*/
/*rgp*/

void UiPlaceRowWidgetPairMaybe_28cf40(s32 mode, s32 idx, s32 p2, s32 p3, void *o)
{
    s32 base;

    if (o == 0) {
        return;
    }
    switch (mode) {
    case 0:
        base = idx * 39;
        UiSetWidgetPos_290f60(o, p2, -0x4A, base + 0x50);
        UiSetWidgetPos_290f60(o, p3, -0x47, base + 0x53);
        break;
    case 1:
        UiMoveWidgetUniform_290f50(o, p2, -0x12, 0xC, D_0047D5D0, 0);
        UiMoveWidgetUniform_290f50(o, p3, -0xF, 0xF, D_0047D5D0, 0);
        break;
    }
}
