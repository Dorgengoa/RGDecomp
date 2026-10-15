#include "types.h"

typedef unsigned __int128 u128;
typedef struct Vec { f32 x, y, z, w; } Vec;
typedef struct Mtx { Vec r[4]; } Mtx;

class Big {
public:
    u8 pad0[0x10];
    u8 m10[0x70];       /* 10 */
    u32 i80;            /* 80 */
    u8 pad84[0x2C];
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void v60(f32);
    u8 padB4[8];
    s16 sBC;            /* BC */
    u8 padBE[0xC2];
    Vec v180;           /* 180 */
    u8 pad190[0x10];
    Vec v1A0;           /* 1A0 */
    Vec v1B0;           /* 1B0 */
    u8 pad1C0[4];
    f32 f1C4;           /* 1C4 */
    f32 f1C8;           /* 1C8 */
};

typedef struct R {
    s16 a;
    s32 b;
    s32 c;
    union { s32 w; struct { u16 d : 16; u16 e : 16; } s; } u;
    s32 f;
} R;

typedef struct Obj { u8 pad[0x32]; s16 h32; s32 i34; s32 i38; u32 i3C; u8 pad40[0x24]; f32 f64; } Obj;
typedef struct H { u8 pad[0xB6]; s16 sB6; } H;

typedef struct Self {
    u8 pad0[0xA0];
    u8 mA0[0x30];       /* A0 */
    u32 flags;          /* D0 */
    u8 padD4[0xC];
    u8 mE0[0x134];      /* E0 */
    s32 i214;           /* 214 */
    s32 i218;           /* 218 */
    u8 pad21C[0x2F4 - 0x21C];
    u8 *p2F4;           /* 2F4 */
    u8 pad2F8[4];
    s16 s2FC;           /* 2FC */
    u8 pad2FE[2];
    s16 s300;           /* 300 */
    s16 s302;           /* 302 */
    char name[0x10];    /* 304 */
    f32 f314;           /* 314 */
    u8 pad318[4];
    f32 f31C;           /* 31C */
    f32 f320;           /* 320 */
    u8 pad324[0xC];
    s32 i330;           /* 330 */
    u8 pad334[4];
    s32 i338;           /* 338 */
} Self;

extern "C" {
void MtxStore3x4_186390(Obj *, Mtx *);
void NodeGetRotation_1865e0(Obj *, Vec *);
void NodeGetTranslation_186650(Obj *, Vec *);
void VecAdd_1cbdc0(Vec *, Vec *, Vec *);
s32 ProjectileCloneAndRegister_22e560(Big *);
s32 GetEffectMgr_2d9040(void);
void EffectSetId_2e0100(s32, R *, s32);
void EffectSetParamInt_2e0530(s32, R *, s32, s32);
void EffectCreateByName_2e1020(R *, s32, void *, s32);
Obj *TargetRefGetMapObj_2e7050(void *);
s32 GetObjRefTable_313de0(void);
H *HandleRegistryLookup_314aa0(s32, s32);
void ProjectileCtor_317eb0(Big *, s32, s32, s32, f32);
void EvMapObjPartSetVelFromPrev_363ef0(void *);
void EvMapObjPartMoveToNode_3640a0(void *, Obj *, Vec *);
void EvMapObjPartClear_3641f0(void *);
f32 GetThrowGravity_3647b0(void);
f32 EvMapObjGetRadiusMaybe_366b60(Self *);
void EvMapObjNodeResetFrameMaybe_367340(u8 *);
s16 *ExecInfoGetActDataMaybe_3a7170(void *);
void ExecInfoInitFromObj_3a7790(void *, s32, s32);
void ExecInfoInitFromChara_3a7830(void *, s32, s32, s32, s32);
char *strcpy(char *, const char *);
void NodeCalcWorldMatrixThunk_186130(Obj *, Mtx *);
}
extern char D_00462E80[];
extern char D_00462E90[];
extern char D_00462EA0[];
extern u8 D_00471AA0[];
extern f32 D_0047D1E8;

#define obj ((Big *)buf)
#define F(p, T, o) (*(T *)((u8 *)(p) + (o)))

