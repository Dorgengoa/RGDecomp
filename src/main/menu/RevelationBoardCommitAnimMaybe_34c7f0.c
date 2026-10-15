#include "types.h"

extern f32 Sinf_128fd0(f32);
extern void *UiFindWidget_290460(s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);

extern const f32 D_0047D278 __attribute__((section(".sdata")));
extern f32 D_0047D35C;
extern const volatile f32 D_0047D400 __attribute__((section(".sdata")));
extern f32 D_0047D628;
extern f32 D_0047D63C;

typedef struct { s32 h; u8 pad4[0x770 - 4]; s16 m770; u8 pad772[6]; f32 m778; } O34c7f0;
typedef struct { u8 pad[4]; s16 x; s16 y; } Box;
typedef struct { u8 pad[0x20]; Box *box; } Item;

static inline f32 Min(f32 a, f32 b) { return (a < b) ? a : b; }
s32 RevelationBoardCommitAnimMaybe_34c7f0(O34c7f0 *arg0)
{
    f32 a;
    f32 b;
    f32 c;
    f32 s;
    f32 t;
    s16 lv;
    Item *it;
    Box *bx;

    t = Sinf_128fd0(D_0047D400 * (f32)(arg0->m770 * 2));
    b = 1.0f;
    if ((f32)(lv = arg0->m770) < 7.5f) {
        b = Sinf_128fd0(D_0047D400 * (f32)(lv * 4));
    }
    a = 1.0f + t;
    c = a;
    if (!(a < D_0047D35C)) {
        c = D_0047D35C;
    }

    UiSetWidgetsVisibleById_291110(arg0->h, 0x58, 1, 1);
    UiSetWidgetColor_2905b0(arg0->h, 0x58, c, c, c, b);
    lv = arg0->m770;
    if (lv >= 0 && lv < 6) {
        UiSetWidgetsVisibleById_291110(arg0->h, 0x59, 1, 1);
        it = (Item *)UiFindWidget_290460(arg0->h, 0x59);
        if (it != 0) {
            bx = it->box;
            if (bx != 0) {
                s = 2.0f * Sinf_128fd0(D_0047D63C * (f32)arg0->m770);
                if (!(a <= D_0047D35C)) {
                    a = D_0047D35C;
                }

                bx->x = 34.0f * s;
                bx->y = 38.0f * s;
                { f32 lim = D_0047D278; if (!(s < lim)) s = lim; }
                UiSetWidgetColor_2905b0(arg0->h, 0x59, a, a, a, s);
            }
        }
    } else if (lv > 5) {
        UiFadeWidgetAlpha_290690(arg0->h, 0x59, 0.0f, D_0047D628, -1.0f);
    }
    arg0->m778 = 1.0f;
    return (u8)(arg0->m770 >= 0x1D);
}
