/* rgp:protos */
#define RGP_SELF_SunGlareFanDrawMaybe_17af60 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#pragma optimization_level 3
#include "types.h"
#pragma vu0_mmi_reg_binding on
typedef rg_s128 __attribute__((aligned(4))) rgvb_vz17af60_t; /* rg:vu0bind vf0 */
#define vz17af60 RG_VU0_BIND_VF(0, rgvb_vz17af60_t)


typedef struct V4_17af60 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) V4_17af60;

typedef struct Flags17af60 {
    u8 pad0[0x48];
    u8 a : 2;
    u8 b : 2;
    u8 rest : 4;
} Flags17af60;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D5D0;
extern f32 D_0047D1FC;

void SunGlareFanDrawMaybe_17af60(V4_17af60 *pos, V4_17af60 *col, Flags17af60 *flags)
{ RG_VU0_FRAME;
    V4_17af60 v __attribute__((aligned(16)));
    V4_17af60 pts[12] __attribute__((aligned(16)));
    V4_17af60 saved[12] __attribute__((aligned(16)));
    V4_17af60 m[4] __attribute__((aligned(16)));
    void *g;
    void *h;
    f32 len;
    f32 rot;
    f32 lift;
    f32 one;
    f32 k;
    f32 a;
    f32 w;
    f32 hh;
    s32 alpha;
    s32 j;
    s32 sx;
    s32 sy;
    s32 i;
    V4_17af60 *p;
    f32 *py;

    g = GetDrawCtx_15de80();
    MtxMulDir_13c860(&v, ((u8 *)GetDrawCtxCamera_15de60()) + 0xB0, pos);
    len = VecLengthXZ_13d470(&v);
    lift = -v.z / VecLength_13d4a0(&v);
    rot = 0.0f;
    if (!(len <= 0.0f)) {
        rot = v.x / len;
    }
    if (lift < 0.0f) {
        lift = 0.0f;
    }
    k = D_0047D5D0;
    lift += k;
    one = 1.0f;
    one = (f32)one;
    if (!(lift <= one)) {
        lift = one;
    }
    p = (V4_17af60 *)(s32)(u32)pts;
    p = (V4_17af60 *)(s32)p;
    if (p) { p = (V4_17af60 *)(s32)(u32)p; }
    *(rg_s128 *)p = vz17af60;
    for (i = 0; i < 11; i++) {
        a = D_0047D1FC * ((f32)(i - 1) / 8.0f);
        p = &pts[i];
        p[1].x = Cosf_128d30(a);
        p[1].y = Sinf_128fd0(a);
        p[1].z = 0.0f;
        p[1].w = one;
    }
    MtxIdentity_13d2e0(m);
    sceVu0RotMatrixZ(m, m, rot);
    for (i = 0; i < 12; i++) {
        p = &pts[i];
        *(rg_u128 *)&saved[i] = *(rg_u128 *)p;
        py = &p->y;
        p->x *= 2.0f;
        *py *= 1.5f;
        MtxMulVec4_10a8c0(p, m, p);
        p->x += rot;
        *py -= k;
    }
    h = DrawListBeginPrim_141b00(g);
    GsPktEnableZTest_13e460(h, 0);
    GsPktSetGouraud_13e3b0(h, 1);
    GsPktSetZWriteMask_13e430(h, 1);
    GsPktSetZTest_13e450(h, 0);
    GsPktSetAlphaBlend_13e500(h, 1);
    GsPktSetUseUV_13e3e0(h, 0);
    GsPktSetBlendMode_13e4f0(h, 2);
    GsPktEnableAlphaTest_13e4d0(h, 0);
    GsPktSetTextured_13e400(h, 0);
    if (flags != NULL) {
        GsPktSetTextured_13e400(h, 1);
        flags->a = 0;
        flags->b = 0;
    }
    w = DrawEnvGetWidth_1451e0(g);
    hh = DrawEnvGetHeight_1451d0(g);
    GsPktOpenPrim_13f730(h, 5);
    GsPktSetTexture_13ec00(h, flags);
    alpha = lift * col->w;
    for (j = 0; j < 12; j++) {
        p = &pts[j];
        if (j == 0) {
            GsPktSetRGBAQ_13ee40(h, col->x, col->y, col->z, alpha);
        } else {
            GsPktSetRGBAQ_13ee40(h, col->x, col->y, col->z, 0);
        }
        sx = 16.0f * ((1.0f + p->x) * w / 2.0f);
        sy = 16.0f * (p->y * hh);
        GsPktSetST_13ed10(h, (1.0f + p->x) / 2.0f, p->y, 1.0f);
        GsPktSetXYZ_13ef10(h, sx, sy, 0);
    }
    GsPktClose_13f5b0(h);
    DrawListEndPrim_141a20(g);
}
