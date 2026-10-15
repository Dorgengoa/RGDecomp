#include "types.h"

typedef unsigned __int128 u128;

struct Vec4 {
    f32 x, y, z, w;
};

struct F4 {
    f32 x, y, z, w;
};

struct Item60 {
    u32 w[12];
    F4 v;
    s16 s[10];
    s32 f54;
} __attribute__((aligned(16)));

struct Ent {
    u8 pad0[0x32];
    s16 vis;             /* 0x32 */
    u8 pad34[8];
    u32 flags;           /* 0x3C */
    u8 pad40[0x24];
    f32 alpha;           /* 0x64 */
};

struct Q {
    u8 pad0[0xF0];
    u128 pos;            /* 0xF0 */
    u8 pad100[0x20];
    f32 a;               /* 0x120 */
    f32 b;               /* 0x124 */
    f32 c;               /* 0x128 */
};

struct VtO {
    u8 pad[0x54];
    void (*f54)(void *, f32, f32, f32);
};

struct Obj80 {
    u8 pad0[0x88];
    s16 idx;             /* 0x88 */
    u8 pad8A[0x26];
    VtO *vt;             /* 0xB0 */
    u8 padB4[0xDC];
    f32 f190;            /* 0x190 */
    u8 pad194[0xC];
};

struct VtS {
    u8 pad[0x40];
    void (*f40)(void *, Vec4 *);
    void (*f44)(void *, Vec4 *);
};

