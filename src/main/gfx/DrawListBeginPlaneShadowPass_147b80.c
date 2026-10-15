#include "types.h"


typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4_147;

typedef struct {
    V4_147 r[3];
} M34_147;

typedef struct {
    s32 a50;
    s32 a54;
    s32 a58;
    s32 a5C;
    s32 a60;
    s32 a64;
    s32 a68;
    s32 a6C;
    s32 a70;
    s32 a74;
    s32 a78;
    s32 a7C;
    s32 a80;
} P147;

typedef struct {
    u16 lo : 4;
    u16 mid : 6;
    u16 hi : 6;
} BF147;

extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktSetZTest_13e450(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktDrawSprite_13ea30(s32, P147 *);
extern void GsPktCommit_13f190(s32);
extern void GsPktOpen_13f4a0(s32);
extern void DrawListEndPrim_141a20(u8 *);
extern s32 DrawListBeginPrim_141b00(u8 *);
extern void DmaPktAddCallTag_141b80(u8 *, s32);
extern void DrawListAddEnv_1421d0(u8 *);
extern u8 *DrawListGetCurBuf_142790(void);
extern void ViewReapplyCameraRec_142e90(u8 *);
extern void DrawEnvPush_144830(u8 *);
extern void DrawEnvSetZbufFromDesc_144f70(u8 *, u8 *, u16);
extern void DrawEnvSetFrameFromDesc_144fe0(u8 *, u8 *, s32);
extern s32 DrawEnvGetHeight_1451d0(u8 *);
extern s32 DrawEnvGetWidth_1451e0(u8 *);
extern s32 DrawPktBuildPlaneShadowMtx_147eb0(u8 *, s32, u8 *, s32);
extern void MemStackAllocQw_14d950(u8 *, s32);
extern void NameTableCopyNode_15ad70(u8 *, u8 *);

void DrawListBeginPlaneShadowPass_147b80(u8 *arg0, u8 *arg1)
{
    P147 prm;
    u8 *h;
    s32 cnt;
    s32 n;
    s32 flag;
    s32 obj;
    u16 old;

    h = DrawListGetCurBuf_142790();
    if (h == 0) {
        return;
    }
    cnt = *(s32 *)(h + 0x28) + (*(s32 *)(h + 0x2C) << 4);
    if (cnt == 0) {
        return;
    }
    n = DrawPktBuildPlaneShadowMtx_147eb0(arg0, cnt, arg1, 1);
    if (n <= 0) {
        return;
    }
    MemStackAllocQw_14d950(h, n);
    DmaPktAddCallTag_141b80(arg0, cnt);
    *(s32 *)(arg0 + 0x3890) = 1;
    ((V4_147 *)(arg0 + 0x38A0))[0] = ((V4_147 *)arg1)[0];
    ((V4_147 *)(arg0 + 0x38A0))[1] = ((V4_147 *)arg1)[1];
    ((V4_147 *)(arg0 + 0x38A0))[2] = ((V4_147 *)arg1)[2];
    NameTableCopyNode_15ad70(arg0 + 0x38D0, arg1 + 0x30);
    NameTableCopyNode_15ad70(arg0 + 0x3938, arg1 + 0x98);
    *(s32 *)(arg0 + 0x39A0) = *(s32 *)(arg1 + 0x100);
    *(s32 *)(arg0 + 0x39A4) = *(s32 *)(arg1 + 0x104);
    *(s32 *)(arg0 + 0x39A8) = *(s32 *)(arg1 + 0x108);
    NameTableCopyNode_15ad70(arg0 + 0x39B0, arg1 + 0x110);
    *(f32 *)(arg0 + 0x3A18) = *(f32 *)(arg1 + 0x178);
    *(V4_147 *)(arg0 + 0x3A20) = *(V4_147 *)(arg1 + 0x180);
    flag = 0;
    if (*(s16 *)(arg1 + 0x32) != DrawEnvGetWidth_1451e0(arg0) || *(s16 *)(arg1 + 0x34) != DrawEnvGetHeight_1451d0(arg0)) {
        flag = 1;
    }
    DrawEnvPush_144830(arg0);
    DrawEnvSetFrameFromDesc_144fe0(arg0, arg1 + 0x30, 0);
    if (flag != 0) {
        old = *(u16 *)(arg1 + 0xD2);
        ((BF147 *)(arg1 + 0xD2))->mid = 0x31;
        DrawEnvSetZbufFromDesc_144f70(arg0, arg1 + 0x98, old);
    }
    ViewReapplyCameraRec_142e90(arg0);
    DrawListAddEnv_1421d0(arg0);
    obj = DrawListBeginPrim_141b00(arg0);
    GsPktSetZWriteMask_13e430(obj, 1);
    GsPktSetZTest_13e450(obj, 0);
    GsPktEnableAlphaTest_13e4d0(obj, 0);
    GsPktSetAlphaBlend_13e500(obj, 0);
    GsPktSetTextured_13e400(obj, 0);
    GsPktOpen_13f4a0(obj);
    prm.a60 = 0;
    prm.a80 = 1;
    prm.a70 = *(s16 *)(arg1 + 0x32) << 4;
    prm.a64 = 0;
    prm.a74 = *(s16 *)(arg1 + 0x34) << 4;
    prm.a58 = prm.a54 = prm.a50 = 0x80;
    prm.a68 = 0;
    prm.a78 = 0;
    prm.a6C = 0;
    prm.a7C = 0;
    prm.a5C = 0;
    GsPktDrawSprite_13ea30(obj, &prm);
    GsPktCommit_13f190(obj);
    DrawListEndPrim_141a20(arg0);
}
