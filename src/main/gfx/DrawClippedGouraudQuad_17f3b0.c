#include "types.h"
typedef unsigned __int128 u128;


typedef struct Vec4 {
    f32 v[4];
} __attribute__((aligned(16))) Vec4;
typedef struct Mtx {
    Vec4 r[4];
} Mtx;

extern void VecScale_13be00(Vec4 *, Vec4 *, f32);
extern void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern void MtxMulPoint_13c890(Vec4 *, Mtx *, Vec4 *);
extern void MtxProjectPoint_13c8c0(Vec4 *, u8 *, Vec4 *);
extern void MtxMul_13d240(Mtx *, u8 *, u8 *);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktSetZTest_13e450(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetRGBAQVec_13edd0(s32, Vec4 *);
extern void GsPktSetXYZfVec_13efe0(s32, Vec4 *);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void DrawListEndPrim_141a20(u8 *);
extern s32 DrawListBeginPrim_141b00(u8 *);
extern u8 *GetDrawCtx_15de80();
extern f32 D_0047E000;
extern f32 D_0047E004;

void DrawClippedGouraudQuad_17f3b0(Vec4 *in, Vec4 *uv) {
    s32 cnt[2]; Mtx mtx; Vec4 tv[4]; Vec4 pos[2][12]; Vec4 tex[2][12]; Vec4 P0; Vec4 T0; Vec4 P1; Vec4 T1; Vec4 D1; Vec4 D2; u8 nxt; u8 in0; s32 i; s32 tt; s32 k; u8 in1; s32 *po; s32 n; s32 cur; s32 cross; s32 j1; Vec4 *ft; s32 *pn; Vec4 *fp; s32 ax; s32 side; f32 t; s32 j; f32 *pa; Vec4 *srct; f32 sg; u8 *cam; f32 *pb; Vec4 *dstt; s32 h; f32 *pd; Vec4 *dst; Vec4 *src; u8 *obj;

    cam = GetDrawCtx_15de80();
    obj = *(u8 **)(cam + 0xF20);
    MtxMul_13d240(&mtx, obj + 0xF0, obj + 0xB0);
    for (i = 0; i < 4; i++) {
        MtxMulPoint_13c890(&tv[i], &mtx, &in[i]);
    }
    *(f32 *)&cnt[0] = D_0047E000;
    cur = 0;
    *(f32 *)&cnt[1] = D_0047E004;
    for (i = 0; i < 4; i++) {
        *(u128 *)&pos[0][i] = *(u128 *)&tv[i];
        *(u128 *)&tex[0][i] = *(u128 *)&uv[i];
    }
    *(u128 *)&pos[0][4] = *(u128 *)&tv[0];
    *(u128 *)&tex[0][4] = *(u128 *)&uv[0];
    for (ax = 0; ax < 2; ax++) {
        pa = &P0.v[ax];
        pb = &P1.v[ax];
        pd = &D1.v[ax];
        for (side = 0; side < 2; side++) {
            sg = 1.0f;
            if (side != 0) {
                sg = -1.0f;
            }
            pn = &cnt[cur];
            nxt = (cur != 0) ^ 1;
            j = 0;
            po = &cnt[nxt];
            *po = 0;
            src = pos[cur];
            srct = tex[cur];
            dst = pos[nxt];
            dstt = tex[nxt];
            for (j = 0; j < *pn; j++) {
                j1 = j + 1;
                P0 = src[j];
                P1 = src[j1];
                T0 = srct[j];
                T1 = srct[j1];
                if (sg > 0.0f) {
                    in0 = *pa < P0.v[3];
                    in1 = *pb < P1.v[3];
                } else {
                    in0 = *pa > -P0.v[3];
                    in1 = *pb > -P1.v[3];
                }
                cross = 0;
                if (in0) {
                    *(u128 *)&dst[*po] = *(u128 *)&P0;
                    *(u128 *)&dstt[*po] = *(u128 *)&T0;
                    (*po)++;
                    if (!in1) cross = 1;
                } else if (in1) {
                    cross = 1;
                }
                if (cross) {
                    VecSub_13be40(&D1, &P1, &P0);
                    VecSub_13be40(&D2, &T1, &T0);
                    t = sg * (*pa - sg * P0.v[3]) / (D1.v[3] - sg * *pd);
                    VecScale_13be00(&D1, &D1, t);
                    VecScale_13be00(&D2, &D2, t);
                    VecAdd_13be20(&dst[*po], &P0, &D1);
                    VecAdd_13be20(&dstt[*po], &T0, &D2);
                    *po = *po + 1;
                }
            }
            *(u128 *)&dst[*po] = *(u128 *)&dst[0];
            *(u128 *)&dstt[*po] = *(u128 *)&dstt[0];
            cur = nxt;
        }
    }
    n = cnt[cur];
    fp = pos[cur];
    ft = tex[cur];
    if (n < 3) return;
    h = DrawListBeginPrim_141b00(cam);
    GsPktEnableZTest_13e460(h, 0);
    GsPktSetZWriteMask_13e430(h, 1);
    GsPktSetGouraud_13e3b0(h, 1);
    GsPktSetZTest_13e450(h, 0);
    GsPktSetTextured_13e400(h, 0);
    GsPktSetAlphaBlend_13e500(h, 0);
    GsPktEnableAlphaTest_13e4d0(h, 0);
    GsPktSetOriginMode_13e2f0(h, 1);
    GsPktOpenPrim_13f730(h, 5);
    for (i = 0; i < n; i++) {
        GsPktSetRGBAQVec_13edd0(h, &ft[i]);
        MtxProjectPoint_13c8c0(&fp[i], obj + 0x130, &fp[i]);
        GsPktSetXYZfVec_13efe0(h, &fp[i]);
    }
    GsPktClose_13f5b0(h);
    DrawListEndPrim_141a20(cam);
}
