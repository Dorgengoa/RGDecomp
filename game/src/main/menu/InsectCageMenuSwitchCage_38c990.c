/* rgp:protos */
#define RGP_SELF_InsectCageMenuSwitchCage_38c990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct ObjFUN_0038c990 {
    u8 pad0[0x10];
    s16 unk10;
} ObjFUN_0038c990;

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

s32 InsectCageMenuSwitchCage_38c990(ObjFUN_0038c990 *arg0, s32 arg1)
{
    s16 temp16;

    if (((signed char)InsectCageMenuHasCage_391080(arg0->unk10)) == 0) {
        PlayMenuSe_289ef0(6);
    } else {
        temp16 = arg0->unk10;
        if (temp16 == ((signed char)InsectCageGetType_3910c0())) {
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
