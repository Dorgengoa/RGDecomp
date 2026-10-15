#include "types.h"
#include "vec.h"

extern void VecScale_13be00(Vec4 *, Vec4 *, f32);
extern void EvObjReset_2f9eb0(u8 *);
extern void EvMapObjPartCalcEdgeLengths_3638d0(u8 *);
extern void EvMapObjPartSetRows_363950(u8 *, Vec4 *);
extern void EvMapObjPartInit_364240(u8 *);
extern const f32 D_0047D2B0 __attribute__((section(".sdata")));
extern const f32 D_0047D2B4 __attribute__((section(".sdata")));

void EvMapObjResetMaybe_366f20(u8 *arg0)
{
    Vec4 m[3];

    EvObjReset_2f9eb0(arg0);
    *(s32 *)(arg0 + 0x2F0) = 0;
    *(s16 *)(arg0 + 0x2FA) = 0;
    *(s32 *)(arg0 + 0x2F4) = 0;
    *(s16 *)(arg0 + 0x2FC) = 0;
    m[0].x = 0.0f;
    m[0].y = 0.0f;
    m[0].z = 1.0f;
    m[0].w = 1.0f;
    m[1].x = D_0047D2B0;
    m[1].y = 0.0f;
    m[1].z = -0.5f;
    m[1].w = 1.0f;
    m[2].x = D_0047D2B4;
    m[2].y = 0.0f;
    m[2].z = -0.5f;
    m[2].w = 1.0f;
    VecScale_13be00(&m[0], &m[0], 5.0f);
    VecScale_13be00(&m[1], &m[1], 5.0f);
    VecScale_13be00(&m[2], &m[2], 5.0f);
    EvMapObjPartInit_364240(arg0 + 0xE0);
    EvMapObjPartSetRows_363950(arg0 + 0xE0, m);
    EvMapObjPartCalcEdgeLengths_3638d0(arg0 + 0xE0);
    *(s32 *)(arg0 + 0x228) = 0;
    *(s32 *)(arg0 + 0x220) = 0;
    *(s32 *)(arg0 + 0x224) = 0;
    *(s8 *)(arg0 + 0x304) = 0;
    *(s16 *)(arg0 + 0x300) = 0;
    *(s16 *)(arg0 + 0x302) = 0;
    *(s16 *)(arg0 + 0x2FE) = -1;
    *(s32 *)(arg0 + 0x330) = 0;
    *(s16 *)(arg0 + 0x2F8) = 0;
    *(s32 *)(arg0 + 0x324) = 0;
    *(s32 *)(arg0 + 0x328) = 0;
    *(s16 *)(arg0 + 0x32C) = -1;
    *(s16 *)(arg0 + 0x32E) = -1;
    *(s32 *)(arg0 + 0x338) = -1;
    *(s32 *)(arg0 + 0x314) = 0;
    *(s32 *)(arg0 + 0x318) = 0;
    *(s32 *)(arg0 + 0x31C) = 0;
    *(s32 *)(arg0 + 0x320) = 0;
    *(s8 *)(arg0 + 0x334) = 0;
}
