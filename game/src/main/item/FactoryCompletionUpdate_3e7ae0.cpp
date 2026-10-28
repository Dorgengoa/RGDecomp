/* rgp:protos */
#line 1
#include "types.h"

struct Ent {
    u8 pad0[8];
    u8 b0 : 1;
    u8 pad9[3];
    void *mC;
};

struct Src {
    u8 pad0[2];
    u8 b0 : 1;
    u8 pad3;
    void *m4;
};

struct Obj {
    u8 pad0[4];
    u8 *m4;
    s16 m8;
    u8 padA[2];
    Ent *mC;
    u8 pad10[4];
    u8 b0 : 1;
    u8 b1 : 1;
};

struct Rec {
    u8 pad0[2];
    s16 m2;
    s16 m4;
    s16 m6;
    Src *m8;
};

extern "C" {
extern void IterInit_370170(void *, u8 *, int, int);
extern void *IterNext_370040(void *);
extern void IterReset_3700f0(void *);
extern Obj *DataTableFindByRefKey_406180(u8 *, s32);
extern s32 ItemGroupUnlockProgressGet_3cbc20(u8 *, s32);
extern s32 StateFlagTest_3ccd70(u8 *, s32);
extern void StateFlagSet_3ccb70(u8 *, s32, bool, s32);
extern void StateVarSet_3cc9c0(u8 *, s32, s16, s32);
extern u8 D_00466BC0[];
}

extern "C" s32 FactoryCompletionUpdate_3e7ae0(u8 *arg0, int rgp_a1, int rgp_a2, int rgp_a3) {
    s32 it1[2];
    s32 it2[2];
    u8 *p;
    Obj *o;
    Rec *r;
    s32 total;
    s32 hit;
    s32 pct;
    bool full;

    p = *(u8 **)(*(u8 **)(*(u8 **)(arg0 + 8) + 0xA4) + 0xC);
    if (p != 0) {
        p += 0x88;
    }
    IterInit_370170(it1, p, (int)rgp_a2, (int)rgp_a3);
    while ((o = (Obj *)IterNext_370040(it1)) != 0) {
        s32 f = 0;
        s32 i;
        s32 n;
        Ent *e;
        o->b0 = f;
        o->b1 = f;
        n = o->m8;
        e = o->mC;
        for (i = 0; i < n; i++, e++) {
            e->b0 = f;
            e->mC = D_00466BC0;
        }
    }
    p = *(u8 **)(*(u8 **)(*(u8 **)(arg0 + 8) + 0xA4) + 0x10);
    if (p != 0) {
        p += 0x88;
    }
    IterInit_370170(it2, p, 0, 0);
    while ((r = (Rec *)IterNext_370040(it2)) != 0) {
        o = DataTableFindByRefKey_406180(*(u8 **)(*(u8 **)(*(u8 **)(arg0 + 8) + 0xA4) + 0xC), r->m4);
        if (o == 0) {
            continue;
        }
        if (o->m4 == 0) {
            continue;
        }
        if (*(s8 *)(o->m4 + 0x1E) >= 0) {
            if (ItemGroupUnlockProgressGet_3cbc20(*(u8 **)(arg0 + 0x10), *(s8 *)(o->m4 + 0x1E)) >= 0) {
                o->b1 = true;
            }
        }
        if (!(u8)StateFlagTest_3ccd70(*(u8 **)(arg0 + 0x10), r->m2)) {
            continue;
        }
        o->b0 = true;
        {
            Ent *e = o->mC;
            s32 n = o->m8;
            s32 n2 = r->m6;
            Src *s = r->m8;
            s32 i;
            if (e != 0 && s != 0 && n > 0 && n2 > 0) {
                for (i = 0; i < n && i < n2; i++, e++, s++) {
                    if (s->b0) {
                        e->b0 = true;
                        e->mC = 0;
                    } else if (!e->b0) {
                        if (s->m4 != 0) {
                            e->mC = s->m4;
                        }
                    }
                }
            }
        }
    }
    total = 0;
    hit = 0;
    IterReset_3700f0(it1);
    while ((o = (Obj *)IterNext_370040(it1)) != 0) {
        total++;
        if (o->b1) {
            hit++;
        }
    }
    pct = 100.0f * ((f32)hit / (f32)total);
    full = false;
    if (pct < 0) {
        pct = 0;
    } else if (pct >= 100) {
        full = true;
        pct = 100;
    }
    StateFlagSet_3ccb70(*(u8 **)(arg0 + 0x10), 0x1E7, full, 0);
    StateVarSet_3cc9c0(*(u8 **)(arg0 + 0x10), 0x6B, pct, 0);
    return 1;
}
