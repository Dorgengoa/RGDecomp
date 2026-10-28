/* rgp:protos */
#line 1
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    void v30() { VCM0(void, 0x30); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v90(s32 a0) { return VCM(s32, (void *, s32), 0x90, a0); }
    s32 v94(s32 a0) { return VCM(s32, (void *, s32), 0x94, a0); }
    s32 v98(s32 a0) { return VCM(s32, (void *, s32), 0x98, a0); }
    
    void vA0(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0xA0, a0, a1); }
    
    u8 vA8() { return VCM0(u8, 0xA8); }
    
    void vB0(s32 a0) { VCM(void, (void *, s32), 0xB0, a0); }
};

typedef struct Info {
    s16 x0;
    s8 x2;
} Info;

typedef struct Unit {
    Obj o;
    u8 pad4[0xC];
    Info *info;
} Unit;

typedef struct Cls {
    u8 pad0[0xA];
    u8 b0 : 1;
    u8 b1 : 1;
} Cls;

typedef struct Lv {
    u8 pad0[0x95];
    u8 x95;
} Lv;

typedef struct Holder {
    u8 pad0[0xC];
    Lv *lv;
} Holder;

typedef struct Mgr {
    u8 pad0[0x90];
    Holder *h;
} Mgr;

typedef struct Sys {
    u8 pad0[0x10];
    s32 x10;
} Sys;

typedef struct Rec {
    u8 x0;
    u8 x1;
    u8 x2;
} Rec;

extern "C" {
s16 *WeaponCombineLookup_3c4280(s32, Info *, u8, Info *, s32, s32 *, u8 *, u8 *, s32 *, Rec **, Rec **, s32 *);
Obj *InvFindByInvId_3c87d0(s32, s32, s32);
void ItemConsume_3d41b0(Obj *, s32, s32, int);
Obj *PoolGetUsedElem_36acb0(s32, s32);
void PoolFreeElem_36a8e0(s32, s32);
s32 InvGetCategoryOfId_3d56f0(s32);
Obj *InvAddItemCoreMaybe_3c6540(s32, s32, s32, s32, s32, s32, s32);
f32 RandFloat_13c010(void);
void WeaponCombineLogAdd_3cbd10(s32, Rec *, s32, s32, bool *);
s32 StateFlagTest_3ccd70(s32, s32);
void StateFlagSet_3ccb70(s32, s32, s32, s32);
extern s32 D_00465A08[];
extern s32 D_00465A10[];
extern s32 D_00465B50[];
extern s32 D_00465D48[];
extern s32 D_00465D50[];
extern s32 D_00465D58[];
extern Sys *D_00483890;
extern Mgr *D_00483894;
}

