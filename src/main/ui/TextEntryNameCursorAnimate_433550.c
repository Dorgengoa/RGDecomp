#include "types.h"

typedef struct T433550 {
    void *m00;
    u8 pad04[0x10];
    f32 m14;
    u8 pad18[0x8];
    f32 m20;
    f32 m24;
} T433550;

extern const f32 D_0047D3E4 __attribute__((section(".sdata")));
extern void UiGetWidgetPos_2910a0(void *o, s32 k, s32 *ox, s32 *oy);
extern void PhaseAdvanceWrapPi_28b630(f32 *v, f32 t);
extern f32 Sinf_128fd0(f32 t);
extern void UiSetWidgetColor_2905b0(void *o, s32 k, f32 r, f32 g, f32 b, f32 a);
extern void UiSetWidgetPos_290f60(void *o, s32 k, s32 x, s32 y);
extern void UiMoveWidgetUniform_290f50(void *o, s32 k, s32 x, s32 y, s32 z, f32 s);

s32 TextEntryNameCursorAnimate_433550(T433550 *p, s16 *q)
{
    s32 ox;
    s32 oy;
    f32 t;
    s32 x;
    s32 y;
    f32 c;

    UiGetWidgetPos_2910a0(p->m00, 2, &ox, &oy);
    PhaseAdvanceWrapPi_28b630(&p->m14, p->m20);
    t = Sinf_128fd0(p->m14);
    c = D_0047D3E4 + (1.0f + t) / 2.0f;
    x = ox + (q[0] + q[8] * q[2]);
    y = oy + (q[1] + q[9] * q[3]);
    UiSetWidgetColor_2905b0(p->m00, 7, c, c, c, -1.0f);
    UiSetWidgetPos_290f60(p->m00, 7, x, y);
    UiMoveWidgetUniform_290f50(p->m00, 0xD, (s32)((f32)x + (4.0f * t - 12.0f)), y + 2, 0,
                 p->m24);
    return 1;
}
