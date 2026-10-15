#include "types.h"

extern void MsgFormat_28a9a0(s32, s32, void *, s32);
extern void MsgFormatParamsCtor_28aa00(void *);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuCursorObjSetVisible_386280(void *, s32);
extern s32 MenuObjInsectGetName_386d40(s32);
extern void UiFitCenterWindow_388270(s32, s32);
extern s32 InsectCageMenuMsgLookup_389d30(s16);
extern void InsectCageMenuSetDrawFlag_390a80(s32, s32);
extern s32 D_00483304;
extern s16 D_00483364;
extern s32 D_0048337C;
extern u8 D_004E94C0[];

s32 InsectCageMenuPairErrorMsgShow_38e980(s32 arg0, s32 arg1)
{
    u8 sp20[0xB0];

    InsectCageMenuSetDrawFlag_390a80(2, 0);
    MenuCursorObjSetVisible_386280(D_004E94C0, 0);
    MsgFormatParamsCtor_28aa00(sp20);
    if (D_0048337C != 0) {
        *(s32 *)(sp20 + 0x1C) = MenuObjInsectGetName_386d40(D_0048337C);
    }
    MsgFormat_28a9a0(D_00483304 + 0x800, InsectCageMenuMsgLookup_389d30(D_00483364), sp20, 1);
    UiFitCenterWindow_388270(0x75DA, 1);
    UiSetWidgetsVisibleById_291110(arg1, 0x75DA, 1, 1);
    return 1;
}
