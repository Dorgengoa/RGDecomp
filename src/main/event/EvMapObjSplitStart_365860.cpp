#include "types.h"
#pragma optimization_level 3

typedef unsigned int u128 __attribute__((mode(TI)));
typedef union { u128 q; struct { f32 x, y, z, w; } f; } V4;
typedef struct { f32 x, y, z, w; } F4;
typedef struct { f32 f[4]; } FA4;
typedef struct { s32 w[12]; } W12;
typedef struct { s16 h[10]; } H10;

typedef struct {
    W12 a;
    FA4 v;
    H10 s;
    s32 x54;
    s32 pad[2];
} Ent;

typedef struct {
    V4 col;
    f32 x, y, z;
    u8 pad1C[0x24];
} Vtx;

typedef struct {
    u8 pad0[0x10];
    Vtx v[3];
    u8 padD0[0x134 - 0xD0];
    f32 r;
} Prim;

typedef struct {
    u8 pad0[0x150];
} Node;

class Pick {
public:
    u8 pad0[0xB0];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void GetPos(V4 *);
    u8 padB4[2];
    s16 fB6;
};

class Draw {
public:
    u8 pad0[0x68];
    virtual void v0();
    virtual void v1();
    virtual void Begin();
    virtual void End();
};

typedef struct {
    u8 pad0[0x6C];
    s32 f6C;
} Mdl;

typedef struct {
    u8 pad0[0xA0];
    u8 fA0[0x30];
    s32 fD0;
    u8 padD4[0xC];
    u8 fE0[0xF0];
    V4 pos;
    u8 pad1E0[0x50];
    Ent ent[2];
    u8 pad2F0[4];
    Node *list;
    s16 nEnt;
    u8 pad2FA[2];
    s16 nList;
    u8 pad2FE[2];
    s16 f300;
    s16 f302;
    char name[0x2C];
    s32 mode;
    u8 pad334[4];
    s32 id;
} Self;