#define INFO(p) (((Unit *)(p))->info)
#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" Obj *WeaponCombinePerformMaybe_3c36c0(s32 arg0, s32 arg1_, u8 *outA, u8 *outB, s32 *outC)
{
    s32 arg1;
    Obj *units[2];
    Info *infos[2];
    s8 cur[2][5];
    s8 max[2][5];
    Rec *r118;
    Rec *r114;
    s32 w110;
    s32 w;
    s32 n;
    s32 i;
    s32 last;
    Obj *p;
    Obj *x;
    Obj *y;
    u8 v;
    Info *info;
    Info *info2;
    s32 id2;
    s32 v2;
    s32 best;
    s32 mx;
    s32 k;
    s32 a;
    s32 b;
    s32 add;
    s16 *r;
    s32 rid;
    s32 j;
    Obj *u;
    s8 *pa;
    s8 *pb;
    s32 cnt;
    Obj *q;
    Obj *nu;
    f32 d1;
    f32 d2;
    f32 sum;
    s32 lvl;
    s32 extra;
    Rec *t;
    bool flag;
    s32 base;
    f32 sx;

    *outA = 0;
    ZERO(units, 8);
    ZERO(infos, 8);
    ZERO(cur, 10);
    ZERO(max, 10);
    arg1 = (s32)(u32)arg1_; /* laundered copy: retail copies a1 -> s6 late, at the first loop */
    n = 0;
    i = D_00465A08[0];
    last = D_00465A10[0];
    for (; i <= last; i++) {
        p = InvFindByInvId_3c87d0(arg0, i, 0);
        if (p != 0 && ((Cls *)p)->b0) {
            units[n] = p;
            n++;
            if (n == 2) {
                break;
            }
        }
    }
    if (n < 2) {
        return 0;
    }
    x = units[0];
    y = units[1];
    if (INFO(x)->x2 == 7) {
        x = y;
        y = units[0];
    }
    info2 = INFO(y);
    info = INFO(x);
    id2 = info2->x0;
    v = x->vA8();
    v2 = y->vA8();
    if (info2->x2 == 7) {
        if (id2 == 0x40E6) {
            best = -1;
            mx = 0;
            for (k = 0; k < 5; k++) {
                a = x->v94(k);
                b = x->v90(k);
                if (a - b > 0) {
                    if (best < 0 || mx < b) {
                        mx = b;
                        best = k;
                    }
                }
            }
            if (best >= 0) {
                x->vA0(best, mx + D_00465D48[0]);
            }
        } else if (id2 == 0x40E7) {
            best = -1;
            mx = 0;
            for (k = 0; k < 5; k++) {
                a = x->v94(k);
                b = x->v90(k);
                if (a - b > 0) {
                    if (best < 0 || b < mx) {
                        mx = b;
                        best = k;
                    }
                }
            }
            if (best >= 0) {
                x->vA0(best, mx + D_00465D50[0]);
            }
        } else if (id2 == 0x40E8) {
            add = D_00465D58[0];
            for (k = 0; k < 5; k++) {
                a = x->v90(k);
                x->vA0(k, a + add);
            }
        }
        ItemConsume_3d41b0(y, 1, 1, 0);
        return x;
    }
    r118 = 0;
    r114 = 0;
    w110 = 0;
    w = 0;
    r = WeaponCombineLookup_3c4280(arg0, info, v, info2, v2, &w, outA, outB, outC, &r118, &r114, &w110);
    if (r == 0) {
        return 0;
    }
    rid = *r;
    for (j = 0; j < 2; j++) {
        u = units[j];
        infos[j] = INFO(u);
        pa = cur[j];
        pb = max[j];
        for (k = 0; k < 5; k++) {
            pa[k] = u->v98(k);
            pb[k] = u->v90(k);
        }
    }
    for (j = 0; j < 2; j++) {
        ItemConsume_3d41b0(units[j], 1, 1, 0);
    }
    if (*(s32 *)(arg0 + 0x168) != 0) {
        cnt = D_00465B50[0];
        for (k = 0; k < cnt; k++) {
            q = PoolGetUsedElem_36acb0(*(s32 *)(arg0 + 0x168), k);
            if (q != 0 && ((Cls *)q)->b1) {
                q->v30();
                PoolFreeElem_36a8e0(*(s32 *)(arg0 + 0x168), k);
            }
        }
    }
    nu = InvAddItemCoreMaybe_3c6540(arg0, rid, InvGetCategoryOfId_3d56f0(arg1), 1, arg1, 0, 0);
    if (nu != 0) {
        for (k = 0; k < 5; k++) {
            d1 = (f32)(max[0][k] - cur[0][k]);
            d2 = (f32)(max[1][k] - cur[1][k]);
            sum = d1 + d2;
            lvl = D_00483894->h->lv->x95;
            base = nu->v98(k);
            sx = d1 * (d1 / sum) + d2 * (d2 / sum);
            nu->vA0(k, base + (s32)(sx * ((f32)lvl / 100.0f)));
        }
    }
    extra = -1;
    if (*outB != 0) {
        extra = (s32)(6.0f * RandFloat_13c010()) + 1;
    }
    if (nu != 0) {
        nu->vB0(extra);
    }
    if (*outA != 0) {
        t = 0;
        if (r118->x2 == r114->x0) {
            t = r118;
        } else if (r114->x2 == r118->x0) {
            t = r114;
        }
        flag = false;
        WeaponCombineLogAdd_3cbd10(D_00483890->x10, t, 0, 1, &flag);
    }
    if (rid == 0x3EC3) {
        if (StateFlagTest_3ccd70(D_00483890->x10, 0x5A3) != 0) {
            StateFlagSet_3ccb70(D_00483890->x10, 0x5A4, 1, 0);
        }
        StateFlagSet_3ccb70(D_00483890->x10, 0x4AF, 1, 0);
    }
    return nu;
}
