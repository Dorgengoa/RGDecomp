/* rgp:protos */
#define RGP_SELF_insect_InsectBattleRosterListTextClipCb_5102f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005102F0 -- 296 bytes.  Five parameters, only the fifth read; the
 * two data handles are ARRAY symbols compared against null, which is why mwcc
 * keeps the tests instead of folding them.  D_004DB150 is a main-image .bss
 * address with no symbol in config/main.symbols.txt -- see the report. */

typedef struct Slot {
    u8  pad00[0x20];
    s32 f20;                        /* +0x20 */
} Slot;

extern u8 insect_D_00525FF0[];
extern u8 D_004DB150[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectBattleRosterListTextClipCb_5102f0(s32 a, s32 b, s32 c, s32 d, s32 mode)
{
    u8   *w1;
    s32   w;
    s32   ht;
    s32   h;
    u8   *w2;
    s32   sx;
    s32   sy;
    s32   x1;
    s32   y0;
    s32   y1;
    Slot *s;

    h = GetDrawCtx_15de80();
    w = DrawEnvGetWidth_1451e0(h);
    ht = DrawEnvGetHeight_1451d0(h);
    w1 = insect_D_00525FF0;
    if (w1 == 0) {
        return 0;
    }
    w2 = D_004DB150;
    s = ((Slot *)UiFindWidget_290460(w1, 0x7549));
    if (s == 0 || w2 == 0) {
        return 0;
    }
    if (s->f20 == 0) {
        return 0;
    }
    UiGetWidgetAbsPos_290fc0(w1, 0x7549, &sx, &sy);
    x1 = sx + 0x1C0;
    y0 = sy + 6;
    y1 = y0 + 0x8A;
    if (x1 >= w) {
        x1 = w;
    }
    if (y1 >= ht) {
        y1 = ht;
    }
    if (mode != 0) {
        TextStyleSetClipRect_26f620(w2, sx + 2, x1 - 2, y0 + 2, y1 - 2);
    } else {
        TextStyleClearClipRect_26f600(w2);
    }
    return 1;
}
