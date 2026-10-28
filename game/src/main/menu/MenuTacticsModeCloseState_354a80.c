/* rgp:protos */
#define RGP_SELF_MenuTacticsModeCloseState_354a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 id;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} T354a80;

typedef struct {
    u8 pad0[4];
    s16 u4;
    s16 u6;
    s16 u8_;
    s16 uA;
    s16 uC;
    s16 uE;
} S354a80;

typedef struct {
    u8 pad0[4];
    s32 u4;
} R354a80;

typedef struct {
    u8 pad0[0x20];
    S354a80 *s;
    u8 pad24[4];
    R354a80 *r;
} M354a80;

typedef struct {
    u8 pad0[0x24];
    s16 u24;
} P354a80;

typedef struct {
    u8 pad0[0xC];
    P354a80 *p;
} O354a80;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern T354a80 D_00462A50[4];
extern f32 D_0047D288;
extern f32 D_0047D5FC;
extern f32 D_0047D604;
extern f32 D_0047D608;
extern s32 D_00481BBC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_0048236C;
extern s32 D_004823D8;
extern s16 D_00482F10;

s32 MenuTacticsModeCloseState_354a80(s32 arg0, s32 arg1) {
    O354a80 *o;
    M354a80 *m;
    S354a80 *s;
    R354a80 *r;
    const T354a80 *t;
    s32 id;
    s32 i;
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    o = ((O354a80 *)GetGameData_1fede0());
    if (arg1 != 0 && D_00482F10 == 0) {
        UiFadeWidgetAlpha_290690(D_0048236C, 1, 0.0f, D_0047D604, -1.0f);
    }
    if (D_00482F10 == 1) {
        if (*((f32 *)UiGetWidgetColor_2904b0(D_0048236C, 2)) <= 1.0f) {
            UiFadeWidgetAlpha_290690(D_0048236C, 1, 0.0f, D_0047D604, -1.0f);
        }
        if (UiGetWidgetAlpha_290770(D_0048236C, 1) <= 0.0f) {
            UiSetWidgetsVisibleById_291110(D_0048236C, 1, 0, 1);
            m = ((M354a80 *)UiFindWidget_290460(D_00482360, 0xC8));
            if (m == NULL) {
                return 0;
            }
            id = o->p->u24;
            s = m->s;
            r = m->r;
            if (s == NULL || r == NULL) {
                return 0;
            }
            for (i = 0; i < 4; i++) {
                t = &D_00462A50[i];
                if (id == t->id) {
                    a = t->a;
                    s->u8_ = a;
                    b = t->b;
                    s->uA = b;
                    c = t->c;
                    d = t->d;
                    s->uC = c;
                    s->u4 = c;
                    s->u6 = d;
                    s->uE = d;
                    r->u4 = MsgTableLookup_28aa30(D_00481BBC, i + 0x4E);
                }
            }
            UiSetWidgetColor_2905b0(D_00482360, 0xC8, D_0047D608, D_0047D608, D_0047D608, -1.0f);
            UiFadeWidgetColor_2904e0(D_00482360, 0xC8, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D5FC);
            UiSetWidgetColor_2905b0(D_00482360, 0xC6, D_0047D608, D_0047D608, D_0047D608, D_0047D288);
            UiFadeWidgetColor_2904e0(D_00482360, 0xC6, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D5FC);
            D_00482F10 = 2;
        }
    } else if (D_00482F10 == 2) {
        if (*((f32 *)UiGetWidgetColor_2904b0(D_00482360, 0xC8)) <= 1.0f) {
            if (o->p->u24 == 2) {
                UiSetTextString_28f510(D_00482360, 0x21E, MsgTableLookup_28aa30(D_004823D8, 0xBB9), 0);
                StateMachineSetState_28ede0(D_0048235C, 0x98, 0);
            } else {
                StateMachineSetState_28ede0(D_0048235C, 0x9A, 0);
            }
        }
    } else {
        if (UiGetWidgetAlpha_290770(D_0048236C, 1) <= 0.0f) {
            UiSetWidgetsVisibleById_291110(D_0048236C, 1, 0, 1);
            StateMachineSetState_28ede0(D_0048235C, 0x9A, 0);
        }
    }
    return 1;
}
