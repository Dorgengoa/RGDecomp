/* rgp:protos */
#define RGP_SELF_MenuListSyncScrollMaybe_357480 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct {
    u8 pad0[0x64];
    f32 unk64;
    u8 pad68[0x134 - 0x68];
    s32 unk134;
} Ctx00357480;

typedef struct {
    u8 pad0[0x6];
    s16 unk6;
    u8 pad8[0x12 - 0x8];
    s16 unk12;
    u8 pad14[0x16 - 0x14];
    s16 unk16;
} Obj00357480;

/*rgp*/    /* extern */
/*rgp*/              /* extern */
/*rgp*/                   /* extern */
/*rgp*/                   /* extern */
extern Ctx00357480 *D_00482380;
extern s32 D_00482F88;
extern s32 D_00482F8C;

void MenuListSyncScrollMaybe_357480(Obj00357480 *arg0) {
    s16 temp_4;
    s16 temp_4_2;

    temp_4 = arg0->unk12;
    if (temp_4 != D_00482F88) {
        D_00482F88 = (s32) temp_4;
        UiSetWidgetPos_290f60(D_00482380->unk134, 0x1DE, 0x10, (arg0->unk12 * arg0->unk6) + 0x11);
        MenuModelPageShowCursorEntryItemsMaybe_359cf0(D_00482380);
    }
    temp_4_2 = arg0->unk16;
    if (temp_4_2 != D_00482F8C) {
        D_00482F8C = (s32) temp_4_2;
        MenuModelPageLogRowsRefreshMaybe_35a1a0(D_00482380);
        MenuModelPageShowCursorEntryItemsMaybe_359cf0(D_00482380);
        {
            f32 m = D_00482380->unk64;
            UiMoveWidgetUniform_290f50(D_00482380->unk134, 0x1D9, 0x14D, (s32) (30.0f + ((f32) arg0->unk16 * m)), 0.25f, 0);
        }
    }
}
