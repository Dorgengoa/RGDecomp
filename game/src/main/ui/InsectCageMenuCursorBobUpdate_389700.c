/* rgp:protos */
#define RGP_SELF_InsectCageMenuCursorBobUpdate_389700 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma no_branch_likely on

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1E8 __attribute__((section(".sdata")));
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_0048330C __attribute__((section(".sdata")));
extern f32 D_00483320;
extern s32 D_00483328 __attribute__((section(".sdata")));
extern s32 D_0048332C __attribute__((section(".sdata")));

void InsectCageMenuCursorBobUpdate_389700(s32 arg0) {
    s32 temp_6;
    s32 t2c;
    f32 tf;

    PhaseAdvanceWrapPi_28b630(&D_00483320, D_0047D3B8);
    tf = 6.0f * Sinf_128fd0(D_00483320);
    temp_6 = (s32)((f32)D_00483328 + tf);
    t2c = D_0048332C;
    if (arg0 != 0) {
        UiSetWidgetPos_290f60(D_0048330C, 0x7602, temp_6, t2c);
        return;
    }
    UiMoveWidgetUniform_290f50(D_0048330C, 0x7602, temp_6, t2c, D_0047D1E8, 0);
}
