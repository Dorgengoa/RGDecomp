/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuStateCtrlSetStep_4eabb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EABB0 (508 bytes, 127 instructions, 16 calls) -- the map-view
 * confirm handler.  ⚠ The flag is `$5`, the SECOND parameter; the first is
 * never read.
 *
 * The three-way dispatch is an if/else CHAIN, not a switch: the case bodies
 * come out in the same order as the tests.
 *
 * ★ `D_00484314` is declared WITH A SIZE.  Without one the two indexed accesses
 * come out as `lui`/`addiu` of an absolute address instead of one gp-relative
 * `addiu $2, $28, -0xE5C`, two words each.
 * ★ Guard polarity in the toggle: the one-store arm (`= 0`) is retail's BRANCH
 * TARGET, carried in a `bnel` delay slot, so it is the `else`.  Written the
 * other way round it costs two words.
 * ★ The `func_28EA40(...)->field14 = 1` store is SPLIT from its call, or mwcc
 * materialises the stored 1 before the call and has to spend a callee-saved
 * register on it instead of reusing the compare's `$3`.
 */

typedef struct Panel Panel;
struct Panel {
    u8  pad00[0x12];
    s16 field12;
};

typedef struct Slot Slot;
struct Slot {
    u8  pad00[0x14];
    s16 field14;
};

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];

extern u8  D_004842E8;      /* gp - 0xE88, passed by address */
extern u8  D_00484304;      /* gp - 0xE6C */
extern u8  D_00484314[2];   /* gp - 0xE5C */
extern f32 D_0047D488;      /* gp - 0x7CE8 */
extern f32 D_0047D49C;      /* gp - 0x7CD4 */

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

s32 insmenu_InsectVsMenuStateCtrlSetStep_4eabb0(s32 p1, s32 open)
{
    Panel *pan;
    Slot *slot;
    s32 mode;

    if (open != 0) {
        UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x7533, 0);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0xF, 1.0f, D_0047D488, -1.0f);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0xE, 1.0f, D_0047D488, -1.0f);
    }
    D_00484304 = 0;
    mode = MenuGridCursorInputPad2_28e100(insmenu_D_004FA1A0, D_004B2570, D_004B27E0, 4);
    pan = ((Panel *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0));
    if (mode == 1) {
        D_00484304 = 1;
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0xF, 0.0f, D_0047D49C, -1.0f);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0xE, 0.0f, D_0047D49C, -1.0f);
        insmenu_InsectVsConfirmDialogOpen_4ee7c0(0xA);
    } else if (mode == 2) {
        D_00484304 = 1;
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0xA, 0.0f, D_0047D49C, -1.0f);
        StateMachineSetState_28ede0(&D_004842E8, 0x7539, 0);
        slot = ((Slot *)UiEntryListFindByTag_28ea40(insmenu_D_004FA1A0, 0x7532));
        slot->field14 = 1;
    } else {
        if ((PadIsTriggered_1839f0(D_004B2570, 0xA000) != 0) ||
            ((((unsigned char)IsPad2Enabled_2882c0()) != 0) && (PadIsTriggered_1839f0(D_004B27E0, 0xA000) != 0))) {
            if (D_00484314[pan->field12] == 0) {
                if (((unsigned char)PadIsAnalogMode_184960(D_004B27E0)) != 0) {
                    D_00484314[pan->field12] = 1;
                }
            } else {
                D_00484314[pan->field12] = 0;
            }
            insmenu_InsectVsCtrlSetRefreshRows_4eb050();
        }
    }
    return 1;
}
