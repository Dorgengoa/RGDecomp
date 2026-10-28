/* rgp:protos */
#define RGP_SELF_GoTitleMenuPromptOpen_39bda0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R39bda0 {
    u8 pad00[4];
    s16 m04;
    s16 m06;
    s16 m08;
    u8 pad0A[0xA];
    s16 m14;
} R39bda0;

extern u8 D_004E9680[];
extern u8 D_004E9660[];
extern void *D_00481BBC;
extern s32 D_00483610;
extern f32 D_0047D7CC;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 GoTitleMenuPromptOpen_39bda0(s32 unused, s32 en)
{
    R39bda0 *r;

    if (en != 0) {
        UiEntryListSelectByTag_28ea90(D_004E9680, 0x7152, 1);
        UiSetWidgetsVisibleById_291110(D_004E9660, 0xA, 1, 1);
        UiSetWidgetPos_290f60(D_004E9660, 0xA, 0x94, 0x96);
        UiFadeWidgetAlpha_290690(D_004E9660, 0xA, 1.0f, D_0047D7CC, 0.0f);
        UiFadeWidgetAlpha_290690(D_004E9660, 0xD, 1.0f, D_0047D7CC, -1.0f);
        UiSetTextString_28f510(D_004E9660, 0xC, MsgTableLookup_28aa30(D_00481BBC, 0x5C), 0);
        UiSetSpriteU_28f930(D_004E9660, 0xC, 0x4C, 1);
        UiSetSpriteU_28f930(D_004E9660, 0xC, 0x18, 0);
        UiSetTextString_28f510(D_004E9660, 0xC, MsgTableLookup_28aa30(D_00481BBC, 0x52), 1);
        UiSetTextString_28f510(D_004E9660, 0xC, MsgTableLookup_28aa30(D_00481BBC, 0x53), 2);
        r = ((R39bda0 *)UiEntryListFindByTag_28ea40(D_004E9680, 0x7152));
        r->m14 = 1;
        UiSetWidgetPos_290f60(D_004E9660, 0xD, r->m04 + r->m14 * r->m08, r->m06);
    }
    StateMachineSetState_28ede0(&D_00483610, 0x7153, 0);
    return 1;
}
