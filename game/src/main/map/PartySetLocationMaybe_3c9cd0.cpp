/* rgp:protos */
#line 1
#include "types.h"
#pragma divbyzerocheck on

extern "C" {
typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct M44 { f32 m[4][4]; } M44;
typedef struct Pair { s16 a; s16 b; } Pair;
typedef struct Rec24 { u8 pad0[0x10]; s16 *x10; } Rec24;
typedef struct Ent24 { s16 x0; u8 pad2[0x16]; } Ent24;
typedef struct Tab { u8 pad0[0x7C]; s16 n7C; u8 pad7E[0xE]; Ent24 *x8C; } Tab;
typedef struct Node { s16 x0; u8 pad2[0xE]; f32 x10; f32 x14; f32 x18; f32 x1C; } Node;
typedef struct K1C { u8 pad0[4]; s16 k4; } K1C;
typedef struct XC { u8 pad0[0x1C]; K1C k; } XC;
typedef struct Bits { u8 b0 : 1; u8 rest : 7; } Bits;
typedef struct Obj {
    u8 pad0[4];
    s16 kind;           /* 0x04 */
    u8 pad6[4];
    s16 a;              /* 0x0A */
    s16 c;              /* 0x0C */
    u8 padE[2];
    s32 d;              /* 0x10 */
    u8 pad14[0xC];
    s32 r20;            /* 0x20 */
    Rec24 *x24;         /* 0x24 */
    s32 r28;            /* 0x28 */
    u8 pad2C[4];
    s16 x30;            /* 0x30 */
    s16 x32;            /* 0x32 */
    s16 f34;
    s16 f36;
    s16 f38;
    s16 n3A;            /* 0x3A */
    s16 n3C;            /* 0x3C */
    Pair p3E[8];        /* 0x3E */
    Pair p5E[8];        /* 0x5E */
    s16 x7E;
    s16 x80;
    s16 x82;
    u8 pad84[0xC];
    V4 x90;             /* 0x90 */
    V4 xA0[3];          /* 0xA0 */
    f32 xD0[3];         /* 0xD0 */
    f32 xDC[3];         /* 0xDC */
    u8 padE8[0x30];
    s64 x118;           /* 0x118 */
    s32 x120;           /* 0x120 */
    u8 pad124[0x68];
    s16 n18C;           /* 0x18C */
    s16 key;            /* 0x18E */
    s16 x190[8];        /* 0x190 */
    u8 pad1A0[0x42D0 - 0x1A0];
    Bits bits;          /* 0x42D0 */
    u8 pad42D1[0x4CA0 - 0x42D1];
    s16 x4CA0;          /* 0x4CA0 */
} Obj;
}

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s32 a0) { return VCM(s32, (void *, s32), 0x70, a0); }
};

extern "C" {
typedef struct S34 { u8 pad0[8]; VObj *x8; u8 padC[8]; void *x14; VObj *x18; } S34;
typedef struct S8 { u8 pad0[0x34]; S34 *x34; } S8;
typedef struct G90 { u8 pad0[8]; S8 *x8; } G90;
typedef struct G94 { u8 pad0[0xC]; XC *xC; u8 pad10[0x24]; void *x34; } G94;

void VecCopy_1cbe30(V4 *, V4 *);
f32 VecDistance_13d3d0(V4 *, V4 *);
f32 VecDistSqXZ_13d330(V4 *, V4 *);
f64 FabsDouble_1283a0(f64);
void MatFromRotPos_1caf90(M44 *, V4 *, V4 *);
void MatMulPoint_1cb8e0(V4 *, M44 *, V4 *);
void *GetMapMgr_201a90(void);
void *MapFindAreaSlotById_1e4cb0(void *, s16);
void MapDataGetRotVec4_1e7720(void *, V4 *);
void MapDataGetPosVec4_1e7740(void *, V4 *);
Node *IterNext_370040(void *);
void IterInit_370170(void *, void *, int, int);
s16 *PartyFindEncounterForKeyMaybe_3c99e0(Obj *, s32, s32 *);
void ZoneRadiusLeaveFireEventMaybe_3ebba0(G90 *, s16, s16);
void ZoneRadiusEnterFireEventMaybe_3ebc90(G90 *, s16, s16);
void ZoneKeyedLeaveFireEventMaybe_3ebd90(G90 *, s16, s16);
void ZoneKeyedEnterFireEventMaybe_3ebe80(G90 *, s16, s16);
void WorldOnPartyMapBoxChangedMaybe_3ebf80(G90 *);
void WorldOnPartyMapIdChanged_3ebfa0(G90 *);
void WorldOnPartyNavGraphChanged_3ebfc0(G90 *, s32, s32, int);
void WorldOnPartyLocationChanged_3ec050(G90 *, s32, s32);
void WorldOnPartyMapAreaChanged_3ec2e0(G90 *);
void HandleEntryFindById_3f1600(G94 *, s32);
void HandleEntryFindById_3f2450(G94 *, s16);
void *GroupFindByKey_411740(void *, s16);
Tab *GroupFindByKey_4117d0(void *, s16);
Pair *DataTableSortedIndexFindRange_413cb0(Tab *, s16, s32 *);
Rec24 * GroupTableFindEntry_415e00(void *, s16, s16, int);
extern f32 D_0045B080[];
extern f32 D_00480190;
extern f32 D_00480194;
extern f32 D_00480198;
extern f32 D_0048019C;
extern G90 *D_00483890;
extern G94 *D_00483894;
}


