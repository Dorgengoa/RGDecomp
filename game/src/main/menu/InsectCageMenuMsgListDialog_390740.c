/* rgp:protos */
#define RGP_SELF_InsectCageMenuMsgListDialog_390740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
extern s32 D_00482374;
extern u8 D_004832A0;
extern s32 D_004832D8;
extern s32 D_00483304;
extern s8 D_00483368;
extern s8 D_0048336C;
extern u8 D_004E94E0[0x400];
extern u8 D_004E94FC[0x400];

s32 InsectCageMenuMsgListDialog_390740(s32 pad0, s32 arg1)
{
            s32 arg_h0;

    s32 temp_17;
    s32 temp_17_2;
    void *temp_16;
    void *temp_2;

    temp_17 = (*(s32 *)D_004E94FC);
    switch (D_00483368) {
    case 0:
        if (MenuFadeIsIdle_29ffa0(D_00482374) != 0) {
            InsectCageMenuSetStateFlagMaybe_390aa0(1, 1);
            InsectCageMenuSetStateFlagMaybe_390aa0(2, 1);
            MenuObjSetPauseFx_384b20(D_004832D8);
            InsectCageMenuSetDrawFlag_390a80(7, 0);
            InsectCageMenuSetStateFlagMaybe_390aa0(7, 0);
            arg_h0 = arg1;
            UiSetWidgetVisible_290010(arg_h0, 0x760C, 1, -1);
            temp_2 = UiFindWidget_290460(arg1, 0x760C);
            temp_17_2 = *(s32 *)((u8 *)temp_2 + 0x20);
            temp_16 = *(void **)((u8 *)temp_2 + 0x28);
            *(s16 *)((u8 *)temp_16 + 0x2) = 0xE;
            *(s32 *)((u8 *)temp_16 + 0x4) = InsectCageMenuMsgLookup_389d30(0x13EC);
            *(s16 *)((u8 *)temp_16 + 0x12) = 0x34;
            *(s32 *)((u8 *)temp_16 + 0x14) = D_00483304 + 0xA00;
            InsectCageMenuDialogFrameLayoutMaybe_3908c0(temp_17_2 + 0x1A0, 0x195, (long long)(2), (long long)(0x26));
            UiLayoutFrameRectsMaybe_28bbb0(temp_17_2, 0x19A, 0x104);
            InsectCageSePlay_3844b0(&D_004832A0, 5);
            D_0048336C = 0x14;
            D_00483368 += 1;
        } else {
        case 1:
            if (D_0048336C > 0) {
                D_0048336C -= 1;
            } else {
                if (temp_17 & 6) {
                    PlayMenuSe_289ef0(5);
                    UiSetWidgetVisible_290010(arg1, 0x760C, 0, -1);
                    UiEntryListSelectByTag_28ea90(&(*(u8 *)D_004E94E0), 0x7531, 1);
                }
            }
        }
        break;
    }
    return 1;
}
