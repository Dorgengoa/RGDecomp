/* rgp:protos */
#define RGP_SELF_MenuPartySwapSelectOpenState_2b8e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A2b8e70 {
    u8 pad00[0x18];
    void *m18;
} A2b8e70;

typedef struct B2b8e70 {
    s8 m00;
    s8 m01;
} B2b8e70;

extern void *D_00482360;
extern void *D_0048235C;
extern void *D_00482364;
extern void *D_00482370;
extern s16 D_00482570;
extern f32 D_0047D6C8;
extern f32 D_0047D6CC;
extern f32 D_0047D35C;
extern u8 D_004DB730[];
extern u8 D_004DB760[];
extern s16 D_004510E0[];
extern s16 D_004510E2[];
extern s16 D_004510E4[];
extern s16 D_004510E6[];

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
/*rgp*/
/*rgp*/

s32 MenuPartySwapSelectOpenState_2b8e70(s32 unused, s32 en)
{
    A2b8e70 *x;
    B2b8e70 *y;
    s32 s;
    s32 idx;
    s16 *p;

    if (en != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x184, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x184, 1.0f, D_0047D6C8, -1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x14B, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x14B, 1.0f, D_0047D6C8, -1.0f);
        UiSelFrameInit_28da30(D_004DB730, D_00482360, 0x14B);
        s = D_00482570;
        UiSelFrameSetRect_28db40(D_004DB730, 0x14B, D_004510E0[s * 4], D_004510E2[s * 4],
                     D_004510E4[s * 4], D_004510E6[s * 4], 0x42, 0x42);
        UiSelFrameCalcTileCounts_28d9d0(D_004DB730);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x14C, 1, 1);
        UiSelFrameInit_28da30(D_004DB760, D_00482360, 0x14C);
        x = ((A2b8e70 *)GetGameData_1fede0());
        y = ((B2b8e70 *)MenuGetCursorPos_29fae0(D_00482370));
        idx = y->m00 + y->m01 * PartyCountMembers_3c2010(x->m18, 1, 1);
        MenuSetSwapSrc_29fa70(D_00482370, idx);
        UiSelFrameSetRect_28db40(D_004DB760, 0x14C, D_004510E0[idx * 4],
                     D_004510E2[idx * 4], D_004510E4[idx * 4],
                     D_004510E6[idx * 4], 0x42, 0x42);
        UiSelFrameCalcTileCounts_28d9d0(D_004DB760);
        UiSetWidgetColor_2905b0(D_00482360, 0x14C, 1.0f, D_0047D35C, D_0047D6CC, 1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x53, 0);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x12, 0);
        p = ((s16 *)UiEntryListGetCurrentData_28ec60(D_00482364));
        UiSetWidgetPos_290f60(D_00482360, 0x184, p[0], p[1]);
    }
    UiSelFrameAnimStep_28d820(D_004DB730, 0x14B);
    UiSelFrameAnimStep_28d820(D_004DB760, 0x14C);
    return 1;
}
