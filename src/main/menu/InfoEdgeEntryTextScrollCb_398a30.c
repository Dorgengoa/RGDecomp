#include "types.h"

extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, f32, s32);
extern const volatile f32 D_0047D460 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_00483594;

typedef struct {
    u8 pad0[0x6];
    s16 unk6;
    u8 pad8[0xa];
    s16 unk12;
} T398a30_arg0;

s32 InfoEdgeEntryTextScrollCb_398a30(T398a30_arg0 *arg0) {
    UiMoveWidgetUniform_290f50(D_00482360, 0x21B, 0, (s32)((f32)arg0->unk12 * D_00483594), D_0047D460, 0);
    UiMoveWidgetUniform_290f50(D_00482360, 0x215, 0, arg0->unk12 * -arg0->unk6, D_0047D460, 0);
    return 1;
}
