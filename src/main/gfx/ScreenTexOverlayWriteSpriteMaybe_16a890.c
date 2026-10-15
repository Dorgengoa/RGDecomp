#include "types.h"
#pragma opt_propagation off

typedef unsigned __int128 u128;

extern void GsPktRawWriteEndStubMaybe_13f1e0(s32);
extern u128 *GsPktReserveQwords_13f230(s32, s32);
extern void GsPktRawWriteBeginStubMaybe_13f250(s32);
extern s32 DrawEnvGetCenterY_145120(s32);
extern s32 DrawEnvGetCenterX_145130(s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);

#define I(p, n) (((s32 *)(p))[n])
#define F(p, n) (((f32 *)(p))[n])

void ScreenTexOverlayWriteSpriteMaybe_16a890(s32 arg0, s32 *arg1, s32 *arg2)
{
    s32 sess;
    s32 dxW;
    s32 dxH;
    s32 dyW;
    s32 dyH;
    u128 *pk;
    u128 *start;
    u128 *end;
    s32 n;

    sess = GetDrawCtx_15de80();
    dxW = DrawEnvGetCenterX_145130(sess) * 16;
    dxH = DrawEnvGetCenterY_145120(sess) * 16;
    dyW = -dxW + DrawEnvGetWidth_1451e0(sess) * 8;
    dyH = -dxH + DrawEnvGetHeight_1451d0(sess) * 8;
    GsPktRawWriteBeginStubMaybe_13f250(arg0);
    pk = GsPktReserveQwords_13f230(arg0, 0);
    pk[0] = 0;
    I(pk, 2) = 0x01000101;
    start = pk + 1;
    n = arg1[1] + dxW;
    F(pk, 4) = (f32)n / 16.0f;
    F(pk, 5) = (f32)(arg1[0] + dxH) / 16.0f;
    F(pk, 8) = (f32)(arg1[3] + dxW) / 16.0f;
    F(pk, 9) = (f32)(arg1[2] + dxH) / 16.0f;
    F(pk, 12) = (f32)dyW / 16.0f;
    F(pk, 13) = (f32)dyH / 16.0f;
    F(pk, 16) = (f32)arg2[0] / 16.0f;
    F(pk, 17) = (f32)arg2[1] / 16.0f;
    I(pk, 20) = 0x8001;
    I(pk, 21) = 0x40000000;
    I(pk, 22) = 0x4343;
    I(pk, 23) = 0;
    I(pk, 3) = ((((u8 *)(pk + 6) - (u8 *)start) / 16) << 16) | 0x6C00008C;
    pk[6] = 0;
    I(pk, 24) = 0x1400012C;
    I(pk, 27) = 0x11000000;
    end = pk + 7;
    I(pk, 0) = (((u8 *)end - (u8 *)start) / 16) | 0x10000000;
    n = 112;
    GsPktReserveQwords_13f230(arg0, n / 16);
    GsPktRawWriteEndStubMaybe_13f1e0(arg0);
}
