/* rgp:protos */
#define RGP_SELF_normal_FieldHudPanelSetRaised_4f5310 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F5310 -- publish one changed s16 of the p->f2BA table; the
 * readout nudges its x by +/-10 depending on whether the new value is set.
 * The two out-parameters sit at 0x4C and 0x48 of a 0x50 frame, TOP-DOWN in
 * declaration order.  0.7f is MAIN's `.lit4` pool entry at 0x0047D248. */
typedef struct N {
    u8  pad000[0x2BA];
    s16 f2BA[1];
    u8  pad2BC[0x378 - 0x2BC];
    s16 f378;
} N;

/*rgp*/
/*rgp*/

void normal_FieldHudPanelSetRaised_4f5310(N *p, s32 idx, s32 val)
{
    s32 x;
    s32 y;
    u16 id;

    if (p->f378 == 0) {
        return;
    }
    if (p->f2BA[idx] == val) {
        return;
    }
    p->f2BA[idx] = val;
    id = idx * 7 + 10;
    UiGetWidgetTargetPos_290d90(p, id, &x, &y);
    if (p->f2BA[idx] != 0) {
        x += 10;
    } else {
        x -= 10;
    }
    UiMoveWidgetUniform_290f50(p, id, *(volatile s32 *)&x, y, 0.7f, 0);
}
