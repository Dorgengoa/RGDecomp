/* rgp:protos */
#define RGP_SELF_TransMenuItemCmdColors_2a0d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x18];
    s32 x18;
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D288;

s32 TransMenuItemCmdColors_2a0d20(s32 *obj, s32 id, s16 mode, s32 type) {
    Ctx *ctx;
    f32 s;
    f32 f;

    ctx = ((Ctx *)GetGameData_1fede0());
    s = 1.0f;
    if (type == 0) {
        if (InvMoveItemToCategoryMaybe_3c59b0(ctx->x18, id, 1, -1, 0, 0, 0, 1) == 0) {
            s = D_0047D288;
        }
    } else if (type == 1) {
        if (InvMoveItemToCategoryMaybe_3c59b0(ctx->x18, id, 0, -1, 0, 0, 0, 1) == 0) {
            s = D_0047D288;
        }
    }
    UiSetWidgetColor_2905b0(*obj, 0x7652, s, s, s, 1.0f);
    if (mode == 0 || mode == 5) {
        UiSetWidgetColor_2905b0(*obj, 0x7653, 1.0f, 1.0f, 1.0f, 1.0f);
        if (MenuItemIsDisabled_2a0270(obj, id)) {
            f = D_0047D288;
        } else {
            f = 1.0f;
        }
        UiSetWidgetColor_2905b0(*obj, 0x7654, f, f, f, 1.0f);
        if (ItemIsUnheldFlaggedMaybe_3d4420(id)) {
            f = 1.0f;
        } else {
            f = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*obj, 0x7655, f, f, f, 1.0f);
        if (ItemHasCountFlag_3d44e0(id)) {
            f = 1.0f;
        } else {
            f = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*obj, 0x7656, f, f, f, 1.0f);
        UiSetWidgetColor_2905b0(*obj, 0x7657, 1.0f, 1.0f, 1.0f, 1.0f);
    } else if (mode == 1) {
        if (ItemIsWeapon_3d46c0(id)) {
            f = 1.0f;
        } else {
            f = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*obj, 0x7653, f, f, f, 1.0f);
        if (ItemIsUnheldFlaggedMaybe_3d4420(id)) {
            f = 1.0f;
        } else {
            f = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*obj, 0x7654, f, f, f, 1.0f);
        UiSetWidgetColor_2905b0(*obj, 0x7655, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(*obj, 0x7656, 1.0f, 1.0f, 1.0f, 1.0f);
    } else if (mode == 3) {
        UiSetWidgetColor_2905b0(*obj, 0x7653, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        UiSetWidgetColor_2905b0(*obj, 0x7654, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(*obj, 0x7655, 1.0f, 1.0f, 1.0f, 1.0f);
    } else if (mode == 4) {
        UiSetWidgetColor_2905b0(*obj, 0x7653, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        UiSetWidgetColor_2905b0(*obj, 0x7654, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        UiSetWidgetColor_2905b0(*obj, 0x7655, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        UiSetWidgetColor_2905b0(*obj, 0x7656, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(*obj, 0x7657, 1.0f, 1.0f, 1.0f, 1.0f);
    }
    return 1;
}
