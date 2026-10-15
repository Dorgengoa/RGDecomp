#include "types.h"

typedef struct Pair {
    s16 a;
    s16 b;
} Pair;

typedef struct Box {
    u8 pad0[4];
    s16 m4;
    s16 m6;
    s16 m8;
    s16 mA;
    s16 mC;
    s16 mE;
} Box;

typedef struct Ent {
    u8 pad0[0x20];
    Box *m20;
} Ent;

extern void UiSetWidgetColor_2905b0(void *, s32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern void UiMoveWidget_290e00(void *, s32, s32, s32, s32, f32, f32);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern void UiMoveWidgetUniform_290f50(void *, s32, s32, s32, s32, f32);
extern void UiFadeWidgetColor_2904e0(void *, s32, f32, f32, f32, f32, f32);
extern void UiGetWidgetPos_2910a0(void *, s32, s32 *, s32 *);
extern Ent *UiFindWidget_290460(void *, s32);
extern s32 LoadHandleIsReady_28b200(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void TopMenuLayoutRows_296790(void);
extern u8 D_004DB1B0[];
extern Pair D_004502E0[];
extern s16 D_004823A4;
extern s16 D_00482340;
extern s16 D_00482344;
extern f32 D_00482348;
extern s32 D_004823F8;
extern u8 D_00482398;
extern s16 D_004823B0;
extern s32 D_00482350;
extern f32 D_0047D6CC;
extern f32 D_0047D35C;
extern f32 D_0047D7B8;
extern f32 D_0047D7BC;
extern f32 D_0047D5E4;
extern f32 D_0047D7C0;
extern f32 D_0047D7C4;
extern f32 D_0047D7AC;

#define UI D_004DB1B0

s32 TopMenuSelectFlashStep_295ec0(void)
{
    s32 id;
    s32 k;
    f32 f;
    s32 w;
    s32 h;
    s32 w2;
    s32 h2;
    Box *p;
    Box *q;

    if (D_004823A4 == 2) {
        return 0;
    }
    switch (D_00482340) {
    case 0:
        break;
    case 1:
        id = (u16)(D_00482344 + 0x39);
        f = D_00482348 + D_0047D6CC;
        D_00482348 = f;
        if (!(f < D_0047D35C)) {
            D_00482348 = D_0047D35C;
            D_00482340 = 2;
        }
        UiSetWidgetColor_2905b0(UI, id, D_00482348, D_00482348, D_00482348, -1.0f);
        break;
    case 2:
        f = D_00482348 + D_0047D7B8;
        id = (u16)(D_00482344 + 0x39);
        D_00482348 = f;
        if (f <= 1.0f) {
            D_00482348 = 1.0f;
            if (LoadHandleIsReady_28b200(D_004823F8) != 0) {
                k = D_00482344;
                if (k == 0) goto L01;
                if (k == 1) {
                L01:
                    if (LoadHandleIsReady_28b200(D_004823F8 + 0x70) != 0) {
                        UiFadeWidgetAlpha_290690(UI, id, 0.0f, D_0047D7BC, -1.0f);
                        D_00482340 = 3;
                    }
                } else if (k == 5) {
                    if (D_00482398 != 0) {
                        UiFadeWidgetAlpha_290690(UI, id, 0.0f, D_0047D7BC, -1.0f);
                        D_00482340 = 3;
                    }
                } else if (k == 6) {
                    UiFadeWidgetAlpha_290690(UI, id, 0.0f, D_0047D7BC, -1.0f);
                    D_004823B0 = 6;
                    StateMachineSetState_28ede0((s32)&D_00482350, 4, 0);
                } else {
                    UiFadeWidgetAlpha_290690(UI, id, 0.0f, D_0047D7BC, -1.0f);
                    D_00482340 = 3;
                }
            }
        }
        UiSetWidgetColor_2905b0(UI, id, D_00482348, D_00482348, D_00482348, -1.0f);
        break;
    case 3:
        TopMenuLayoutRows_296790();
        UiGetWidgetPos_2910a0(UI, 0x16, &w, &h);
        UiMoveWidget_290e00(UI, 1, D_004502E0[D_00482344].a, D_004502E0[D_00482344].b, 3, D_0047D5E4, 0.0f);
        UiSetWidgetPos_290f60(UI, 0x27, 0, D_00482344 * 39 + 0x50);
        UiMoveWidgetUniform_290f50(UI, 0x27, 0, 0, 0, D_0047D7C0);
        UiFadeWidgetColor_2904e0(UI, 0x27, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D7C0);
        D_00482340 = 4;
        break;
    case 4:
        UiGetWidgetPos_2910a0(UI, 0x27, &w2, &h2);
        if ((f32)h2 <= 0.0f) {
            p = UiFindWidget_290460(UI, 0x41)->m20;
            q = UiFindWidget_290460(UI, (u16)(D_00482344 + 0x39))->m20;
            p->m4 = 0x28;
            p->m6 = 0x28;
            p->m8 = q->m8;
            p->mA = q->mA;
            p->mC = q->mC;
            p->mE = q->mE;
            UiSetWidgetPos_290f60(UI, 0x41, 0x30, 0xF);
            UiSetWidgetColor_2905b0(UI, 0x41, 0.0f, 0.0f, 0.0f, 0.0f);
            *(s32 *)&D_00482348 = 0;
            D_00482340 = 7;
        }
        break;
    case 5:
        f = D_00482348 + D_0047D7C4;
        D_00482348 = f;
        if (!(f < D_0047D35C)) {
            D_00482340 = 6;
            D_00482348 = D_0047D35C;
        }
        UiSetWidgetColor_2905b0(UI, 0x41, D_00482348, D_00482348, D_00482348, 1.0f);
        UiFadeWidgetAlpha_290690(UI, 0x41, 1.0f, D_0047D7AC, -1.0f);
        break;
    case 6:
        f = D_00482348 - D_0047D7C4;
        D_00482348 = f;
        if (f <= 1.0f) {
            D_00482348 = 1.0f;
            D_00482340 = 7;
        }
        UiSetWidgetColor_2905b0(UI, 0x41, D_00482348, D_00482348, D_00482348, 1.0f);
        break;
    }
    return 0;
}
