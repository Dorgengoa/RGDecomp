#include "types.h"

extern "C" {
extern void *GetGameData_1fede0(void);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern s32 MenuItemIsDisabled_2a0270(s32 *, s32);
extern s32 MenuGetMode_2a4e30(s32 *);
extern s32 MenuItemGetOpenModeMaybe_2a4ec0(s32 *);
extern s32 PartyFindSlotOfId_3c3070(s32, s32);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern s32 CageRecIsPlaced_3d0d20(s32);
extern s32 InvObjCastToItem4B0_3d3cd0(s32);
extern s32 ItemHasAnyEffectMaybe_3d42e0(s32);
extern s32 ItemIsUnheldFlaggedMaybe_3d4420(s32);
extern s32 ItemHasCountFlag_3d44e0(s32);
extern s32 ItemIsWeapon_3d46c0(s32);
extern s32 PartyFindItemHolder_3d4c20(s32);
extern s32 ItemGetOwnerCharaId_3d4d50(s32, s32);
extern f32 D_0047D288;
s32 MenuItemCmdColors_2a1140(s32 *self, s32 obj, s16 mode);
}


s32 MenuItemCmdColors_2a1140(s32 *self, s32 obj, s16 mode)
{
    s32 g;
    s32 t;
    s32 p;
    f32 v;
    f32 w;

    g = (s32)GetGameData_1fede0();
    if (mode == 0 || mode == 5) {
        if (ItemHasAnyEffectMaybe_3d42e0(obj) != 0 || MenuItemIsDisabled_2a0270(self, obj) != 0) {
            if (*(s8 *)(*(s32 *)(obj + 0x10) + 2) == 5 && !(*(u8 *)(*(s32 *)(g + 0x20) + 0x24C) & 1)) {
                v = D_0047D288;
            } else if (ItemHasAnyEffectMaybe_3d42e0(obj) == 0 && MenuItemGetOpenModeMaybe_2a4ec0(self) == 2) {
                v = D_0047D288;
            } else {
                v = 1.0f;
            }
        } else {
            v = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*self, 0x83, v, v, v, 1.0f);
        UiSetWidgetColor_2905b0(*self, 0x84, 1.0f, 1.0f, 1.0f, 1.0f);
        if (MenuItemIsDisabled_2a0270(self, obj) != 0) {
            v = D_0047D288;
        } else {
            v = 1.0f;
        }
        UiSetWidgetColor_2905b0(*self, 0x85, v, v, v, 1.0f);
        if (ItemIsUnheldFlaggedMaybe_3d4420(obj) != 0) {
            v = 1.0f;
        } else {
            v = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*self, 0x86, v, v, v, 1.0f);
        if (ItemHasCountFlag_3d44e0(obj) != 0 && MenuGetMode_2a4e30(self) != 9) {
            v = 1.0f;
        } else {
            v = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*self, 0x87, v, v, v, 1.0f);
        if (MenuGetMode_2a4e30(self) != 9) {
            v = 1.0f;
        } else {
            v = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*self, 0x88, v, v, v, 1.0f);
    } else if (mode == 1) {
        if (ItemIsWeapon_3d46c0(obj) != 0) {
            v = 1.0f;
        } else {
            v = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*self, 0x83, v, v, v, 1.0f);
        w = D_0047D288;
        t = ItemGetOwnerCharaId_3d4d50(obj, 1);
        if ((bool)PartyFindItemHolder_3d4c20(obj) == false && t != -1 && MenuGetMode_2a4e30(self) != 9 && PartyFindSlotOfId_3c3070(*(s32 *)(g + 0x18), t) != -1 &&
            (*(s8 *)(*(s32 *)(obj + 0x10) + 2) != 0 || StateFlagTest_3ccd70(*(s32 *)(g + 0x10), 0xB6) == 0 || t != 0)) {
            w = 1.0f;
        }
        UiSetWidgetColor_2905b0(*self, 0x84, w, w, w, 1.0f);
        if (ItemIsUnheldFlaggedMaybe_3d4420(obj) != 0) {
            v = 1.0f;
        } else {
            v = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*self, 0x85, v, v, v, 1.0f);
        UiSetWidgetColor_2905b0(*self, 0x86, 1.0f, 1.0f, 1.0f, 1.0f);
        if (MenuGetMode_2a4e30(self) != 9) {
            v = 1.0f;
        } else {
            v = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*self, 0x87, v, v, v, 1.0f);
    } else if (mode == 3) {
        if (MenuItemGetOpenModeMaybe_2a4ec0(self) == 2) {
            w = D_0047D288;
        } else {
            w = 1.0f;
        }
        UiSetWidgetColor_2905b0(*self, 0x83, w, w, w, 1.0f);
        UiSetWidgetColor_2905b0(*self, 0x84, w, w, w, 1.0f);
        UiSetWidgetColor_2905b0(*self, 0x85, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(*self, 0x86, 1.0f, 1.0f, 1.0f, 1.0f);
    } else if (mode == 2) {
        UiSetWidgetColor_2905b0(*self, 0x83, 1.0f, 1.0f, 1.0f, 1.0f);
        if (ItemIsWeapon_3d46c0(obj) != 0) {
            v = 1.0f;
        } else {
            v = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*self, 0x84, v, v, v, 1.0f);
        UiSetWidgetColor_2905b0(*self, 0x85, 1.0f, 1.0f, 1.0f, 1.0f);
    } else if (mode == 4) {
        p = InvObjCastToItem4B0_3d3cd0(obj);
        if (p == 0) {
            return 0;
        }
        if (MenuItemGetOpenModeMaybe_2a4ec0(self) == 2) {
            w = 1.0f;
            UiSetWidgetColor_2905b0(*self, 0x83, D_0047D288, D_0047D288, D_0047D288, 1.0f);
            UiSetWidgetColor_2905b0(*self, 0x84, D_0047D288, D_0047D288, D_0047D288, 1.0f);
            UiSetWidgetColor_2905b0(*self, 0x85, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        } else {
            if (*(s16 *)(*(s32 *)(p + 0x18) + 2) > 0 && CageRecIsPlaced_3d0d20(p) == 0) {
                v = 1.0f;
            } else {
                v = D_0047D288;
            }
            w = 1.0f;
            UiSetWidgetColor_2905b0(*self, 0x83, v, v, v, 1.0f);
            if (CageRecIsPlaced_3d0d20(p) != 0) {
                v = D_0047D288;
            } else {
                v = 1.0f;
            }
            UiSetWidgetColor_2905b0(*self, 0x84, v, v, v, 1.0f);
            if (*(s16 *)(*(s32 *)(p + 0x18) + 2) > 0 && CageRecIsPlaced_3d0d20(p) == 0) {
                v = 1.0f;
            } else {
                v = D_0047D288;
            }
            UiSetWidgetColor_2905b0(*self, 0x85, v, v, v, 1.0f);
        }
        switch (CageRecIsPlaced_3d0d20(p)) {
        case 0:
            w = D_0047D288;
        }
        UiSetWidgetColor_2905b0(*self, 0x86, w, w, w, 1.0f);
        UiSetWidgetColor_2905b0(*self, 0x87, 1.0f, 1.0f, 1.0f, 1.0f);
    }
    return 1;
}
