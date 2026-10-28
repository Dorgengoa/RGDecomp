/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSourceChoiceOpen_4f8800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F8800 -- `beqz $5` branches AWAY, so the block is the
 * FALL-THROUGH and the condition is `!= 0`; $4 is never read.
 *
 * ★ The tail guard is `c.lt.s $f0, $f1` (f1 = 1.0f) with `bc1tl` branching
 * AWAY, which is `>= 1.0f` -- MIPS has no `c.ge.s`.
 * ★ `daddu $7, $6, $0` after `addiu $6, $0, 0x1` is mwcc SHARING a constant it
 * already materialised, not a computed argument: write both literals.
 * ★ `sll $2, $3, 5 / subu $7, $2, $3` is `x * 31`.
 * ★ `D_0048436C = 0;` written BEFORE the first call fills its delay slot.
 */
typedef struct {
    u8  pad00[0x16];
    s16 field16;
} Ent;

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern s16 D_0048436C;      /* gp - 0xE04 */
extern s16 D_004842E8;      /* gp - 0xE88 */
extern f32 D_0047D460;

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
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsSourceChoiceOpen_4f8800(s32 unused, s32 a)
{
    void *w;
    const void *t;
    Ent *e;

    if (a != 0) {
        D_0048436C = 0;
        w = UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x5C, 0);
        UiLayoutWindowFrame_28b8e0(w, 0xF0, 0x46, 2);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x5C, 1, 1);
        UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x5C, 0.0f);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x5C, 1.0f, D_0047D460, -1.0f);
        UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x5E, 0.0f);
        t = MsgTableLookup_28aa30(insmenu_InsectVsGetMsgTable_4f3320(), 0x578);
        UiSetTextString_28f510(insmenu_D_004FA180, 0x5C, t, 0);
        t = MsgTableLookup_28aa30(insmenu_InsectVsGetMsgTable_4f3320(), 0x579);
        UiSetTextString_28f510(insmenu_D_004FA180, 0x5C, t, 1);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x5C, 0x88, 0xBE);
        e = ((Ent *)UiEntryListFindByTag_28ea40(insmenu_D_004FA1A0, 0x88C2));
        if (e != 0) {
            UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x5D, 0, e->field16 * 31);
        }
    }
    if (UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x5C) >= 1.0f) {
        StateMachineSetState_28ede0(&D_004842E8, 0x88C7, 0);
    }
    return 1;
}
