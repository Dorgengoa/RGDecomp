#include "types.h"
#pragma optimization_level 3

typedef struct Vec4 {
    f32 x, y, z, w;
} Vec4;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct Mdl {
    s32 x0;
    u8 pad4[0x11C];
    u8 anim[0x50];
    f32 alpha;
    u8 pad174[0x4C];
} Mdl;

typedef struct Group {
    Mdl m[4];
    f32 f[4];
    u8 pad[0x10];
} Group;

typedef struct Obj {
    s32 x0;
    u8 pad4[0xC];
    Group g[3];
} Obj;

void *GetDrawCtx_15de80(void);
void LightStateGetAmbient_15cb10(void *);
void DrawListAddTexLoad_1418c0(void *, s32, f32);
void ModelSetScale_150ff0(Mdl *, Vec4 *);
void ModelSetPos_151110(Mdl *, void *);
void ModelSetRot_151080(Mdl *, Vec4 *);
void ModelDraw_14f6d0(Mdl *, void *, void *);
extern Vec4 D_0047DFF0 __attribute__((section(".sdata")));

static inline void setv(Vec4 *v, f32 x, f32 y, f32 z) {
    *v = *(Vec4 *)&D_0047DFF0;
    v->x = x;
    v->y = y;
    v->z = z;
}

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 0x10; if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

void MapSkyDrawLayers_17e760(Obj *a, Vec3 *p1, Vec3 *p2, Vec3 *p3, s32 idx, f32 *volatile al1, f32 *al2) {
    void *r;
    s32 i;
    f32 *ap;
    Mdl *m;
    void *an;
    f32 f;
    u8 o1[0x10];
    u8 o2[0x10];

    if (idx < 0 || idx >= 4) return;
    r = GetDrawCtx_15de80();
    LightStateGetAmbient_15cb10(o1);
    LightStateGetAmbient_15cb10(o2);
    for (i = 0; i < 4; i++) {
        ap = &al1[i];
        if (*ap <= 0.0f) continue;
        if (a->g[1].m[i].x0 == 0) continue;
        DrawListAddTexLoad_1418c0(r, *(s32 *)&a->g[2].f[i], 1.0f);
        a->g[1].m[i].alpha = *ap;
        { Vec4 sc1 = {0};
        m = &a->g[1].m[i];
        sc1.x = 1.0f;
        sc1.y = 1.0f;
        sc1.z = 1.0f;
        ModelSetScale_150ff0(m, &sc1);
        { Vec4 pos1;
        setv(&pos1, p1->x, p1->y, p1->z);
        ModelSetPos_151110(m, &pos1);
        f = a->g[1].f[i];
        { Vec4 rot1 = {0};
        rot1.x = 0.0f;
        rot1.y = f;
        rot1.z = 0.0f;
        ModelSetRot_151080(m, &rot1);
        an = a->g[1].m[i].anim;
        ModelDraw_14f6d0(m, r, an);
        if (a->x0 == 0) continue;
        { Vec4 sn1 = {0};
        sn1.x = 1.0f;
        sn1.y = -1.0f;
        sn1.z = 1.0f;
        m = (Mdl *)((u8 *)a + (((i << 3) - i) << 6) + 0x730);
        ModelSetScale_150ff0(m, &sn1);
        ModelDraw_14f6d0(m, r, an);
        } } } }
    }
    if (al1[2] <= 0.0f) {
        for (i = 0; i < 4; i++) {
            ap = &al2[i];
            if (*ap <= 0.0f) continue;
            if (a->g[2].m[i].x0 == 0) continue;
            DrawListAddTexLoad_1418c0(r, *(s32 *)&a->g[2].f[i], 1.0f);
            a->g[2].m[i].alpha = *ap;
            m = &a->g[2].m[i];
            ModelSetPos_151110(m, p2);
            an = a->g[2].m[i].anim;
            ModelDraw_14f6d0(m, r, an);
            if (a->x0 == 0) continue;
            if (i == 2) continue;
            if (p2->y <= 0.0f) continue;
            { Vec4 v2;
            setv(&v2, p2->x, -p2->y, p2->z);
            m = (Mdl *)((u8 *)a + (((i << 3) - i) << 6) + 0xE50);
            ModelSetPos_151110(m, &v2);
            ModelDraw_14f6d0(m, r, an);
            }
        }
    }
    if (!(al1[2] <= 0.0f)) {
        for (i = 0; i < 4; i++) {
            ap = &al2[i];
            if (*ap <= 0.0f) continue;
            if (a->g[2].m[i].x0 == 0) continue;
            DrawListAddTexLoad_1418c0(r, *(s32 *)&a->g[2].f[i], 1.0f);
            a->g[2].m[i].alpha = *ap;
            m = &a->g[2].m[i];
            ModelSetPos_151110(m, p3);
            an = a->g[2].m[i].anim;
            ModelDraw_14f6d0(m, r, an);
            if (a->x0 == 0) continue;
            if (i == 2) continue;
            if (p3->y <= 0.0f) continue;
            { Vec4 v3;
            setv(&v3, p3->x, -p3->y, p3->z);
            m = (Mdl *)((u8 *)a + (((i << 3) - i) << 6) + 0xE50);
            ModelSetPos_151110(m, &v3);
            ModelDraw_14f6d0(m, r, an);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        ap = &al1[i];
        if (*ap <= 0.0f) continue;
        if (a->g[0].m[i].x0 == 0) continue;
        a->g[0].m[i].alpha = *ap;
        DrawListAddTexLoad_1418c0(r, *(s32 *)&a->g[2].f[i], 1.0f);
        { Vec4 sc4 = {0};
        m = &a->g[0].m[i];
        sc4.x = 1.0f;
        sc4.y = 1.0f;
        sc4.z = 1.0f;
        ModelSetScale_150ff0(m, &sc4);
        { Vec4 pos4;
        setv(&pos4, p1->x, p1->y, p1->z);
        ModelSetPos_151110(m, &pos4);
        f = a->g[0].f[i];
        { Vec4 rot4 = {0};
        rot4.x = 0.0f;
        rot4.y = f;
        rot4.z = 0.0f;
        ModelSetRot_151080(m, &rot4);
        an = a->g[0].m[i].anim;
        ModelDraw_14f6d0(m, r, an);
        if (a->x0 == 0) continue;
        { Vec4 sn4 = {0};
        sn4.x = 1.0f;
        sn4.y = -1.0f;
        sn4.z = 1.0f;
        m = (Mdl *)((u8 *)a + (((i << 3) - i) << 6) + 0x10);
        ModelSetScale_150ff0(m, &sn4);
        ModelDraw_14f6d0(m, r, an);
        } } } }
    }
}