class Src {
public:
    u8 pad0[0x80];
    u32 flags;           /* 0x80 */
    u8 pad84[0x2C];
    virtual void v8(); virtual void vC(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C();
    virtual void f40(Vec4 *);
    virtual void f44(Vec4 *);
};

struct VtE {
    u8 pad[0x10];
    void (*f10)(void *);
    void (*f14)(void *);
};

class Eff {
public:
    u8 pad0[0x68];
    virtual void v8(); virtual void vC();
    virtual void f10();
    virtual void f14();
};

class VObj {
public:
    u8 pad0[0xB0];
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void SetPos(f32, f32, f32);
};

struct Fade {
    u8 pad0[0xA0];
    u8 fA0[0x30];        /* 0xA0 */
    u32 flags;           /* 0xD0 */
    u8 padD4[0xC];
    u8 fE0[0xF0];        /* 0xE0 */
    Vec4 v1D0;           /* 0x1D0 */
    Vec4 v1E0;           /* 0x1E0 */
    u8 pad1F0[0x40];
    Item60 items[2];     /* 0x230 */
    u8 pad2F0[4];
    u8 *list;            /* 0x2F4 */
    s16 nitems;          /* 0x2F8 */
    s16 pad2FA;
    s16 count;           /* 0x2FC */
    s16 pad2FE;
    s16 active;          /* 0x300 */
    s16 timer;           /* 0x302 */
    u8 on;               /* 0x304 */
    u8 pad305[0xF];
    f32 a;               /* 0x314 */
    f32 da;              /* 0x318 */
    f32 b;               /* 0x31C */
    f32 db;              /* 0x320 */
    u8 pad324[0x10];
    u8 flag334;          /* 0x334 */
    u8 pad335[3];
    s32 id;              /* 0x338 */
};

extern "C" {
s32 GetMapMgr_201a90(void);
s32 TargetRefGetId_2e7120(void *);
s32 MapSlotsFindById_1e4b90(s32, s32, s32);
s32 MapDataIsLoaded_1e79d0(s32);
s32 EvMapObjGetName_366b90(Fade *);
s32 MapDataFindObjsByName_1e6d40(s32, s32, Ent **, s32);
Ent *TargetRefGetMapObj_2e7050(void *);
s32 EvMapObjGetMode_366b80(Fade *);
s32 GetObjRefTable_313de0(void);
Src *HandleRegistryLookup_314aa0(s32, s32);
void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
f32 EvMapObjGetRadiusMaybe_366b60(Fade *);
void NodeCalcWorldMatrixThunk_186130(Ent *, void *);
void VecAdd_1cbdc0(Vec4 *, Vec4 *, Vec4 *);
void MtxStore3x4_186390(Ent *, void *);
void EvMapObjPartMoveToNode_3640a0(void *, Ent *, Vec4 *);
void EvMapObjSplitStart_365860(Fade *, Vec4 *, u32);
Q *EvMapObjNodeGetFrame_3673d0(u8 *);
Q *EvMapObjNodeGetPart_3673c0(u8 *);
void FrameGetWorldPos_148f30(Q *, Vec4 *);
void VecDivScalar_1cbbf0(Vec4 *, Vec4 *, f32);
void VecDivScalarPoint_1cbbc0(Vec4 *, Vec4 *, f32);
void VecCopy_1cbe30(Vec4 *, Vec4 *);
s32 MapEvCollectCollTrisNearMaybe_1ff130(Item60 *, s32, Vec4 *, Vec4 *, s32, f32);
void EvMapObjNodeApplyPartMatrixMaybe_367230(u8 *, Item60 *, s32);
void VecAdd_13be20(Vec4 *, Vec4 *, void *);
void VecNormalize_13bd90(Vec4 *, Vec4 *);
f32 EvMapObjGetScatterSpeedMaybe_366b50(Fade *);
void VecScale_13be00(Vec4 *, Vec4 *, f32);
void EvMapObjPartAddVel_363a10(Q *, Vec4 *);
void EvMapObjPartGetMeanVelMaybe_3639a0(Q *, Vec4 *);
f32 VecLength_13d4a0(Vec4 *);
void EvMapObjPartClipEdgesToColl_3636e0(Q *, Item60 *, s32);
void EvMapObjStartFade_3657e0(Fade *);
s32 IsInBattle_288420(void);
s32 GetGameMode_1f59c0(void);
void NodeGetTranslation_186650(Ent *, Vec4 *);
s32 EvMapObjGetId_366b70(Fade *);
void AttackObjBaseCtor_3181b0(Obj80 *, s32, s32, s32, f32);
void AttackObjBaseCloneAndRegister_27bd90(Obj80 *);
extern f32 D_0045B080[];
extern VtO D_00471AA0;
}

#define ZERO16(v) { u8 *p_ = (u8 *)&(v); u32 n_ = 0x10; if (p_) { while (n_) { *p_ = 0; n_--; p_++; } } }

#pragma optimization_level 3
extern "C" void EvMapObjUpdate_364ab0(Fade *p) {
    Ent *list[0x140];
    Vec4 v800;
    Vec4 mF0;
    u8 mC0[0x30];
    Vec4 mB0;
    Vec4 mA0;
    Vec4 z90;
    Vec4 sum;
    Vec4 t70;
    Vec4 hi;
    Vec4 lo;
    Item60 arr[0x100];
    Vec4 v740;
    Vec4 v730;
    Ent *list2[0x140];
    Vec4 v220;
    Obj80 o;
    u8 *itk;
    u8 *it;
    Eff *eff;
    s32 g;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    Ent *e;
    Src *src;
    s32 w;
    Q *q;
    f32 f20;
    f32 f21;
    f32 f6;
    f32 d;
    f32 len;

    if (!(p->flags & 0x2000000)) return;
    p->a = p->a + p->da;
    if (p->a < 0.0f) p->a = 0.0f;
    if (!(p->a <= 1.0f)) p->a = 1.0f;
    if (p->da != 0.0f) {
        w = GetMapMgr_201a90();
        g = MapSlotsFindById_1e4b90(w, TargetRefGetId_2e7120(p->fA0), 0);
        if (g != 0 && MapDataIsLoaded_1e79d0(g) != 0) {
            n = MapDataFindObjsByName_1e6d40(g, EvMapObjGetName_366b90(p), list, 0x140);
            for (i = 0; i < n; i++) {
                list[i]->alpha = p->a;
                if (p->a == 0.0f) {
                    list[i]->vis = 0;
                } else if (p->flag334 != 0 && list[i]->flags == 0) {
                    list[i]->vis = 1;
                }
            }
        }
    }
    p->b = p->b + p->db;
    if (p->b < 0.0f) p->b = 0.0f;
    if (!(p->b <= 1.0f)) p->b = 1.0f;
    if (p->da != 0.0f || p->db != 0.0f) {
        e = TargetRefGetMapObj_2e7050(p->fA0);
        if (e != 0) {
            e->alpha = p->a * p->b;
            if (e->alpha == 0.0f || p->active == 0) {
                e->vis = 0;
                e->flags |= 1;
            } else {
                e->vis = 1;
                e->flags &= ~1;
            }
        }
    }
    if (p->a == 0.0f) {
        if (p->da < 0.0f) p->da = 0.0f;
    }
    if (p->a == 1.0f) {
        if (!(p->da <= 0.0f)) p->da = 0.0f;
    }
    if (p->b == 0.0f) {
        if (p->db < 0.0f) p->db = 0.0f;
    }
    if (p->b == 1.0f) {
        if (!(p->db <= 0.0f)) p->db = 0.0f;
    }
    switch (EvMapObjGetMode_366b80(p)) {
    case 1:
        ZERO16(v800);
        src = HandleRegistryLookup_314aa0(GetObjRefTable_313de0(), p->id);
        if (src != 0) {
        VecSub_13be40(&v800, &p->v1D0, &p->v1E0);
        e = TargetRefGetMapObj_2e7050(p->fA0);
        if (e != 0) {
            src->f40(&mB0);
            src->f44(&mA0);
            mB0.y = mB0.y - EvMapObjGetRadiusMaybe_366b60(p);
            NodeCalcWorldMatrixThunk_186130(e, mC0);
            VecAdd_1cbdc0(&mF0, &mB0, &mA0);
            MtxStore3x4_186390(e, mC0);
            ZERO16(z90);
            EvMapObjPartMoveToNode_3640a0(p->fE0, e, &z90);
        }
        if (src->flags & 3) {
            EvMapObjSplitStart_365860(p, &v800, src->flags);
        }
        } else {
            e = TargetRefGetMapObj_2e7050(p->fA0);
            if (e != 0) {
                e->vis = 0;
                e->flags |= 1;
            }
            p->active = 0;
        }
        break;
    case 2:
    case 3:
        eff = (Eff *)TargetRefGetMapObj_2e7050(p->fA0);
        if (eff == 0) break;
        ZERO16(sum);
        for (it = p->list, j = 0; j < p->count; j++, it += 0x150) {
            FrameGetWorldPos_148f30(EvMapObjNodeGetFrame_3673d0(it), &t70);
            VecAdd_1cbdc0(&sum, &sum, &t70);
        }
        VecDivScalar_1cbbf0(&sum, &sum, sum.w);
        VecCopy_1cbe30(&lo, &sum);
        VecCopy_1cbe30(&hi, &sum);
        f21 = D_0045B080[0];
        f21 = 3.0f * (f32)f21;
        f20 = EvMapObjGetRadiusMaybe_366b60(p);
        f20 = f20 + f21;
        f6 = EvMapObjGetRadiusMaybe_366b60(p);
        f6 = f6 + f21;
        lo.x += f20;
        lo.y += f6;
        lo.z += f20;
        hi.x -= f20;
        hi.y -= f6;
        hi.z -= f20;
        for (i = 0; i < p->nitems; i++) {
            arr[i] = p->items[i];
        }
        i += MapEvCollectCollTrisNearMaybe_1ff130(&arr[i], 0x100 - i, &lo, &sum, -1, f20);
        it = p->list;
        eff->f10();
        for (j = 0; j < p->count; j++, it += 0x150) {
            EvMapObjNodeApplyPartMatrixMaybe_367230(it, arr, i);
        }
        eff->f14();
        if (EvMapObjGetMode_366b80(p) == 2 && p->timer == 1) {
            ZERO16(v740);
            for (j = 0, it = p->list; j < p->count; j++, it += 0x150) {
                VecAdd_13be20(&v740, &v740, &EvMapObjNodeGetPart_3673c0(it)->pos);
            }
            VecDivScalarPoint_1cbbc0(&v740, &v740, (f32)p->count);
            f21 = 0.0f;
            f20 = 1024.0f;
            for (j = 0, it = p->list; j < p->count; j++, it += 0x150) {
                Q *qm = EvMapObjNodeGetPart_3673c0(it);
                d = (qm->a + qm->b + qm->c) / 6.0f;
                if (!(d <= f21)) f21 = d;
                if (d < f20) f20 = d;
            }
            for (k = 0, itk = p->list; k < p->count; k++, itk += 0x150) {
                q = EvMapObjNodeGetPart_3673c0(itk);
                *(u128 *)&v730 = q->pos;
                VecSub_13be40(&v730, &v730, &v740);
                VecNormalize_13bd90(&v730, &v730);
                VecScale_13be00(&v730, &v730, EvMapObjGetScatterSpeedMaybe_366b50(p));
                EvMapObjPartAddVel_363a10(q, &v730);
                EvMapObjPartGetMeanVelMaybe_3639a0(q, &v730);
                len = VecLength_13d4a0(&v730);
                if (!(len <= 6.0f)) {
                    VecScale_13be00(&v730, &v730, 6.0 / len);
                    EvMapObjPartGetMeanVelMaybe_3639a0(q, &v730);
                }
                j = 0;
                do {
                    EvMapObjPartClipEdgesToColl_3636e0(q, arr, i);
                    j++;
                } while (j < 3);
            }
        }
        if (EvMapObjGetMode_366b80(p) == 2 && p->timer > 30) {
            EvMapObjStartFade_3657e0(p);
        }
        if (!(p->b <= 0.0f)) break;
    default:
        p->on = 0;
        p->active = 0;
        break;
    }
    if (IsInBattle_288420() != 0 && GetGameMode_1f59c0() == 7 && p->a == 1.0f) {
        w = GetMapMgr_201a90();
        g = MapSlotsFindById_1e4b90(w, TargetRefGetId_2e7120(p->fA0), 0);
        if (g != 0 && MapDataIsLoaded_1e79d0(g) != 0) {
            n = MapDataFindObjsByName_1e6d40(g, EvMapObjGetName_366b90(p), list2, 0x140);
            for (i = 0; i < n; i++) {
                e = *(Ent **)(u32)&list2[i];
                if (e->vis == 0) continue;
                NodeGetTranslation_186650(e, &v220);
                AttackObjBaseCtor_3181b0(&o, 4, EvMapObjGetId_366b70(p), 2, 1.0f);
                o.idx = i;
                v220.y = v220.y + EvMapObjGetRadiusMaybe_366b60(p);
                ((VObj *)&o)->SetPos(v220.x, v220.y, v220.z);
                o.f190 = EvMapObjGetRadiusMaybe_366b60(p);
                AttackObjBaseCloneAndRegister_27bd90(&o);
                o.vt = &D_00471AA0;
            }
        }
    }
    p->timer++;
    if (p->timer > 10000) p->timer--;
}
