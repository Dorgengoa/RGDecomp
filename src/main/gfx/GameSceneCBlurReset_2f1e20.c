#include "types.h"
extern void *GetCurrentScene_1f5be0(void);
extern s32 SysModeMsgIsKeyCapWarpStartMaybe_27bc40(void);
extern void ColorFromRgba128_1ce5f0(void *, s32, s32, s32, s32);
extern f32 D_0047D470;
void GameSceneCBlurReset_2f1e20(void)
{
    u8 *o;
    u8 *q;
    s32 v;

    o = GetCurrentScene_1f5be0();
    *(f32 *)(o + 0x5930) = D_0047D470;
    v = -0x20;
    if (SysModeMsgIsKeyCapWarpStartMaybe_27bc40() != 0) {
        v = 0;
    }
    q = o + 0x58A0;
    ColorFromRgba128_1ce5f0(q, 0x80, 0x80, 0x80, 0x80);
    *(s16 *)(q + 0x12) = 1;
    *(u8 *)(q + 0x11) = 0;
    *(s16 *)(q + 0x14) = 0;
    *(s16 *)(q + 0x16) = v;
}
