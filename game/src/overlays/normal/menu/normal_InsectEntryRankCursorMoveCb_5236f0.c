/* rgp:protos */
#define RGP_SELF_normal_InsectEntryRankCursorMoveCb_5236f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005236F0 -- three readouts on one row, whose y is nudged by
 * `5 - D_004807C4` clamped at zero. */
typedef struct Ret {
    u8    pad000[0x20];
    void *f20;
} Ret;

typedef struct N {
    u8  pad000[0x12];
    s16 f12;
} N;

extern s32 D_004807C4;            /* gp - 0x49AC */
extern u8  normal_D_00528180[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_InsectEntryRankCursorMoveCb_5236f0(N *p)
{
    Ret *r;
    s32  n;

    r = ((Ret *)UiFindWidget_290460(normal_D_00528180, 3));
    if (r == NULL) {
        return 0;
    }
    if (r->f20 == NULL) {
        return 0;
    }
    UiLayoutWindowFrame_28b8e0(r->f20, 0xFA, 0xAA, 6);
    n = 5 - D_004807C4;
    if (n < 0) {
        n = 0;
    }
    UiSetSpriteW_28fbf0(normal_D_00528180, 3, 0, p->f12 + 4 + n);
    UiSetSpriteUvW_28f850(normal_D_00528180, 3, 0, p->f12 + 4 + n);
    UiSetWidgetPos_290f60(normal_D_00528180, 2, 0x84, (p->f12 + n) * 27 + 0x78);
    return 1;
}
