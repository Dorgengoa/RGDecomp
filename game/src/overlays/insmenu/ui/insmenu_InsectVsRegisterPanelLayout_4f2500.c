/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegisterPanelLayout_4f2500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F2500 -- build the equipment panel.  96 instructions, 15 calls,
 * ONE loop with a nested guard.
 *
 * ★ `slti $1, $16, 0x4` lands in $at and that is the DEFAULT polarity of the
 * $at class ([[at-compare-class]]): the consumer is `beql`, i.e. the branch is
 * taken on `>=`, so the natural `if (i < 4)` spelling already gives $at and
 * there is nothing to steer.  The latch's `slti $2, $16, 0x5` feeding `bnel`
 * is the mirror -- a strict `<` continue-condition, which is a GPR -- so
 * `for (i = 0; i < 5; i++)` is right and `i <= 4` would move it to $at.
 *
 * ★ The `beql` delay slot carries `addiu $16, $16, 0x1`, the loop increment,
 * which is the MERGE's first instruction duplicated -- a plain forward branch
 * around the guarded call, not a case body.
 *
 * ★ D_004842FC is re-read at the top of every iteration (it fills the latch's
 * delay slot); that falls out of the plain global read across a call boundary.
 */

extern u8 insmenu_D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsRegisterPanelLayout_4f2500(void)
{
    void *w;
    const void *t;
    s32 i;

    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x17, 0x2B, 4.0f);
    w = UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x17, 0);
    UiLayoutFrameRectsMaybe_28bbb0(w, 0xFA, 0x2B);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x15, 0x26, 0x50);
    w = UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x3C, 0);
    UiLayoutFrameRectsMaybe_28bbb0(w, 0x7D, 0x2B);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x3C, 0, 0xAC);
    UiSetWidgetVisible_290010(insmenu_D_004FA180, 0x15, 1, -1);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x15, 0.0f);

    for (i = 0; i < 5; i++) {
        t = MsgTableLookup_28aa30(D_004842FC, i + 0xF);
        UiSetTextString_28f510(insmenu_D_004FA180, 0x3D, t, i);
        if (i < 4) {
            UiSetTextX_28f590(insmenu_D_004FA180, 0x3D, 0x27, i);
        }
    }

    UiSetSpriteSize_28fc30(insmenu_D_004FA180, 0x16, 0xEE, 0x1F, 0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x16, 0, 0);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x16, 0.0f);
}
