#include "types.h"
#include "vec.h"

typedef struct View {
    s32 x0;
    s32 w;
    s32 h;
    s32 cx;
    s32 cy;
} View;

typedef struct Ent {
    f32 x;
    f32 y;
    f32 z;
    f32 pad0c;
    f32 r;
    s32 pad14;
    s32 on;
    s32 pad1c;
} Ent;

typedef struct Obj {
    s32 active;
    u8 pad04[0x1C];
    u8 x20[0x70];
    Ent ents[20];
} Obj;

typedef struct Mgr {
    u8 pad[0x270];
    View *view;
} Mgr;

typedef struct Pt {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Pt;

void VecAdd_13be20(Vec4 *, s32, Ent *);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktSetTexture_13ec00(s32, void *);
void GsPktWriteAD_13ec80(s32, s32, u64);
void GsPktSetUVFixed_13ed90(s32, s32, s32);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetXYZVecI_13eeb0(s32, Pt *);
void GsPktClose_13f5b0(s32);
void GsPktOpenPrim_13f730(s32, s32);
void DrawListEndPrim_141a20(Mgr *);
s32 DrawListBeginPrim_141b00(Mgr *);
s32 CameraProjectBillboardRect_15cde0(Pt *, Pt *, Vec4 *, s32, f32, f32);
Mgr *GetDrawCtx_15de80(void);

void ParticleSwirlDraw_17d7b0(Obj *obj, s32 arg1, Vec4 *scale) {
    Pt ra;
    Pt rb;
    Vec4 v;
    volatile s32 a1v __attribute__((aligned(16)));
    Mgr *mgr;
    s32 ctx;
    View *view;
    s32 x0;
    s32 y0;
    s32 i;
    Ent *e;
    s32 ax;
    s32 ay;
    s32 bx;
    s32 by;
    f32 r;

    a1v = arg1;
    if (obj->active != 0) {
        mgr = GetDrawCtx_15de80();
        ctx = DrawListBeginPrim_141b00(mgr);
        view = mgr->view;
        GsPktEnableZTest_13e460(ctx, 1);
        GsPktSetZWriteMask_13e430(ctx, 1);
        GsPktSetTextured_13e400(ctx, 1);
        GsPktSetAlphaBlend_13e500(ctx, 1);
        GsPktSetBlendMode_13e4f0(ctx, 1);
        GsPktEnableAlphaTest_13e4d0(ctx, 0);
        GsPktSetOriginMode_13e2f0(ctx, 1);
        GsPktOpenPrim_13f730(ctx, 6);
        GsPktSetTexture_13ec00(ctx, obj->x20);
        GsPktWriteAD_13ec80(ctx, 0x3B, ((u64)0x80 << 32) | 0x80);
        GsPktSetRGBAQ_13ee40(ctx, 0x80, 0x80, 0x80, 0x20);
        x0 = (view->cx - view->w / 2) * 16;
        y0 = (view->cy - view->h / 2) * 16;
        for (i = 0; i < 20; i++) {
            e = &obj->ents[i];
            if (e->on <= 0) {
                continue;
            }
            v.x = e->x * scale->x;
            v.y = e->y * scale->y;
            v.z = e->z * scale->z;
            VecAdd_13be20(&v, a1v, e);
            v.w = 1.0f;
            r = e->r;
            if (CameraProjectBillboardRect_15cde0(&ra, &rb, &v, 0, r * scale->x, r * scale->y) == 0) {
                continue;
            }
            if (ra.x < x0) {
                ra.x = x0;
            }
            if (ra.y < y0) {
                ra.y = y0;
            }
            ax = ra.x - x0 + 0x28;
            ay = ra.y - y0 + 0x28;
            bx = rb.x - x0 - 0x28;
            by = rb.y - y0 - 0x28;
            if (ax < 0) {
                ax = 0;
            }
            if (ay < 0) {
                ay = 0;
            }
            if (bx < 0) {
                bx = 0;
            }
            if (by < 0) {
                by = 0;
            }
            GsPktSetUVFixed_13ed90(ctx, ax, ay);
            GsPktSetXYZVecI_13eeb0(ctx, &ra);
            GsPktSetUVFixed_13ed90(ctx, bx, by);
            GsPktSetXYZVecI_13eeb0(ctx, &rb);
        }
        GsPktClose_13f5b0(ctx);
        DrawListEndPrim_141a20(mgr);
    }
}
