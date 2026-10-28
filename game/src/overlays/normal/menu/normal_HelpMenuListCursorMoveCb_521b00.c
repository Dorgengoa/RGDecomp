/* rgp:protos */
#define RGP_SELF_normal_HelpMenuListCursorMoveCb_521b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00521B00 -- the 0x2A widget bring-up: bail if the open fails, run
 * the eight-slot init pair, then the three per-selection calls.  The final
 * `3.0f + (f32)f16 * D_00484A04` is left INLINE so the scheduler keeps the
 * adda.s/madd.s contraction retail has -- naming the product would kill it. */

typedef struct Box {
    u8  pad00[0x12];
    s16 f12;
    u8  pad14[0x16 - 0x14];
    s16 f16;
} Box;

extern u8 normal_D_00528180[];

extern f32 D_00484A04;            /* gp - 0x76C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_HelpMenuListCursorMoveCb_521b00(Box *p)
{
    s32 i;

    if (((s32)UiFindWidget_290460(normal_D_00528180, 0x2A)) == 0) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        UiSetSpriteW_28fbf0(normal_D_00528180, 0x2A, 0x14F, i);
        UiSetSpriteUvW_28f850(normal_D_00528180, 0x2A, 4, i);
    }
    UiSetSpriteW_28fbf0(normal_D_00528180, 0x2A, 0, p->f12);
    UiSetSpriteUvW_28f850(normal_D_00528180, 0x2A, 0, p->f12);
    UiSetWidgetPos_290f60(normal_D_00528180, 0x29, 0x52, p->f12 * 27 + 0x70);
    normal_HelpMenuListFill_522e30(p->f16);
    UiMoveWidgetUniform_290f50(normal_D_00528180, 0x2B, 0x154, (s32)(3.0f + (f32)p->f16 * D_00484A04), 0.25f, 0
);
    return 1;
}
