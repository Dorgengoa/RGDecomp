#include "types.h"

typedef f32 Vec[4];

typedef struct {
    s16 h0;
    s16 pad2;
    u8 *p4;
    s32 pad8;
    s32 padC;
    s32 n10;
    s32 pad14;
    s32 pad18;
    s32 n1C;
    f32 f20;
    s32 pad24;
    s32 pad28;
    f32 f2C;
} Obj;

extern void sceVu0CopyVector(f32 *, u8 *);
extern void sceVu0SubVector(f32 *, f32 *, f32 *);
extern void sceVu0ScaleVector(f32 *, f32 *, f32);
extern void sceVu0AddVector(f32 *, f32 *, f32 *);
extern s32 SplineSampleCatmullRom_2d77c0(Vec *, Vec *, s32, s32, s32, s32);
extern void *GetDrawCtx_15de80(void);
extern void *DrawListBeginPrim_141b00(void *);
extern void DrawListEndPrim_141a20(void *);
extern void GsPktSetOriginMode_13e2f0(void *, s32);
extern void GsPktSetTextured_13e400(void *, s32);
extern void GsPktSetAlphaBlend_13e500(void *, s32);
extern void GsPktSetBlendMode_13e4f0(void *, s32);
extern void GsPktEnableAlphaTest_13e4d0(void *, s32);
extern void GsPktSetGouraud_13e3b0(void *, s32);
extern void GsPktSetTexFilter_13e3d0(void *, s32);
extern void GsPktSetZWriteMask_13e430(void *, s32);
extern void GsPktSetFrameMask_13e420(void *, s32);
extern void GsPktEnableZTest_13e460(void *, s32);
extern void GsPktSetUseUV_13e3e0(void *, s32);
extern void GsPktOpenPrim_13f730(void *, s32);
extern void GsPktSetTexture_13ec00(void *, s32);
extern void GsPktSetUV_13ed60(void *, s32, s32);
extern void GsPktSetRGBAQ_13ee40(void *, s32, s32, s32, s32);
extern void GsPktSetXYZVecI_13eeb0(void *, f32 *);
extern void GsPktClose_13f5b0(void *);
extern s32 ProjectToScreen_15d340(f32 *, f32 *);

void SwordTrailDraw_2d7230(Obj *obj, s32 arg1) {
    volatile s32 n;
    f32 scr1[4];
    f32 scr0[4];
    Vec c[512];
    Vec d[512];
    Vec a[64];
    Vec b[64];
    f32 tmp[4];
    u8 *src;
    f32 *pa;
    void *h;
    f32 *pb;
    void *g;
    f32 step;
    f32 t;
    s32 k;
    s32 j;
    f32 *pc;
    s32 i;
    f32 *pd;



    if (obj->h0 != 0 && arg1 != 0 && obj->n10 >= 2) {
    src = obj->p4;
    pa = a[0];
    pb = b[0];
    i = 0;
    while (i < obj->n10) {
        sceVu0CopyVector(pa, src);
        sceVu0CopyVector(pb, src + 0x10);
        pa += 4;
        pb += 4;
        i++;
        src += 0x30;
    }
    n = SplineSampleCatmullRom_2d77c0(c, a, obj->n10, 10, 0, obj->n10);
    n = SplineSampleCatmullRom_2d77c0(d, b, obj->n10, 10, 0, obj->n10);
    n = n - obj->n1C;
    if (n > 0) {
        h = GetDrawCtx_15de80();
        g = DrawListBeginPrim_141b00(h);
        GsPktSetOriginMode_13e2f0(g, 1);
        GsPktSetTextured_13e400(g, 1);
        GsPktSetAlphaBlend_13e500(g, 1);
        GsPktSetBlendMode_13e4f0(g, 2);
        GsPktEnableAlphaTest_13e4d0(g, 1);
        GsPktSetGouraud_13e3b0(g, 1);
        GsPktSetTexFilter_13e3d0(g, 1);
        GsPktSetZWriteMask_13e430(g, 1);
        GsPktSetFrameMask_13e420(g, -1);
        GsPktEnableZTest_13e460(g, 1);
        GsPktSetUseUV_13e3e0(g, 1);
        pc = c[obj->n1C];
        step = 63.0f / n;
        pd = d[obj->n1C];
        t = 0.0f;
        GsPktOpenPrim_13f730(g, 4);
        GsPktSetTexture_13ec00(g, arg1);
        j = 0;
        while (j < n) {
            sceVu0SubVector(tmp, pc, pd);
            sceVu0ScaleVector(tmp, tmp, obj->f2C);
            sceVu0AddVector(pc, pd, tmp);
            if (ProjectToScreen_15d340(scr1, pc) != 0 && ProjectToScreen_15d340(scr0, pd) != 0) {
                k = (s32)t;
                GsPktSetUV_13ed60(g, 0, k);
                GsPktSetRGBAQ_13ee40(g, 0x80, 0x80, 0x80, (s32)(160.0f * obj->f20));
                GsPktSetXYZVecI_13eeb0(g, scr1);
                GsPktSetUV_13ed60(g, 0x3F, k);
                GsPktSetRGBAQ_13ee40(g, 0x80, 0x80, 0x80, (s32)(160.0f * obj->f20));
                GsPktSetXYZVecI_13eeb0(g, scr0);
                t += step;
            }
            j++;
            src += 0x30;
            pc += 4;
            pd += 4;
        }
        GsPktClose_13f5b0(g);
        DrawListEndPrim_141a20(h);
    }
    }
}