extern "C" s32 EvMapObjThrowStart_3661f0(Self *self, Obj *o, Vec *v, s32 id, s32 x) {
    Vec v770;
    Vec v760;
    Mtx m720;
    Vec v710;
    u128 buf[0x630 / 16];
    R tmp;
    R rA0;
    R r80;
    u8 *q2;
    Obj *p;
    u8 *q;
    s32 i;
    H *h;
    f32 z;
    u32 fl;
    f32 f;
    s32 r;
    s16 *s;
    s32 w;

    if (!(self->flags & 0x2000000)) return 0;
    if (o == 0) return 0;
    self->i330 = 0;
    o->h32 = 0;
    o->i3C |= 1;
    NodeGetTranslation_186650(o, &v770);
    NodeGetRotation_1865e0(o, &v760);
    VecAdd_1cbdc0(&v770, &v770, v);
    p = TargetRefGetMapObj_2e7050(self->mA0);
    if (p != 0) {
        self->f31C = 1.0f;
        self->f320 = 1.0f;
        p->h32 = 1;
        p->i3C &= ~1;
        p->i34 = 0;
        p->i38 = 0;
        NodeCalcWorldMatrixThunk_186130(o, &m720);
        VecAdd_1cbdc0(&m720.r[3], &m720.r[3], v);
        MtxStore3x4_186390(p, &m720);
        p->f64 = self->f31C * self->f314;
        { u8 *p_ = (u8 *)&v710; u32 n_ = 0x10; if (p_) while (n_) { *p_ = 0; n_--; p_++; } }
        EvMapObjPartClear_3641f0(self->mE0);
        EvMapObjPartMoveToNode_3640a0(self->mE0, p, &v710);
        EvMapObjPartSetVelFromPrev_363ef0(self->mE0);
        self->i218 = 2;
        self->i214 = 0;
        q = self->p2F4;
        for (i = 0; i < self->s2FC; i++, q += 0x150) {
            EvMapObjNodeResetFrameMaybe_367340(q);
        }
    }
    h = HandleRegistryLookup_314aa0(GetObjRefTable_313de0(), self->i338);
    if (h != 0) {
        h->sB6 = 1;
        self->i338 = -1;
    }
    ProjectileCtor_317eb0(obj, 1, id, 0xD, 150.0f);
    q2 = obj->m10;
    if (id >= 0 && id < 12) {
        ExecInfoInitFromChara_3a7830(q2, id, -1, 0, x);
    } else if (id >= 0x80 && id < 0x9C) {
        ExecInfoInitFromObj_3a7790(q2, id, x);
    }
    obj->sBC = 3;
    obj->v60(EvMapObjGetRadiusMaybe_366b60(self));
    z = v770.z;
    f = EvMapObjGetRadiusMaybe_366b60(self);
    obj->v180.w = 1.0f;
    obj->v180.y = v770.y + f;
    obj->v180.z = z;
    fl = obj->i80;
    F(obj, f32, 0x180) = v770.x;
    if (fl & 0x80000000) *(u128 *)&obj->v1A0 = *(u128 *)&obj->v180;
    *(u128 *)&obj->v1B0 = *(u128 *)v;
    obj->f1C4 = GetThrowGravity_3647b0();
    obj->f1C8 = D_0047D1E8;
    r = ProjectileCloneAndRegister_22e560(obj);
    self->i338 = r;
    if (r < 0) {
        F(obj, void *, 0xB0) = D_00471AA0;
        return 0;
    }
    s = ExecInfoGetActDataMaybe_3a7170(q2);
    if (s != 0 && (*s == 0x25B || *s == 0x25E || *s == 0x261 || *s == 0x265)) {
        w = GetEffectMgr_2d9040();
        tmp.u.w = 0;
        if (*s == 0x25B || *s == 0x261) {
            EffectCreateByName_2e1020(&rA0, w, D_00462E80, -1);
            tmp = rA0;
        } else {
            EffectCreateByName_2e1020(&r80, w, D_00462E90, -1);
            tmp = r80;
        }
        EffectSetId_2e0100(w, &tmp, id);
        EffectSetParamInt_2e0530(w, &tmp, 0, 1);
        EffectSetParamInt_2e0530(w, &tmp, 1, self->i338);
    }
    strcpy(self->name, D_00462EA0);
    self->s300 = 1;
    self->s302 = 0;
    F(obj, void *, 0xB0) = D_00471AA0;
    return 1;
}
