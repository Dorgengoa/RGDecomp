/* rgp:protos */
#define RGP_SELF_MenuTacticsAbilityListCursorCbMaybe_353bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct {
    u8 pad0[0x12];
    s16 unk12;
    u8 pad14[0x16 - 0x14];
    s16 unk16;
} Obj00353bf0;

typedef struct {
    u8 pad0[0x6C];
    f32 unk6C;
    u8 pad70[0x72 - 0x70];
    s16 unk72;
} Obj0048237C;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482360;
extern Obj0048237C *D_0048237C;
extern s16 D_00482F14;
extern u8 D_004B2570[];

s32 MenuTacticsAbilityListCursorCbMaybe_353bf0(Obj00353bf0 *arg0)
{
    s32 arg_h1;
    s16 x;
    s16 y;
    f32 f;
    f32 g;

    if (!(PadIsTriggered_1839f0(D_004B2570, 0xA000) == 0)) {
        MenuCycleCharaSel_3537c0(arg0, 0);
        UiSetWidgetPos_290f60(D_00482360, 0xC6, 0x18, 0x39);
    } else {
        y = D_0048237C->unk72;
        x = arg0->unk12;
        if (x == y) {
            g = D_0048237C->unk6C;
            f = (f32) arg0->unk16;
            UiMoveWidgetUniform_290f50(D_00482360, 0x1A5, 0x178, (s32) (51.0f + f * g), 0.25f, 0
);
            arg_h1 = D_00482F14;
            MenuTacticsAbilityListRefreshMaybe_355d20(D_0048237C, arg_h1, arg0->unk16);
        }
        UiSetWidgetPos_290f60(D_00482360, 0xC6, 0x18, (arg0->unk12 * 0x1B) + 0x39);
        D_0048237C->unk72 = arg0->unk12;
    }
    return 1;
}
