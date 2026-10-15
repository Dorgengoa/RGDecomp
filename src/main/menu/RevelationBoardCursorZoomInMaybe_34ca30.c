#include "types.h"

#pragma divbyzerocheck on

typedef struct {
    u8 pad0[4];
    s16 m4;
    s16 m6;
} Sub34ca30;

typedef struct {
    u8 pad0[0x20];
    Sub34ca30 *m20;
} Ent34ca30;

typedef struct {
    s32 h;
    u32 m4;
    u8 pad8[4];
    s32 mC;
    u8 pad10[0x770 - 0x10];
    s16 m770;
    s16 m772;
    u8 pad774[4];
    f32 m778;
} Obj34ca30;

extern f32 Cosf_128d30(f32);
extern void *GetGameData_1fede0(void);
extern Ent34ca30 *UiFindWidget_290460(s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern u32 RevelationBoardGetCells_3eb510(void *, s32);
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern const f32 D_0047D248 __attribute__((section(".sdata")));
extern const f32 D_0047D288 __attribute__((section(".sdata")));

s32 RevelationBoardCursorZoomInMaybe_34ca30(Obj34ca30 *arg0)
{
    void *g;
    s16 cnt;
    f32 c;
    Ent34ca30 *e;
    Sub34ca30 *s;
    s32 idx;

    g = GetGameData_1fede0();
    if (g == NULL) {
        return 0;
    }
    cnt = 0;
    c = Cosf_128d30(D_0047D3B8 * (f32)arg0->m770);
    arg0->m778 = 1.0f;
    if (arg0->m772 != 0 && arg0->h != 0) {
        e = UiFindWidget_290460(arg0->h, 0xB5);
        if (e != NULL) {
            s = e->m20;
            if (s != NULL) {
                s->m4 = (s32)(42.0f + 42.0f * c);
                s->m6 = (s32)(46.0f + 46.0f * c);
                UiSetWidgetAlpha_2907a0(arg0->h, 0xB5, D_0047D248 - D_0047D288 * c);
                if (s->m4 < 0x21) {
                    s->m4 = 0x20;
                    cnt++;
                }
                if (s->m6 < 0x25) {
                    s->m6 = 0x24;
                    cnt++;
                }
            }
        }
    }
    if (cnt == 2) {
        if (arg0->h != 0) {
            e = UiFindWidget_290460(arg0->h, 0x58);
            if (e != NULL && e->m20 != NULL && arg0->m4 != 0) {
            { u32 r = RevelationBoardGetCells_3eb510(g, arg0->mC); idx = ((s64)arg0->m4 - (s64)r) / 4; }
            UiSetWidgetsVisibleById_291110(arg0->h, 0x58, 1, 1);
            UiSetWidgetPos_290f60(arg0->h, 0x58, idx % 26 * 42 + 5, idx / 26 * 46 + 1);
            UiSetWidgetAlpha_2907a0(arg0->h, 0x58, 0.0f);
            }
        }
        return 1;
    }
    return 0;
}
