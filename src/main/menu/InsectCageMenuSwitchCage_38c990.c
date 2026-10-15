#include "types.h"

typedef struct ObjFUN_0038c990 {
    u8 pad0[0x10];
    s16 unk10;
} ObjFUN_0038c990;

extern void PlayMenuSe_289ef0(s32 arg0);
extern void UiSetWidgetVisible_290010(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void MenuFadeStartToColor_2a0040(s32 arg0);
extern void InsectCageMenuSetCursorVisible_389d00(s32 arg0);
extern void InsectCageMenuSetStateFlagMaybe_390aa0(s32 arg0, s32 arg1);
extern void MainMenuSetState_390d60(s32 arg0);
extern s32 InsectCageMenuHasCage_391080(s16 arg0);
extern s32 InsectCageGetType_3910c0(void);
extern void InsectCageSetType_3910d0(s16 arg0);

extern s32 D_00482374;

s32 InsectCageMenuSwitchCage_38c990(ObjFUN_0038c990 *arg0, s32 arg1)
{
    s16 temp16;

    if (InsectCageMenuHasCage_391080(arg0->unk10) == 0) {
        PlayMenuSe_289ef0(6);
    } else {
        temp16 = arg0->unk10;
        if (temp16 == InsectCageGetType_3910c0()) {
            PlayMenuSe_289ef0(6);
        } else {
            PlayMenuSe_289ef0(5);
            UiSetWidgetVisible_290010(arg1, 0x754E, 0, -1);
            InsectCageMenuSetCursorVisible_389d00(0);
            UiSetWidgetVisible_290010(arg1, 0x7576, 0, -1);
            InsectCageSetType_3910d0(arg0->unk10);
            InsectCageMenuSetStateFlagMaybe_390aa0(1, 1);
            MenuFadeStartToColor_2a0040(D_00482374);
            MainMenuSetState_390d60(0xAB);
        }
    }
    return 1;
}
