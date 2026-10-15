#include "types.h"

extern f32 Sinf_128fd0(f32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern f32 GetSceneTimeStep_293350(s32);
extern const f32 D_0047D1FC __attribute__((section(".sdata")));
extern f32 D_0047D34C;
extern f32 D_0047D240;
extern f32 D_0047D440;

typedef struct {
    u8 pad0[0x24C];
    f32 unk24C;
    u8 pad250[0x274 - 0x250];
    s32 unk274;
    u8 pad278[0x284 - 0x278];
    s32 unk284;
} T;

void MenuCatalogTab1BlinkUpdate_35ddf0(T *arg0)
{
    f32 temp_f0;
    s32 temp_4;

    temp_4 = arg0->unk284;
    if (temp_4 == 1) {
        temp_f0 = arg0->unk24C + D_0047D34C * GetSceneTimeStep_293350(temp_4);
        arg0->unk24C = temp_f0;
        if (!(temp_f0 <= D_0047D1FC)) {
            arg0->unk24C = 0.0f;
        }
        UiSetWidgetAlpha_2907a0(arg0->unk274, 0x1F1, D_0047D240 + D_0047D440 * Sinf_128fd0(arg0->unk24C));
    }
}
