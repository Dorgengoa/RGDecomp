/* rgp:protos */
#define RGP_SELF_MenuItemCategoryTabsLayout_288ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Spr {
    s16 m0;
    s16 m2;
    u8 pad4[4];
    s64 m8;
    u8 pad10[6];
    s16 m16;
    s16 m18;
    s16 m1A;
    s16 m1C;
    s16 m1E;
} Spr;

typedef struct Ctx {
    u8 pad0[0x18];
    s32 m18;
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004659E8[];
extern s32 D_00465A18[];

s32 MenuItemCategoryTabsLayout_288ac0(s32 arg0, s32 arg1, u16 arg2, u16 arg3, s32 sel, s32 mode) {
    s32 max;
    Ctx *ctx;
    s32 i;
    s32 x;
    Spr *p;
    Spr *q;

    if (mode == 0) {
        max = D_004659E8[0];
    } else if (mode == 1) {
        max = D_00465A18[0];
    }
    ctx = ((Ctx *)GetGameData_1fede0());
    for (i = 0; i < 0x10; i++) {
        if (i == max) {
            UiSetSpriteX_28fcd0(arg0, arg1, -1, i * 2);
            break;
        }
        if (i == sel) {
            x = i * 42;
            UiSetSpritePosSizeUv_28f710(arg0, arg1, x + 0x1B, -0x1A, 0x16, 0x29, 0x88, 1, 0x16, 0x29, i * 2);
            UiSetSpritePosSizeUv_28f710(arg0, arg1, x + 0x31, -0x1A, 0x16, 0x29, 0xA6, 1, 0x16, 0x29, (u32)i * 2 + 1);
        } else {
            x = i * 42;
            UiSetSpritePosSizeUv_28f710(arg0, arg1, x + 0x1B, -0x18, 0x16, 0x1B, 0x88, 0x2B, 0x16, 0x1B, i * 2);
            UiSetSpritePosSizeUv_28f710(arg0, arg1, x + 0x31, -0x18, 0x16, 0x1B, 0xA6, 0x2B, 0x16, 0x1B, (u32)i * 2 + 1);
        }
    }
    p = ((Spr *)UiGetWidgetSubItem_28f2b0(arg0, arg2, 0));
    if (p == 0) {
        return 0;
    }
    UiSetWidgetColor_2905b0(arg0, arg2, 0.5f, 0.5f, 0.5f, 1.0f);
    q = ((Spr *)UiGetWidgetSubItem_28f2b0(arg0, arg3, 0));
    if (q == 0) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (i == sel) {
            if (i < max) {
                q->m0 = i * 42 + 0x3B;
                q->m2 = -0xC;
                q->m16 = 0xC;
                q->m18 = 0x10;
                q->m1A |= 2;
                q->m1C = 0xA;
                q->m1E = 0x10;
                q->m8 = InvCountInCategory_3c7ba0(ctx->m18, mode, i, 0);
            } else {
                q->m0 = -1;
            }
        } else {
            p->m0 = i * 42 + 0x3B;
            p->m2 = -0xC;
            p->m16 = 0xC;
            p->m18 = 0x10;
            p->m1A |= 2;
            p->m1C = 0xA;
            p->m1E = 0x10;
            if (i < max) {
                p->m8 = InvCountInCategory_3c7ba0(ctx->m18, mode, i, 0);
            } else {
                p->m0 = -1;
            }
            p++;
        }
    }
    UiSetWidgetsVisibleById_291110(arg0, arg2, 1, 1);
    return 1;
}
