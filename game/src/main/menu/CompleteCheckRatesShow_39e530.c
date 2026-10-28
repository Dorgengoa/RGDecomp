/* rgp:protos */
#define RGP_SELF_CompleteCheckRatesShow_39e530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void Sprintf_1343b8(char *, const char *, s32);
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
/*rgp*/
extern void *memset(void *, s32, u32);
extern s16 D_00464450[];
extern char D_00464460[];
extern f32 D_0047D5D0;
extern u8 D_00483690[8];
extern s32 D_0048369C;
extern u8 D_004E96B0[];
extern u8 D_004E96D0[];
extern char D_004E9700[8][8];

s32 CompleteCheckRatesShow_39e530(s32 arg0, s32 arg1) {
    s32 obj;
    s32 i;
    s32 r;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_004E96D0, 0x7531, 1);
        UiSetWidgetVisible_290010(D_004E96B0, 1, 1, -1);
        UiFadeWidgetAlpha_290690(D_004E96B0, 1, 1.0f, D_0047D5D0, 0.0f);
        UiSetWidgetPos_290f60(D_004E96B0, 1, 0x80, 0x6E);
        UiSetWidgetPos_290f60(D_004E96B0, 7, 0, 0);
        UiSetWidgetPos_290f60(D_004E96B0, 5, 0, 0);
        obj = ((s32)GetGameData_1fede0());
        CompletionRatesUpdate_3e7800(obj);
        for (i = 0; i < 8; i++) {
            memset(D_004E9700[i], 0, 8);
        }
        UiSetTextString_28f510(D_004E96B0, 6, ((char *)MsgTableLookup_28aa30(D_0048369C, 0)), 0x10);
        UiSetTextCenteredX_28f300(D_004E96B0, 6, 0x80, 0x10);
        for (i = 0; i < 8; i++) {
            UiSetTextString_28f510(D_004E96B0, 6, ((char *)MsgTableLookup_28aa30(D_0048369C, i + 1)), i + 8);
            r = ((short)StateVarGet_3ccac0(*(s32 *)(obj + 0x10), D_00464450[i]));
            if (r == 100) {
                UiSetTextString_28f510(D_004E96B0, 6, ((char *)MsgTableLookup_28aa30(D_0048369C, 9)), i);
                UiSetTextColor_290a40(D_004E96B0, 6, 0xFF004040, i);
                UiSetTextColor_290a40(D_004E96B0, 6, 0xFF004040, i + 8);
            } else {
                Sprintf_1343b8(D_004E9700[i], D_00464460, r);
                UiSetTextString_28f510(D_004E96B0, 6, D_004E9700[i], i);
                UiSetTextColor_290a40(D_004E96B0, 6, 0xFF303030, i);
                UiSetTextColor_290a40(D_004E96B0, 6, 0xFF303030, i + 8);
            }
        }
    }
    if (!(UiGetWidgetAlpha_290770(D_004E96B0, 1) < 1.0f)) {
        StateMachineSetState_28ede0(D_00483690, 0x7532, 1);
    }
    return 1;
}
