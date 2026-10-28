/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamPwStepCb_4f4260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F4260 (352 bytes, 88 instructions, 13 calls) -- the map's other
 * cancel path, a near-twin of insmenu_InsectVsTeamInfoStepCb_4f43f0.  Same four-term
 * short-circuit chain against 0x20 then 0x10, same `func_2F6660` guard written
 * as a single condition (not an early return) so the shared epilogue keeps its
 * predecessors and the branch into it stays LIKELY.
 *
 * Both arms end with `D_00484360 = 0;` sunk into the `func_28EA90` delay slot.
 */

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];

extern u8 D_00484360;       /* gp - 0xE10 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsTeamPwStepCb_4f4260(void)
{
    if (GetPauseStep_2f6660() == 0) {
        if ((PadIsTriggered_1839f0(D_004B2570, 0x20) != 0) ||
            ((((unsigned char)IsPad2Enabled_2882c0()) != 0) && (PadIsTriggered_1839f0(D_004B27E0, 0x20) != 0))) {
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x9CA7, 0, 1);
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x9CAA, 1, 1);
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88CC, 1, 1);
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88E0, 1, 1);
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88F4, 1, 1);
            SaveUiWidgetFadeIn_37b490(0x890D);
            D_00484360 = 0;
            UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88BD, 0);
        } else if ((PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) ||
                   ((((unsigned char)IsPad2Enabled_2882c0()) != 0) && (PadIsTriggered_1839f0(D_004B27E0, 0x10) != 0))) {
            D_00484360 = 0;
            UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88C0, 0);
        }
    }
    return 1;
}
