/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadPanelClose_4f7ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F7BA0 -- the 004F5480 block with a leading `func_376B10(0)` and
 * a different tail.  `beqz $5` branches AWAY, so the block is the FALL-THROUGH
 * and the condition is `!= 0`; $4 is never read.
 *
 * ★ `sp1E = 0;` written BEFORE the call fills that call's delay slot, and the
 * same shape repeats for the pair of flag stores that share the constant 1
 * with the call's second argument.
 * ★ The tail guard is `c.le.s $f0, $f1` (f1 = 0.0f) with `bc1fl` branching
 * AWAY, so the body runs on `<= 0.0f` -- the guard polarity of that shape, not
 * the value-producing `> 0.0f` one.
 * ★ The inner `beql`'s delay slot carries the ELSE arm's `addiu $4, $28, K`,
 * the merge target's first instruction duplicated: a plain if/else with the
 * `!= 0` arm as the fall-through.
 */
extern u8 insmenu_D_004FA180[];
extern u8  D_00484348;      /* gp - 0xE28 */
extern u8  D_00484350;      /* gp - 0xE20 */
extern s16 D_00480464;      /* gp - 0x4D0C */
extern s16 D_004842E8;      /* gp - 0xE88 */
extern f32 D_0047D3C8;
extern f32 D_0047D460;
extern f32 D_0047D488;
extern f32 D_0047D49C;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadPanelClose_4f7ba0(s32 unused, s32 a)
{
    s16 sp1E;
    s32 h;

    if (a != 0) {
        SaveSetBusy_376b10(0);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88BA, 0.0f, D_0047D3C8, -1.0f);
        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88BA, 0xC8, 0, D_0047D460, 0);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88BC, 0.0f, D_0047D3C8, -1.0f);
        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88C1, -0x12, 0xC, D_0047D488, 0);
        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88C0, -0xF, 0xF, D_0047D488, 0);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88C1, 0.0f, D_0047D49C, -1.0f);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88C0, 0.0f, D_0047D49C, -1.0f);
        sp1E = 0;
        h = ((s32)insmenu_InsectVsGetLoadedTeam_4f9440(&sp1E));
        if (h != 0) {
            D_00484350 = 1;
            D_00480464 = 1;
            InsectVsCagePanelFillMaybe_379be0(h, 1, sp1E, D_00484348);
        }
    }
    if (UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x88BA) <= 0.0f) {
        if (D_00484350 != 0) {
            StateMachineSetState_28ede0(&D_004842E8, 0x88BD, 0);
        } else {
            StateMachineSetState_28ede0(&D_004842E8, 0x88BF, 0);
        }
    }
    return 1;
}
