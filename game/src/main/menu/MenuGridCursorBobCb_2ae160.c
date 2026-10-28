/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_2ae160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    u8 pad8[8];
    s16 h10;
    s16 h12;
} Obj;

typedef struct {
    s16 v[3][7];
} Tab;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00451030[0x400];
extern f32 D_0047D278;
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0047D400;
extern f32 D_0047D474;
extern s16 D_0047EC80;
extern s16 D_0047EC82;
extern s16 D_0047EC84;
extern s32 D_00482360;
extern s32 D_00482374;
extern f32 D_004824C8;
extern f32 D_004824EC;
extern u8 D_004DB430[0x100];

s32 MenuGridCursorBobCb_2ae160(Obj *arg0, s32 arg1)
{
    Tab tab __attribute__((aligned(16)));
    volatile s16 row[3];

    f32 s;
    f32 f;
    f32 t;
    s32 lvl;
    s32 x;
    s32 y;

    PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
    s = 6.0f * Sinf_128fd0(D_004824C8);
    lvl = PartyCountReserve_3c1c20(*(s32 *)((u8 *)GetGameData_1fede0() + 0x18), 1, 1) - 5;
    if (lvl <= 0) {
        lvl = 0;
    }
    row[0] = D_0047EC80;
    row[1] = D_0047EC82;
    row[2] = D_0047EC84;
    tab = *(Tab *)D_00451030;
    if (arg0->h12 == 0) {
        x = s + (f32)(arg0->h0 + row[arg0->h10]);
        if (ItemGetUseEffectTargetModeMaybe_3d4f00(MenuGetSelItem_2a02d0(D_00482374)) == 3) {
            y = (f32)(arg0->h2 + 0x60) + s;
        } else {
            y = (f32)arg0->h2 + s;
        }
    } else if (arg0->h12 == 1) {
        x = s + (f32)(arg0->h0 + tab.v[lvl][arg0->h10]);
        y = s + (f32)(arg0->h2 + arg0->h6);
    }
    UiMoveWidgetUniform_290f50(D_00482360, 0x227, x, y, 0.25f, 0);
    PhaseAdvanceWrapPi_28b630(&D_004824EC, D_0047D400);
    t = D_0047D474 * Sinf_128fd0(D_004824EC);
    f = D_0047D278 + t;
    UiSetWidgetColor_2905b0(arg1, 0x8E, f, f, f, 1.0f);
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
