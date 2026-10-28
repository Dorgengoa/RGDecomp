/* rgp:protos */
#define RGP_SELF_MenuCursorBobUpdate_342e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[0x10 - 0x6];
    s16 unk10;
} Obj00342e70;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360 __attribute__((section(".sdata")));
extern f32 D_00482D18;

void MenuCursorBobUpdate_342e70(Obj00342e70 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_6;
    s32 temp_7;
    f32 t;

    PhaseAdvanceWrapPi_28b630(&D_00482D18, D_0047D3B8);
    t = 12.0f * Sinf_128fd0(D_00482D18);
    temp_6 = (s32) ((f32) arg2 + (t + (f32) (arg0->unk0 + (arg0->unk10 * arg0->unk4))));
    temp_7 = arg0->unk2 + arg3;
    if (arg4 != 0) {
        UiSetWidgetPos_290f60(D_00482360, 0x19E, temp_6, temp_7);
    } else {
        UiMoveWidgetUniform_290f50(D_00482360, 0x19E, temp_6, temp_7, 0.25f, 0);
    }
}