static inline s32 Find(Obj *o)
{
    s32 j;
    for (j = 0; j < o->n18C; j++) {
        if (o->x190[j] == o->key) {
            return j;
        }
    }
    return -1;
}

static inline Ent24 *Lookup(Tab *t, s32 k)
{
    return (k >= 0 && k < t->n7C) ? &t->x8C[k] : 0;
}

extern "C" s32 PartySetLocationMaybe_3c9cd0(Obj *obj, s32 a, s32 c, s32 d, s32 x30, s32 x32, V4 *pos, f32 *rad, u8 bit, s32 v4CA0, u8 quiet)
{
    s32 cnt;
    s32 idx;
    u8 it[8];
    Pair sv3E[8] __attribute__((aligned(16)));
    Pair sv5E[8] __attribute__((aligned(16)));
    V4 v1E0 __attribute__((aligned(16)));
    V4 v1D0 __attribute__((aligned(16)));
    V4 v1C0 __attribute__((aligned(16)));
    V4 v1B0 __attribute__((aligned(16)));
    V4 v1A0 __attribute__((aligned(16)));
    M44 mtx __attribute__((aligned(16)));
    V4 v150 __attribute__((aligned(16)));
    V4 v140 __attribute__((aligned(16)));
    s32 oldA;
    u8 *kb;
    s32 cs;
    s16 pa;
    s32 qa;
    s32 qb;
    s16 pb;
    s32 oldC;
    s32 old10;
    s32 old30;
    s32 old32;
    s32 n3A;
    s32 n3C;
    s32 i;
    s32 j;
    s32 k;
    bool flag;
    bool upd32;
    bool upd3C;
    bool chg1;
    bool chg2;
    bool chg3;
    bool chg4;
    bool found;
    bool fd1;
    bool fd2;
    bool fd3;
    s32 id;
    s32 id2;
    Rec24 *rp;
    s16 *sp_;
    Tab *tab;
    Pair *list;
    Ent24 *ent;
    void *mdl;
    void *sub;
    Node *node;
    f32 r2;
    f32 thr;
    f32 lim;
    K1C *e;

    if (D_00483890 == 0 || D_00483894 == 0) {
        return 0;
    }
    oldA = obj->a;
    oldC = obj->c;
    old10 = obj->d;
    old30 = obj->x30;
    old32 = obj->x32;
    n3A = obj->n3A;
    n3C = obj->n3C;
    for (i = 0; i < n3A; i++) {
        sv3E[i].a = obj->p3E[i].a;
        sv3E[i].b = obj->p3E[i].b;
    }
    for (i = 0; i < (s16)n3C; i++) {
        sv5E[i].a = obj->p5E[i].a;
        sv5E[i].b = obj->p5E[i].b;
    }
    j = Find(obj);
    VecCopy_1cbe30(&v1E0, &obj->x90);
    VecCopy_1cbe30(&v1D0, &pos[j]);
    v1C0.x = D_00480190;
    v1C0.y = D_00480194;
    v1C0.z = D_00480198;
    v1C0.w = D_0048019C;
    for (k = 0; k < 3; k++) {
        if (obj->x190[k] >= 0) {
            kb = (u8 *)obj + k * 16;
            VecCopy_1cbe30((V4 *)(kb + 0xA0), &pos[k]);
            obj->xD0[k] = rad[k];
            obj->xDC[k] = (f32)FabsDouble_1283a0((f64)VecDistance_13d3d0(&obj->xA0[j], (V4 *)(kb + 0xA0)));
        } else {
            VecCopy_1cbe30(&obj->xA0[k], &v1C0);
            obj->xD0[k] = 0.0f;
            obj->xDC[k] = -1.0f;
        }
    }
    obj->bits.b0 = bit;
    if (a != oldA) {
        obj->a = a;
        obj->r20 = D_00483890->x8->x34->x8->v26((s16)a);
        if (!quiet) {
            WorldOnPartyMapAreaChanged_3ec2e0(D_00483890);
        }
        obj->f34 = 1;
    }
    if (x30 != old30) {
        obj->x30 = x30;
        if (!quiet) {
            WorldOnPartyMapIdChanged_3ebfa0(D_00483890);
        }
    }
    if (c != oldC) {
        obj->c = c;
        cs = (s16)c;
        obj->x24 = GroupTableFindEntry_415e00(D_00483890->x8->x34->x14, cs / 100, cs, 0);
        if (!quiet) {
            WorldOnPartyLocationChanged_3ec050(D_00483890, obj->c, oldC);
        }
        obj->f36 = 1;
        obj->x118 = 0;
        obj->x120 = 0;
    }
    if (d != old10) {
        obj->d = d;
        obj->r28 = D_00483890->x8->x34->x18->v26(d);
        if (!quiet) {
            WorldOnPartyNavGraphChanged_3ebfc0(D_00483890, obj->d, old10, 0);
        }
        obj->f38 = 1;
    }
    rp = obj->x24;
    sp_ = (rp != 0) ? rp->x10 : 0;
    id = (sp_ != 0) ? *sp_ : -1;
    e = &D_00483894->xC->k;
    flag = false;
    if (e != 0) {
        if (e->k4 == 3) goto set;
        if (e->k4 == 4) {
        set:
            flag = true;
        }
    }
    HandleEntryFindById_3f2450(D_00483894, obj->c);
    HandleEntryFindById_3f1600(D_00483894, obj->d);
    obj->x4CA0 = v4CA0;
    if (obj->kind == 10) {
        s32 t = 0;
        if (obj->kind == 10) {
            if (obj->x30 > 20000 && obj->x30 <= 21000) {
                t = obj->x30 - 20000;
            }
        }
        obj->x4CA0 = t + 700;
    }
    upd32 = false;
    if (x32 != old32 && flag) {
        obj->x32 = x32;
        if (!quiet) {
            WorldOnPartyMapBoxChangedMaybe_3ebf80(D_00483890);
        }
        tab = 0;
        if (D_00483894->x34 != 0) {
            tab = GroupFindByKey_4117d0(D_00483894->x34, id);
        }
        obj->n3A = 0;
        upd32 = true;
        cnt = 0;
        list = 0;
        if (tab != 0) {
            list = DataTableSortedIndexFindRange_413cb0(tab, obj->x32, &cnt);
        }
        if (list != 0 && cnt > 0) {
            for (i = 0; i < cnt; i++, list++) {
                ent = Lookup(tab, list->b);
                if (ent == 0) {
                    continue;
                }
                obj->p3E[obj->n3A].a = id;
                obj->p3E[obj->n3A].b = ent->x0;
                obj->n3A++;
                if (obj->n3A >= 8) {
                    break;
                }
            }
        }
    }
    thr = D_0045B080[0];
    upd3C = false;
    if (!((f32)FabsDouble_1283a0((f64)VecDistance_13d3d0(&v1D0, &v1E0)) <= thr) && flag) {
        VecCopy_1cbe30(&obj->x90, &v1D0);
        mdl = MapFindAreaSlotById_1e4cb0(GetMapMgr_201a90(), obj->a);
        if (mdl != 0) {
            MapDataGetPosVec4_1e7740(mdl, &v1B0);
            MapDataGetRotVec4_1e7720(mdl, &v1A0);
            MatFromRotPos_1caf90(&mtx, &v1A0, &v1B0);
            sub = 0;
            if (D_00483894->x34 != 0) {
                sub = GroupFindByKey_411740(D_00483894->x34, id);
            }
            obj->n3C = 0;
            upd3C = true;
            if (sub != 0) {
                sub = (u8 *)sub + 0x88;
            }
            IterInit_370170(it, sub, 0, 0);
            lim = 2.0f * thr;
            while ((node = IterNext_370040(it)) != 0) {
                v150.x = node->x10;
                v150.y = node->x14;
                v150.z = node->x18;
                v150.w = 1.0f;
                MatMulPoint_1cb8e0(&v140, &mtx, &v150);
                if (!((f32)FabsDouble_1283a0((f64)(v140.y - obj->x90.y)) <= lim)) {
                    continue;
                }
                r2 = node->x1C;
                r2 *= r2;
                if ((f32)FabsDouble_1283a0((f64)VecDistSqXZ_13d330(&v140, &obj->x90)) <= r2) {
                    obj->p5E[obj->n3C].a = id;
                    obj->p5E[obj->n3C].b = node->x0;
                    obj->n3C++;
                    if (obj->n3C >= 8) {
                        break;
                    }
                }
            }
        }
    }
    chg1 = false;
    if (upd32) {
        for (i = 0; i < n3A; i++) {
            pa = sv3E[i].a;
            pb = sv3E[i].b;
            found = false;
            for (k = 0; k < obj->n3A; k++) {
                qb = obj->p3E[k].b;
                qa = obj->p3E[k].a;
                if (qa == pa && qb == pb) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                chg1 = true;
                if (!quiet) {
                    ZoneKeyedLeaveFireEventMaybe_3ebd90(D_00483890, pa, pb);
                }
            }
        }
    }
    chg2 = false;
    if (upd3C) {
        for (i = 0; i < n3C; i++) {
            pa = sv5E[i].a;
            pb = sv5E[i].b;
            fd1 = false;
            for (k = 0; k < obj->n3C; k++) {
                qb = obj->p5E[k].b;
                qa = obj->p5E[k].a;
                if (qa == pa && qb == pb) {
                    fd1 = true;
                    break;
                }
            }
            if (!fd1) {
                chg2 = true;
                if (!quiet) {
                    ZoneRadiusLeaveFireEventMaybe_3ebba0(D_00483890, pa, pb);
                }
            }
        }
    }
    chg3 = false;
    if (upd32) {
        for (i = 0; i < obj->n3A; i++) {
            pa = obj->p3E[i].a;
            pb = obj->p3E[i].b;
            fd2 = false;
            for (k = 0; k < n3A; k++) {
                qb = sv3E[k].b;
                qa = sv3E[k].a;
                if (pa == qa && pb == qb) {
                    fd2 = true;
                    break;
                }
            }
            if (!fd2) {
                chg3 = true;
                if (!quiet) {
                    ZoneKeyedEnterFireEventMaybe_3ebe80(D_00483890, pa, pb);
                }
            }
        }
    }
    chg4 = false;
    if (upd3C) {
        for (i = 0; i < obj->n3C; i++) {
            pa = obj->p5E[i].a;
            pb = obj->p5E[i].b;
            fd3 = false;
            for (k = 0; k < n3C; k++) {
                qb = sv5E[k].b;
                qa = sv5E[k].a;
                if (pa == qa && pb == qb) {
                    fd3 = true;
                    break;
                }
            }
            if (!fd3) {
                chg4 = true;
                if (!quiet) {
                    ZoneRadiusEnterFireEventMaybe_3ebc90(D_00483890, pa, pb);
                }
            }
        }
    }
    if (chg3 || chg4 || chg1 || chg2) {
        rp = obj->x24;
        sp_ = (rp != 0) ? rp->x10 : 0;
        id2 = (sp_ != 0) ? *sp_ : -1;
        idx = -1;
        sp_ = PartyFindEncounterForKeyMaybe_3c99e0(obj, id2, &idx);
        if (sp_ != 0) {
            obj->x7E = id2;
            obj->x80 = *sp_;
            obj->x82 = idx;
        } else {
            obj->x7E = -1;
            obj->x80 = -1;
            obj->x82 = -1;
        }
    }
    return 1;
}
