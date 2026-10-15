#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4 __attribute__((aligned(16)));

extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);
extern void CameraVecFromEye_15cda0(V4 *, V4 *);
extern s32 ProjectDepth_15d0a0(f32);
extern s32 ProjectToScreenOffset_15d160(V4 *, V4 *);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GetDrawCtx_15de80(void);
extern void SunGlareFanDrawMaybe_17af60(V4 *, V4 *, s32);
extern void SunFlareDrawQuadsMaybe_17b390(V4 *, V4 *, s32, s32, s32);
extern void TimeOfDaySunWeights_18d600(u8 *, V4 *);
extern void SceneGetSunPos_1c4fc0(u8 *, V4 *, s32);
extern u8 *ObjRecGetLiveObject_1c5250(u8 *, s32);
extern u8 D_0045B0C0[];
extern V4 D_0044B2F0[4];
extern V4 D_0047E2E0 __attribute__((section(".sdata")));

void SunFlareDraw_1cf240(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    V4 s;
    V4 v;
    V4 a;
    V4 b;
    V4 c;
    u8 *e;
    s32 i;
    s32 k;
    f32 t;
    s32 ctx;
    s32 st;

    e = ObjRecGetLiveObject_1c5250(arg0, *(s32 *)(arg0 + 0x434C));
    if (e == 0) {
        return;
    }
    if (*(s32 *)(e + 0x200) == 0 || *(s32 *)(e + 0x20C) == 0) {
        return;
    }
    TimeOfDaySunWeights_18d600(e, &s);
    if (s.x != 0.0f || s.y != 0.0f || s.w != 0.0f) {
        v = D_0047E2E0;
        for (i = 0; i < 4; i++) {
            v.x = 0.0f + v.x + D_0044B2F0[i].x * *(f32 *)((u32)&(&s.x)[i]);
            v.y = 0.0f + v.y + D_0044B2F0[i].y * *(f32 *)((u32)&(&s.x)[i]);
            v.z = 0.0f + v.z + D_0044B2F0[i].z * *(f32 *)((u32)&(&s.x)[i]);
        }
        SceneGetSunPos_1c4fc0(arg0, &a, i);
        a.w = 1.0f;
        if (ProjectToScreenOffset_15d160(&b, &a) != 0) {
            k = 10000;
            *(s32 *)&b.z = ProjectDepth_15d0a0((f32)k);
            SunFlareDrawQuadsMaybe_17b390(&b, &v, arg1, arg2, arg3);
        }
        k = *(s32 *)(arg0 + 0x59DC);
        if (k < 0) {
            if (*(f32 *)(arg0 + 0x59D8) < 0.0f) {
                *(f32 *)(arg0 + 0x59D0) = 0.0f;
            }
            if (*(f32 *)(arg0 + 0x59D8) > 0.0f) {
                *(f32 *)(arg0 + 0x59D0) = *(f32 *)(arg0 + 0x59D4);
            }
            *(s32 *)(arg0 + 0x59D8) = 0;
        } else {
            *(s32 *)(arg0 + 0x59DC) = k - 1;
            *(f32 *)(arg0 + 0x59D0) += *(f32 *)(arg0 + 0x59D8);
            if (*(f32 *)(arg0 + 0x59D0) < 0.0f) {
                *(f32 *)(arg0 + 0x59D0) = 0.0f;
            }
            if (!(*(f32 *)(arg0 + 0x59D0) <= *(f32 *)(arg0 + 0x59D4))) {
                *(f32 *)(arg0 + 0x59D0) = *(f32 *)(arg0 + 0x59D4);
            }
        }
        CameraVecFromEye_15cda0(&c, &a);
        v.w = *(f32 *)(arg0 + 0x59D0);
        ctx = GetDrawCtx_15de80();
        st = GetDrawCtxNameTable_15de40();
        DrawListAddTexLoad_1418c0(ctx, 0x31C, 1.0f);
        SunGlareFanDrawMaybe_17af60(&c, &v, NameTableFindByName_159fb0(st, D_0045B0C0, 0x31C));
    }
}
