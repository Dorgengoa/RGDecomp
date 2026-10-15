#include "types.h"

extern "C" {
typedef unsigned __int128 u128;
typedef struct V4 { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct M4 { V4 r[4]; } M4;
typedef struct Cmd { s32 type; } Cmd;
typedef struct Obj {
    u8 pad0[8];
    Cmd *l0; s32 f0;
    Cmd *l1; s32 f1;
    Cmd *l2; s32 f2;
    Cmd *l3; s32 f3;
    Cmd *l4; s32 f4;
    Cmd *x30;
    Cmd *x34;
    u8 pad38[0x18];
    V4 pos;
    V4 tgt;
    f32 yaw;
    f32 dy;
    f32 dist;
    s32 x7C;
    s32 x80;
    s32 mode;
    u8 pad88[8];
    V4 offs;
    f32 ang;
    f32 h;
    f32 r;
    char name[0xD4];
    s32 x180;
    u8 pad184[0x1C];
    V4 p1A0;
    V4 p1B0;
} Obj;
typedef struct Ctx { u8 pad[0x4344]; s32 cam; } Ctx;
extern Ctx *D_00481F78;
extern void EventCameraReset_254a90(Obj *);
extern void sceVu0CopyVector(void *, const void *);
extern void VecSub_13be40(V4 *, V4 *, V4 *);
extern void VecAdd_13be20(V4 *, V4 *, V4 *);
extern void VecNormalize_13bd90(V4 *, V4 *);
extern f32 Atan2f_1291a8(f32, f32);
extern f32 VecDistance_13d3d0(V4 *, V4 *);
extern Cmd *EventCameraNodeRelease_254240(Obj *, Cmd *, s32);
extern s32 (*D_0044D5A0[])(Cmd *, Obj *);
extern s32 strcmp(const char *, const char *);
extern char D_0045EDA0[];
extern u8 D_004BDDB0[];
extern s32 EventCastSlotFindFrame_257e30(void *, s32, char *);
extern void FrameGetWorldPos_148f30(s32, V4 *);
extern void FrameCalcWorldMatrix_148ff0(s32, M4 *);
extern void EventCastGetPos_258740(void *, s32, V4 *);
extern void EventCastGetRotation_258610(void *, s32, V4 *);
extern f32 Sinf_128fd0(f32);
extern f32 Cosf_128d30(f32);
extern void MtxMulVec4_10a8c0(V4 *, M4 *, V4 *);
extern f32 D_0047D1FC;
extern f32 D_0047DC20;
extern f32 D_0047DC24;
extern f32 D_0047DC28;
extern f32 D_0047DC2C;
}

class Cam {
public:
    u8 pad[0xC0];
    virtual void v0(V4 *);
    virtual void v1(V4 *);
    virtual void v2(V4 *);
    virtual void v3(V4 *);
    virtual void v4(V4 *);
    virtual void v5(V4 *);
    virtual void v6(V4 *);
    virtual void v7(V4 *);
    virtual void v8(V4 *);
    virtual void v9(V4 *);
    virtual void v10(V4 *);
    virtual void v11(V4 *);
    virtual void v12(V4 *);
    virtual void v13(V4 *);
    virtual void v14(V4 *);
    virtual void v15(V4 *);
    virtual void v16(V4 *);
    virtual void v17(V4 *);
    virtual void v18(V4 *);
    virtual void v19(V4 *);
    virtual void v20(V4 *);
    virtual void v21(V4 *);
    virtual void v22(V4 *);
    virtual void v23(V4 *);
    virtual void v24(V4 *);
    virtual void v25(V4 *);
    virtual void v26(V4 *);
    virtual void v27(V4 *);
    virtual void v28(V4 *);
    virtual void v29(V4 *);
    virtual void v30(V4 *);
    virtual void v31(V4 *);
    virtual void v32(V4 *);
    virtual void v33(V4 *);
    virtual void v34(V4 *);
    virtual void v35(V4 *);
    virtual void v36(V4 *);
    virtual void v37(V4 *);
    virtual void v38(V4 *);
    virtual void v39(V4 *);
    virtual void v40(V4 *);
    virtual void v41(V4 *);
    virtual void v42(V4 *);
    virtual void v43(V4 *);
};

extern "C" Cam *ObjRecGetLiveObject_1c3bc0(Ctx *, s32);

extern "C" void EventCameraUpdate_2544f0(Obj *o)
{
    V4 d;
    V4 n;
    V4 a;
    V4 b;
    V4 r1;
    V4 r2;
    M4 m;
    V4 t;
    Cmd *c;
    s32 *pf;
    s32 k;
    Cmd **pp;
    Cam *cam;
    s32 t0;
    s32 res;
    f32 ang;
    s32 h;

    cam = ObjRecGetLiveObject_1c3bc0(D_00481F78, D_00481F78->cam);
    if (cam == 0) {
        EventCameraReset_254a90(o);
        return;
    }
    cam->v39(&o->pos);
    cam->v40(&o->tgt);
    if (o->x180 != 0) {
        sceVu0CopyVector(&o->pos, &o->p1A0);
        sceVu0CopyVector(&o->tgt, &o->p1B0);
    }
    VecSub_13be40(&d, &o->tgt, &o->pos);
    n.y = 0.0f;
    n.x = d.x;
    n.w = 0.0f;
    n.z = d.z;
    VecNormalize_13bd90(&n, &n);
    o->yaw = Atan2f_1291a8(-n.x, -n.z);
    o->dy = o->pos.y - o->tgt.y;
    sceVu0CopyVector(&a, &o->pos);
    a.y = 0.0f;
    sceVu0CopyVector(&b, &o->tgt);
    b.y = 0.0f;
    o->dist = VecDistance_13d3d0(&a, &b);
    for (k = 0; k < 5; k++) {
        switch (k) {
        case 0: pp = &o->l0; pf = &o->f0; break;
        case 1: pp = &o->l1; pf = &o->f1; break;
        case 2: pp = &o->l2; pf = &o->f2; break;
        case 3: pp = &o->l3; pf = &o->f3; break;
        case 4: pp = &o->l4; pf = &o->f4; break;
        }
        c = *pp;
        while (c != 0) {
            t0 = c->type;
            if (t0 > 0 && t0 < 0x24) {
                res = D_0044D5A0[t0](c, o);
                if (res != 0) {
                    if (res == 1) goto out;
                    if (res == 2) {
                        switch (k) {
                        case 0: c = o->x30; break;
                        case 1: c = o->x34; break;
                        case 2: break;
                        }
                    }
                }
            } else {
                c = 0;
                break;
            }
            c = EventCameraNodeRelease_254240(o, c, k);
        }
    out:
        *pp = c;
        if (c == 0) *pf = 0;
    }
    if (o->x7C != 0) {
        if (strcmp(o->name, D_0045EDA0) != 0) {
            h = EventCastSlotFindFrame_257e30(D_004BDDB0, o->x80, o->name);
            if (h != 0) {
                FrameGetWorldPos_148f30(h, &o->tgt);
            } else {
                EventCastGetPos_258740(D_004BDDB0, o->x80, &o->tgt);
                o->mode = 1;
            }
        } else {
            EventCastGetPos_258740(D_004BDDB0, o->x80, &o->tgt);
        }
        VecAdd_13be20(&o->tgt, &o->tgt, &o->offs);
        ang = o->ang;
        switch (o->mode) {
        case 1:
            EventCastGetRotation_258610(D_004BDDB0, o->x80, &r1);
            ang += r1.y;
            if (ang > D_0047D1FC) {
                ang -= D_0047DC24;
            } else if (ang <= D_0047DC20) {
                ang += D_0047DC24;
            }
        case 0:
        default:
            o->pos.x = o->tgt.x + o->r * Sinf_128fd0(ang);
            o->pos.y = o->h + o->tgt.y;
            o->pos.z = o->tgt.z + o->r * Cosf_128d30(ang);
            break;
        case 2:
            EventCastGetRotation_258610(D_004BDDB0, o->x80, &r2);
            ang += r2.y;
            if (ang > D_0047D1FC) {
                ang -= D_0047DC2C;
            } else if (ang <= D_0047DC28) {
                ang += D_0047DC2C;
            }
            o->pos.x = o->tgt.x + o->r * Sinf_128fd0(ang);
            o->pos.y = o->h + o->tgt.y;
            o->pos.z = o->tgt.z + o->r * Cosf_128d30(ang);
            VecSub_13be40(&o->pos, &o->pos, &o->tgt);
            *(u128 *)&r2 = 0;
            h = EventCastSlotFindFrame_257e30(D_004BDDB0, o->x80, o->name);
            if (h != 0) {
                FrameCalcWorldMatrix_148ff0(h, &m);
                m.r[3].w = 1.0f;
                m.r[3].z = 0.0f;
                m.r[3].y = 0.0f;
                m.r[3].x = 0.0f;
                FrameGetWorldPos_148f30(h, &t);
            }
            MtxMulVec4_10a8c0(&o->tgt, &m, &o->offs);
            VecAdd_13be20(&o->tgt, &o->tgt, &t);
            MtxMulVec4_10a8c0(&o->pos, &m, &o->pos);
            VecAdd_13be20(&o->pos, &o->tgt, &o->pos);
            break;
        }
    }
    cam->v42(&o->pos);
    cam->v43(&o->tgt);
}
