#pragma peephole off
#pragma opt_propagation off
#include "types.h"

typedef unsigned __int128 u128;

typedef struct {
    u128 m0;
    u128 m10;
    s32 m20;
    s32 m24;
    u8 pad28[0xF0 - 0x28];
    u128 mF0;
    u8 pad100[0x1C0 - 0x100];
} S;

extern void LightStateSetCurrent_142920(s32 arg0, s32 arg1);
extern s32 LightStatePush_1429f0(s32 arg0, s32 *arg1, s32 arg2);
extern void DrawListAddLightPacket_148120(s32 arg0);
extern void LightStateInit_156b50(s32 *arg0);
extern void LightStateSetAmbient_15cb30(S *arg0);
extern void LightStateSetMatrices_15cc00(u8 *arg0, u8 *arg1);
extern s32 GetDrawCtx_15de80(void);
extern s32 ModelObjExDraw_1ad7a0(u8 *arg0);
extern void sceVu0InterVector(u128 *arg0, f32 *arg1, u8 *arg2, f32 arg3);
extern f32 D_0047E1E0;
extern f32 D_0047E1E4;
extern f32 D_0047E1E8;
extern f32 D_0047E1EC;

s32 Character2DrawTintedMaybe_1ae620(u8 *arg0, f32 x, f32 y, f32 z, f32 t)
{
    f32 v[4];
    f32 *qv = v;
    S s;
    s32 h;
    s32 k;
    s32 r;

    qv[0] = D_0047E1E0;
    qv[1] = D_0047E1E4;
    qv[2] = D_0047E1E8;
    qv[3] = D_0047E1EC;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    h = GetDrawCtx_15de80();
    s.m24 = 0;
    s.m20 = -1;
    LightStateInit_156b50(&s.m20);
    k = LightStatePush_1429f0(h, &s.m20, 1);
    LightStateSetMatrices_15cc00(arg0 + 0x630, arg0 + 0x6F0);
    sceVu0InterVector(&s.m10, v, arg0 + 0x5D0, t);
    sceVu0InterVector(&s.m0, v, arg0 + 0x5A0, t);
    s.mF0 = s.m10;
    LightStateSetAmbient_15cb30(&s);
    DrawListAddLightPacket_148120(h);
    r = ModelObjExDraw_1ad7a0(arg0);
    LightStateSetCurrent_142920(h, k);
    return r;
}
