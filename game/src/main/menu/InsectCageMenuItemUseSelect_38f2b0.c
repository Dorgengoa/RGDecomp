/* rgp:protos */
#define RGP_SELF_InsectCageMenuItemUseSelect_38f2b0 1
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
extern u16 D_0047FC00[] __attribute__((section(".sdata")));
extern s16 D_00483364;

s32 InsectCageMenuItemUseSelect_38f2b0(s32 arg0, s32 arg1)
{
    s32 h;
    s32 idx;
    s32 a;
    s32 r;

    InsectCageMenuGetCursorInvItem_38f550(&h);
    if (h == 0) {
        PlayMenuSe_289ef0(6);
        return 0;
    }
    idx = ItemInsectUseClassMaybe_390b20(h);
    a = InsectCageMenuGetCursorObj_390f70();
    r = InsectCageMenuItemUseStatus_38fb50(h, a, MenuObjCountActive_390ec0());
    if (r == 1) {
        PlayMenuSe_289ef0(6);
        return 0;
    }
    InsectCageMenuItemPanelShowMaybe_38fc60(0);
    UiSetWidgetsVisibleById_291110(arg1, 0x7616, 0, 1);
    InsectCagePreviewModelSetup_389370(0, 1);
    InsectCageMenuSetDrawFlag_390a80(7, 0);
    InsectCageMenuSetStateFlagMaybe_390aa0(7, 0);
    if (r == 3) {
        PlayMenuSe_289ef0(6);
        D_00483364 = 0x4BC;
        InsectCageMenuSelectEntry_390d40(0x7535, 0);
        return 1;
    } else if (r == 2) {
        PlayMenuSe_289ef0(6);
        D_00483364 = 0x4BB;
        InsectCageMenuSelectEntry_390d40(0x7535, 0);
        return 1;
    } else if (r == 4) {
        PlayMenuSe_289ef0(6);
        D_00483364 = 0x4BA;
        InsectCageMenuSelectEntry_390d40(0x7535, 0);
        return 1;
    } else if (r == 5) {
        PlayMenuSe_289ef0(6);
        D_00483364 = 0x4BD;
        InsectCageMenuSelectEntry_390d40(0x7535, 0);
        return 1;
    } else if (r == 6) {
        PlayMenuSe_289ef0(6);
        D_00483364 = 0x4BF;
        InsectCageMenuSelectEntry_390d40(0x7535, 0);
        return 1;
    } else {
        InsectCageMenuSetDrawFlag_390a80(2, 0);
        PlayMenuSe_289ef0(5);
        InsectCageMenuSelectEntry_390d40(D_0047FC00[idx], 0);
        return 1;
    }
}
