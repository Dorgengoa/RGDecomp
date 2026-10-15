#include "types.h"

typedef struct {
    u8 pad[0x10];
    s16 x;
    s16 y;
} Cursor;

extern s32 GetGameData_1fede0(void);
extern void PlayMenuSe_289ef0(s32);
extern void UiSetWidgetColor_2905b0(s32, u16, f32, f32, f32, f32);
extern s32 MenuGetSelItem_2a02d0(s32);
extern void MenuItemUseTargetSelFrameLayout_2a0a60(s32, s16, s16, s32);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 ItemGetUseEffectTargetModeMaybe_3d4f00(s32);
extern f32 D_0047D288;
extern s32 D_00482360;
extern s32 D_00482374;
extern s16 D_004824C0;
extern s16 D_004824C2;

s32 MenuItemUseTargetCursorCb_2aded0(Cursor *p) {
    s32 mode;
    s32 obj;
    s32 a;
    s32 b;
    s32 i;
    s32 sel;
    u16 id;

    mode = ItemGetUseEffectTargetModeMaybe_3d4f00(MenuGetSelItem_2a02d0(D_00482374));
    if (mode == 2 || mode == 3) {
        p->x = 2;
        p->y = 0;
        return 1;
    }
    obj = GetGameData_1fede0();
    a = PartyCountMembers_3c2010(*(s32 *)(obj + 0x18), 1, 1);
    b = PartyCountReserve_3c1c20(*(s32 *)(obj + 0x18), 1, 1);
    if (D_004824C0 == p->x) {
        if (p->y == 0) {
            if (p->x > 0 && p->x < 4) {
                p->x = 1;
            } else if (p->x == 4) {
                p->x = 2;
            }
            if (a < p->x + 1) {
                p->x = a - 1;
            }
        } else if (p->y == 1) {
            if (p->x == 1) {
                p->x = 2;
            } else if (p->x == 2) {
                p->x = 4;
            }
            if (b < p->x + 1) {
                p->x = b - 1;
            }
        }
    }
    if (b == 0) {
        p->y = 0;
    }
    if (p->y == 0 && p->x >= a) {
        p->x = a - 1;
    } else if (p->y == 0 && p->x < 0) {
        p->x = 0;
    } else if (p->y == 1 && p->x >= b) {
        p->x = b - 1;
    } else if (p->y == 1 && p->x < 0) {
        p->x = 0;
    }
    MenuItemUseTargetSelFrameLayout_2a0a60(D_00482374, p->x, p->y, mode);
    sel = p->x + p->y * 3;
    for (i = 0; i < 10; i++) {
        id = i + 0x8F;
        if (i == sel) {
            UiSetWidgetColor_2905b0(D_00482360, id, 1.0f, 1.0f, 1.0f, 1.0f);
        } else {
            UiSetWidgetColor_2905b0(D_00482360, id, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        }
    }
    D_004824C0 = p->x;
    D_004824C2 = p->y;
    PlayMenuSe_289ef0(4);
    return 1;
}
