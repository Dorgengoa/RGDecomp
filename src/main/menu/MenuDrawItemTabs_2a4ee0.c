#include "types.h"

typedef struct Obj {
    s32 x0;             /* +0x00 */
    u8 pad4[0xD];
    s8 sel;             /* +0x11 */
} Obj;

typedef struct Rec {
    s16 x0;             /* +0x00 */
    s16 x2;             /* +0x02 */
    u8 pad4[4];
    s64 x8;             /* +0x08 */
    u8 pad10[6];
    s16 x16;            /* +0x16 */
    s16 x18;            /* +0x18 */
    s16 x1a;            /* +0x1A */
    s16 x1c;            /* +0x1C */
    s16 x1e;            /* +0x1E */
} Rec;

typedef struct Actor {
    u8 pad0[0x18];
    s32 x18;
} Actor;

extern Actor *GetGameData_1fede0(void);
extern void UiSetSpritePosSizeUv_28f710(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern Rec *UiGetWidgetSubItem_28f2b0(s32, s32, s32);
extern s32 InvCountInCategory_3c7ba0(s32, s32, s32, s32);
extern s32 D_004659E8[];

s32 func_002A4EF0(Obj *arg0, s32 arg1, s32 sel, s8 mode);

s32 MenuDrawItemTabs_2a4ee0(Obj *arg0, s32 arg1, s8 mode)
{
    return func_002A4EF0(arg0, arg1, arg0->sel, mode);
}

s32 func_002A4EF0(Obj *arg0, s32 arg1, s32 sel, s8 mode)
{
    Actor *actor;
    s32 n0;
    s32 n;
    s32 i;
    s32 k;
    s32 v;
    Rec *p;
    Rec *q;

    actor = GetGameData_1fede0();
    if (arg0->x0 == 0) {
        return 0;
    }
    n0 = D_004659E8[0];
    n = n0 + 1;
    if (mode == 0) {
        n--;
    }
    for (i = 0; i < n; i++) {
        if (i == sel) {
            k = i * 42;
            UiSetSpritePosSizeUv_28f710(arg0->x0, arg1, k + 0x1B, -0x1A, 0x16, 0x29, 0x88, 1, 0x16, 0x29, i * 2);
            UiSetSpritePosSizeUv_28f710(arg0->x0, arg1, k + 0x31, -0x1A, 0x16, 0x29, 0xA6, 1, 0x16, 0x29, (u32)i * 2 + 1);
        } else {
            k = i * 42;
            UiSetSpritePosSizeUv_28f710(arg0->x0, arg1, k + 0x1B, -0x18, 0x16, 0x1B, 0x88, 0x2B, 0x16, 0x1B, i * 2);
            UiSetSpritePosSizeUv_28f710(arg0->x0, arg1, k + 0x31, -0x18, 0x16, 0x1B, 0xA6, 0x2B, 0x16, 0x1B, (u32)i * 2 + 1);
        }
    }
    UiSetSpriteX_28fcd0(arg0->x0, arg1, -1, n * 2);
    if (mode == 0) {
        UiSetWidgetsVisibleById_291110(arg0->x0, 0x6A, 0, 1);
        UiSetWidgetsVisibleById_291110(arg0->x0, 0x6B, 0, 1);
    } else if (mode == 1) {
        UiSetWidgetsVisibleById_291110(arg0->x0, 0x6A, 1, 1);
        UiSetWidgetsVisibleById_291110(arg0->x0, 0x6B, 0, 1);
        v = D_004659E8[0];
        UiSetWidgetPos_290f60(arg0->x0, 0x6A, v * 42 + 0x25, -0xD);
        if (sel < v) {
            UiSetWidgetColor_2905b0(arg0->x0, 0x6A, 0.5f, 0.5f, 0.5f, 1.0f);
        } else {
            UiSetWidgetColor_2905b0(arg0->x0, 0x6A, 1.0f, 1.0f, 1.0f, 1.0f);
        }
    } else if (mode == 2) {
        UiSetWidgetsVisibleById_291110(arg0->x0, 0x6A, 0, 1);
        UiSetWidgetsVisibleById_291110(arg0->x0, 0x6B, 1, 1);
        v = D_004659E8[0];
        UiSetWidgetPos_290f60(arg0->x0, 0x6B, v * 42 + 0x25, -0xD);
        if (sel < v) {
            UiSetWidgetColor_2905b0(arg0->x0, 0x6B, 0.5f, 0.5f, 0.5f, 1.0f);
        } else {
            UiSetWidgetColor_2905b0(arg0->x0, 0x6B, 1.0f, 1.0f, 1.0f, 1.0f);
        }
    }
    p = UiGetWidgetSubItem_28f2b0(arg0->x0, 0x69, 0);
    if (p == 0) {
        return 0;
    }
    UiSetWidgetColor_2905b0(arg0->x0, 0x69, 0.5f, 0.5f, 0.5f, 1.0f);
    q = UiGetWidgetSubItem_28f2b0(arg0->x0, 0x68, 0);
    if (q == 0) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (i == sel) {
            if (i < n0) {
                q->x0 = i * 42 + 0x3B;
                q->x2 = -0xC;
                q->x16 = 0xC;
                q->x18 = 0x10;
                q->x1a |= 2;
                q->x1c = 0xA;
                q->x1e = 0x10;
                q->x8 = InvCountInCategory_3c7ba0(actor->x18, 0, i, 0);
            } else {
                q->x0 = -1;
            }
        } else {
            p->x0 = i * 42 + 0x3B;
            p->x2 = -0xC;
            p->x16 = 0xC;
            p->x18 = 0x10;
            p->x1a |= 2;
            p->x1c = 0xA;
            p->x1e = 0x10;
            if (i < n0) {
                p->x8 = InvCountInCategory_3c7ba0(actor->x18, 0, i, 0);
            } else {
                p->x0 = -1;
            }
            p++;
        }
    }
    return 1;
}