extern "C" {
void VecScale_13be00(void *, void *, f32);
void VecAdd_13be20(void *, void *, void *);
void VecSub_13be40(void *, void *, void *);
s32 ModelFindFrameIndexByName_151220(s32, s32);
void ModelGetFrameMeshBounds_151f60(s32, void *, s32, s32);
void MtxStore3x4_186390(Draw *, void *);
void NodeGetTranslation_186650(Draw *, void *);
void VecScaleToLength_1cb510(void *, void *, f32);
void MatMulVec4Args_1cb7f0(void *, void *, f32, f32, f32, f32);
void VecCross_1cb9f0(void *, void *, void *);
void VecNormalize_1cbb80(void *, void *);
void VecScale_1cbca0(void *, void *, f32);
void VecSub_1cbd00(void *, void *, void *);
void VecCopy_1cbe30(void *, void *);
void MatIdentity_1cbe40(void *);
void GameSceneSoundSlot5PlaySe_1d05a0(s32, s32);
s32 GetCurrentScene_1f5be0(void);
s32 MapEvCollectCollTrisNearMaybe_1ff130(void *, s32, void *, void *, s32, f32);
void EffectSpawnHitBulletAlt_2d7e00(s32, V4 *);
Draw *TargetRefGetMapObj_2e7050(void *);
s32 GetObjRefTable_313de0(void);
Pick *HandleRegistryLookup_314aa0(s32, s32);
void EvMapObjPartClipEdgesToColl_3636e0(Prim *, void *, s32);
void EvMapObjPartCalcRadiusMaybe_363850(Prim *, s32);
void EvMapObjPartCalcEdgeLengths_3638d0(Prim *);
void EvMapObjPartSetRows_363950(Prim *, void *);
void EvMapObjPartCalcMatrix_363a70(void *, void *);
void EvMapObjPartInitFromFrame_363f90(Prim *, s32 *);
void EvMapObjPartClear_3641f0(Prim *);
s32 EvMapObjGetBreakSe_366b40(Self *);
f32 EvMapObjGetRadiusMaybe_366b60(Self *);
s32 EvMapObjGetId_366b70(Self *);
s32 EvMapObjGetMode_366b80(Self *);
Mdl *EvMapObjGetModel_366bb0(Self *);
Prim *EvMapObjNodeGetPart_3673c0(Node *);
s32 *EvMapObjNodeGetFrame_3673d0(Node *);
char *strcpy(char *, const char *);
extern char D_00462E70[];
extern f32 D_0047D294;

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

s32 EvMapObjSplitStart_365860(Self *self, void *arg1, s32 arg2) {
    V4 gp;
    V4 z;
    V4 mtx[4];
    V4 t;
    V4 c;
    F4 m[3];
    F4 box[2];
    F4 sz;
    V4 v6110;
    F4 mx;
    F4 mn;
    V4 M[4];
    V4 a;
    V4 b;
    Ent buf[0x100];
    Pick *p;
    Draw *d;
    Mdl *q;
    s32 mdl;
    Node *node;
    s32 i;
    Prim *o;
    s32 *key;
    V4 *pp;
    s32 j;
    s32 dev;
    Node *nd2;
    s32 n2;
    Prim *o2;

    if (!(self->fD0 & 0x2000000)) {
        return 0;
    }
    if (EvMapObjGetMode_366b80(self) != 1) {
        return 0;
    }
    self->mode = arg2;
    self->nEnt = 0;
    p = HandleRegistryLookup_314aa0(GetObjRefTable_313de0(), self->id);
    if (p != 0) {
        p->fB6 = 1;
        self->id = -1;
        if (EvMapObjGetId_366b70(self) == 10) {
            p->GetPos(&gp);
            EffectSpawnHitBulletAlt_2d7e00(-1, &gp);
            return 0;
        }
    }
    d = TargetRefGetMapObj_2e7050(self->fA0);
    q = EvMapObjGetModel_366bb0(self);
    if (d != 0 && q != 0) {
        mdl = q->f6C;
        ZERO(&z, 0x10);
        d->Begin();
        t = self->pos;
        EvMapObjPartCalcMatrix_363a70(self->fE0, mtx);
        VecAdd_13be20(&t, &t, &mtx[3]);
        mtx[3].q = t.q;
        mtx[3].f.w = 1.0f;
        MtxStore3x4_186390(d, mtx);
        d->End();
        VecScale_1cbca0(&c, arg1, 1.0f);
        d->Begin();
        node = self->list;
        i = 0;
        if (self->nList > 0) {
        pp = &self->pos;
        for (; i < self->nList; i++, node++) {
            o = EvMapObjNodeGetPart_3673c0(node);
            key = EvMapObjNodeGetFrame_3673d0(node);
            EvMapObjPartClear_3641f0(o);
            ModelGetFrameMeshBounds_151f60(mdl, box, ModelFindFrameIndexByName_151220(mdl, *key), 0);
            VecSub_13be40(&sz, &box[0], &box[1]);
            if (sz.x < sz.y && sz.x < sz.z) {
                m[0].y = sz.z;
                m[0].x = 0.0f;
                m[0].z = 0.0f;
                m[0].w = 1.0f;
                m[1].x = 0.0f;
                m[1].y = 0.0f;
                m[1].w = 1.0f;
                m[2].w = 1.0f;
                m[2].x = 0.0f;
                m[2].y = 0.0f;
                m[1].z = -sz.x / 2.0f;
                m[2].z = sz.x / 2.0f;
                o->r = sz.x / 2.0f;
            } else if (sz.y < sz.x && sz.y < sz.z) {
                m[0].z = sz.z;
                m[0].x = 0.0f;
                m[0].y = 0.0f;
                m[0].w = 1.0f;
                m[1].y = 0.0f;
                m[1].z = 0.0f;
                m[1].w = 1.0f;
                m[2].w = 1.0f;
                m[2].y = 0.0f;
                m[2].z = 0.0f;
                m[1].x = -sz.x / 2.0f;
                m[2].x = sz.x / 2.0f;
                o->r = sz.y / 2.0f;
            } else {
                m[0].x = 0.0f;
                m[0].y = sz.z;
                m[0].z = 0.0f;
                m[0].w = 1.0f;
                m[1].y = 0.0f;
                m[1].z = 0.0f;
                m[1].w = 1.0f;
                m[2].w = 1.0f;
                m[2].y = 0.0f;
                m[2].z = 0.0f;
                m[1].x = -sz.x / 2.0f;
                m[2].x = sz.x / 2.0f;
                o->r = sz.z / 2.0f;
            }
            VecAdd_13be20(&sz, &m[0], &m[1]);
            VecAdd_13be20(&sz, &sz, &m[2]);
            VecScale_13be00(&sz, &sz, D_0047D294);
            VecAdd_13be20(&m[0], &m[0], &sz);
            VecAdd_13be20(&m[1], &m[1], &sz);
            VecAdd_13be20(&m[2], &m[2], &sz);
            EvMapObjPartSetRows_363950(o, m);
            EvMapObjPartCalcEdgeLengths_3638d0(o);
            EvMapObjPartCalcRadiusMaybe_363850(o, EvMapObjGetId_366b70(self));
            EvMapObjPartInitFromFrame_363f90(o, key);
            o->v[0].col = c;
            o->v[1].col = c;
            o->v[2].col = c;
            o->v[0].x = pp->f.x;
            o->v[0].y = pp->f.y;
            o->v[0].z = pp->f.z;
            o->v[1].x = pp->f.x;
            o->v[1].y = pp->f.y;
            o->v[1].z = pp->f.z;
            o->v[2].x = pp->f.x;
            o->v[2].y = pp->f.y;
            o->v[2].z = pp->f.z;
        }
        }
        d->End();
        NodeGetTranslation_186650(d, &v6110);
        VecCopy_1cbe30(&mn, &self->pos);
        VecCopy_1cbe30(&mx, &self->pos);
        mn.x += 32.0f;
        mn.y += 32.0f;
        mn.z += 32.0f;
        mx.x -= 32.0f;
        mx.y -= 32.0f;
        mx.z -= 32.0f;
        self->nEnt = 0;
        if (self->mode & 2) {
            MatIdentity_1cbe40(M);
            VecScaleToLength_1cb510(&a, &c, -EvMapObjGetRadiusMaybe_366b60(self));
            VecNormalize_1cbb80(&b, &a);
            VecCross_1cb9f0(&M[0], &M[1], &a);
            VecCross_1cb9f0(&M[1], &a, &M[0]);
            VecCross_1cb9f0(&M[2], &M[0], &M[1]);
            VecSub_1cbd00(&M[3], &v6110, &a);
            VecScaleToLength_1cb510(&M[0], &M[0], EvMapObjGetRadiusMaybe_366b60(self));
            VecScaleToLength_1cb510(&M[1], &M[1], EvMapObjGetRadiusMaybe_366b60(self));
            VecScaleToLength_1cb510(&M[2], &M[2], EvMapObjGetRadiusMaybe_366b60(self));
            MatMulVec4Args_1cb7f0(&self->ent[self->nEnt].a.w[0], M, 1.0f, 1.0f, 0.0f, 1.0f);
            MatMulVec4Args_1cb7f0(&self->ent[self->nEnt].a.w[4], M, -1.0f, 1.0f, 0.0f, 1.0f);
            MatMulVec4Args_1cb7f0(&self->ent[self->nEnt].a.w[8], M, 1.0f, -1.0f, 0.0f, 1.0f);
            VecCopy_1cbe30(&self->ent[self->nEnt].v, &b);
            self->ent[self->nEnt].s.h[0] = 0;
            self->ent[self->nEnt].s.h[2] = 0;
            self->ent[self->nEnt].s.h[3] = 0;
            self->nEnt++;
            MatMulVec4Args_1cb7f0(&self->ent[self->nEnt].a.w[0], M, -1.0f, -1.0f, 0.0f, 1.0f);
            MatMulVec4Args_1cb7f0(&self->ent[self->nEnt].a.w[4], M, 1.0f, -1.0f, 0.0f, 1.0f);
            MatMulVec4Args_1cb7f0(&self->ent[self->nEnt].a.w[8], M, -1.0f, 1.0f, 0.0f, 1.0f);
            VecCopy_1cbe30(&self->ent[self->nEnt].v, &b);
            self->ent[self->nEnt].s.h[0] = 0;
            self->ent[self->nEnt].s.h[2] = 0;
            self->ent[self->nEnt].s.h[3] = 0;
            self->nEnt++;
        }
        for (j = 0; j < self->nEnt; j++) {
            buf[j].a = self->ent[j].a;
            buf[j].v = self->ent[j].v;
            buf[j].s = self->ent[j].s;
            buf[j].x54 = self->ent[j].x54;
        }
        j += MapEvCollectCollTrisNearMaybe_1ff130(&buf[j], 0x100 - j, &mn, &self->pos, -1, 32.0f);
        nd2 = self->list;
        for (n2 = 0; n2 < self->nList; n2++, nd2++) {
            o2 = EvMapObjNodeGetPart_3673c0(nd2);
            for (mdl = 0; mdl < 3; mdl++) {
                EvMapObjPartClipEdgesToColl_3636e0(o2, buf, j);
            }
        }
    }
    dev = GetCurrentScene_1f5be0();
    GameSceneSoundSlot5PlaySe_1d05a0(dev, EvMapObjGetBreakSe_366b40(self));
    strcpy(self->name, D_00462E70);
    self->f300 = 2;
    self->f302 = 0;
    return 1;
}
}
