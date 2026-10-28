/* rgp:protos */
#define RGP_SELF_MenuCursorBobUpdate_2ba9f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 pad4[0x2];
    s16 unk6;
    u8 pad8[0x8];
    s16 unk10;
    s16 unk12;
} T2ba9f0_arg0;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} T2ba9f0_ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s16 D_0047ED28 __attribute__((section(".sdata")));
extern s16 D_0047ED2A __attribute__((section(".sdata")));
extern s16 D_0047ED2C __attribute__((section(".sdata")));
extern s32 D_00482360 __attribute__((section(".sdata")));
extern f32 D_00482560;

s32 MenuCursorBobUpdate_2ba9f0(T2ba9f0_arg0 *arg0, s32 pad1, s32 arg2, s32 arg3, s32 arg4)
{
    s16 tbl[3];
    f32 f;
    s32 v;
    s32 i;
    s32 x;
    s32 y;

    PhaseAdvanceWrapPi_28b630(&D_00482560, D_0047D3B8);
    f = 12.0f * Sinf_128fd0(D_00482560);
    if (arg0->unk12 == 0) {
        v = 0x82;
    } else {
        i = PartyCountReserve_3c1c20(((T2ba9f0_ctx *)GetGameData_1fede0())->unk18, 1, 1) - 5;
        if (i <= 0) {
            i = 0;
        }
        tbl[0] = D_0047ED28;
        tbl[1] = D_0047ED2A;
        tbl[2] = D_0047ED2C;
        v = tbl[i];
    }
    x = (s32)((f32)arg2 + (f + (f32)(arg0->unk0 + arg0->unk10 * v)));
    y = arg3 + (arg0->unk2 + arg0->unk12 * arg0->unk6);
    if (arg4 != 0) {
        UiSetWidgetPos_290f60(D_00482360, 0x117, x, y);
    } else {
        UiMoveWidgetUniform_290f50(D_00482360, 0x117, x, y, 0.25f, 0);
    }
    return 1;
}
