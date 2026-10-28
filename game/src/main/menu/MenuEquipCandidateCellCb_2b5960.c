/* rgp:protos */
#define RGP_SELF_MenuEquipCandidateCellCb_2b5960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004DB7F0[];
extern u8 D_004DB7C0[];
extern void *D_00482370;
extern void *D_00482360;
extern void *D_0048235C;
extern f32 D_0047D34C;

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

s32 MenuEquipCandidateCellCb_2b5960(s16 *p)
{
    s32 a;
    s32 b;
    s16 *r;
    s32 t;

    a = p[8] * p[2];
    b = p[9] * p[3];
    UiSelFrameSetRect_28db40(D_004DB7F0, 0x180, 0xDA, 0x13, 0xBB, 0xB9, 0x42, 0xD0);
    UiSelFrameSetRect_28db40(D_004DB7C0, 0x14E, a + 0x19, b + 0x17, 0x2A, 0x30, 0x42, 0x42);
    r = ((s16 *)MenuGetGridSel_29f9c0(D_00482370));
    if (p[9] == r[1]) {
        if (p[0xB] != r[2]) {
            MenuEquipCandidateRowFill_29de60(D_00482370, 0x166, p[9], p[0xB]);
            t = 0x32;
            if (p[9] == 1) {
                t *= -1;
            }
            UiMoveWidget_290e00(D_00482360, 0x165, 0, t, 1, 0.0f, 4.0f);
            UiMoveWidget_290e00(D_00482360, 0x134, 0, t, 1, 0.0f, 4.0f);
            UiMoveWidgetUniform_290f50(D_00482360, 0x136, 0x183, (s32)(30.0f + (f32)p[0xB] * MenuGetScrollStep_29f9a0(D_00482370)), D_0047D34C, 0

);
            StateMachineSetState_28ede0(D_0048235C, 0x62, 0);
        }
    }
    MenuEquipCandidateInfoPanelUpdate_2b4360(MenuGetEquipCandidate_29f9f0(D_00482370, p[8] + p[9] * 8 + p[0xB] * 8));
    MenuSetGridSel_29f9b0(D_00482370, p[8], p[9], p[0xB]);
    return 1;
}
