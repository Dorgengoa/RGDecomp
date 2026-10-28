/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_loop_invariants off
typedef rg_u128 u128;

typedef struct {
    f32 x, y, z, w;
} Vec4;

struct ListNode {
    ListNode *next;
    s8 _4[0xC];
};

struct Item {
    s8 _0[0xC];
    u8 xC;
    s8 _d[0xA4 - 0xD];
    void *xA4;
    u8 xA8;
};

struct ItemList {
    ListNode *head;
    ListNode *cur;
    s32 done;
};

struct Slot {
    s32 x0;
    s32 _4;
    s16 x8;
    s8 _a[0x12];
};

struct Party {
    s8 _0[0xC];
    Slot *slots;
    s8 _10[0x24];
    u8 *x34;
};

struct Elem {
    s8 _0[4];
    s32 x4;
    s16 x8;
    s8 _a[0x12];
    s32 x1C;
};

extern "C" {
f64 FabsDouble_1283a0(f64);
f32 VecDistanceXZ_13d390(Vec4 *, Vec4 *);
void NodeGetTranslation_186650(void *, Vec4 *);
u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
s32 MapGetAreaSlot1_1e5750(s32);
s32 MapGetFirstAreaSlot_1e5760(s32);
void *MapDataFindNodeByName_1e7190(s32, s32);
s32 GetCurrentScene_1f5be0(void);
u8 *GetGameData_1fede0(void);
Party *GetWorldDataMgr_1fedf0(void);
s32 GetMapMgr_201a90(void);
void HatenaMarkSetAssigned_345110(Item *, s32);
void HatenaMarkBindNode_345120(Item *, void *);
void HatenaMarkSetState_345190(Item *, s32);
void HatenaMarkCheckStateChange_345230(Item *);
void HatenaMarkLatchState_345290(Item *);
float HatenaMarkProximityCheck_3452b0(Item *, Vec4 *, s32);
Elem *IterNext_370040(void *);
void IterInit_370170(void *, void *, int, int);
void HatenaMarkListAssignNearby_344900(ItemList *list);
}

static inline void listBegin(ItemList *l) {
    if (l->cur == 0) {
        l->cur = l->head;
        l->done = 0;
    }
}

static inline Item *listNext(ItemList *l) {
    ListNode *n = l->cur;
    Item *it;
    if (n == 0) {
        return 0;
    }
    it = (Item *)(n + 1);
    l->cur = n->next;
    if (l->cur == 0) {
        l->done = 1;
    }
    return it;
}

static inline void listEnd(ItemList *l) {
    l->cur = 0;
    l->done = 0;
}

static inline u8 *getTbl(u8 *t, s32 idx) {
    u8 *r;
    if (idx >= 0) {
        if (idx >= 2) {
            r = 0;
        } else {
            r = *(u8 **)(t + 0x4C) + idx * 0xB4;
        }
    } else {
        r = 0;
    }
    return r;
}

static inline bool farther(f32 a, f32 b) {
    bool r = a > b;
    return r;
}

static inline void *getO(void **op) {
    return *op;
}

static inline f32 getD(f32 *dp) {
    return *dp;
}

static inline void putS(void **op, f32 *dp, void *co, f32 cd, void *po, f32 pd) {
    op[-1] = co;
    dp[-1] = cd;
    *op = po;
    *dp = pd;
}

static inline void getS(void **op, f32 *dp, void **co, f32 *cd) {
    *co = *op;
    *cd = *dp;
}

#pragma push
#pragma optimization_level 3
void HatenaMarkListAssignNearby_344900(ItemList *list) {
    u8 iter[8];
    Vec4 pos[3] __attribute__((aligned(16)));
    void *objs[64];
    f32 dists[64] __attribute__((aligned(16)));
    Vec4 v __attribute__((aligned(16)));
    u8 *pl;
    Party *party;
    s32 ctx;
    s32 n;
    s32 i;
    Item *it;

    pl = GetGameData_1fede0();
    if (pl == 0) {
        return;
    }
    party = GetWorldDataMgr_1fedf0();
    if (party == 0) {
        return;
    }
    ctx = GetMapMgr_201a90();
    if (ctx == 0) {
        return;
    }
    {
        s32 d = GetCurrentScene_1f5be0();
        u8 *q;
        if (d == 0) {
            return;
        }
        q = ObjRecGetLiveObject_1c4a90(d, *(s16 *)(*(u8 **)(pl + 0x18) + 0x18E));
        Vec4 *pp = &pos[0];
        if (q != 0) {
            *(u128 *)pp = *(u128 *)(q + 0x180);
        } else {
            pp->x = 0;
            pp->y = 0;
            pp->z = 0;
            pp->w = 0;
        }
    }
    n = 0;
    for (i = 0; i < 2; i++) {
        Slot *slot = &party->slots[i];
        s32 grp;
        u8 *tbl;
        s32 idx;
        Elem *el;
        if (slot == 0) {
            continue;
        }
        if (slot->x0 == 0) {
            continue;
        }
        if (i == 0) {
            grp = MapGetAreaSlot1_1e5750(ctx);
        } else {
            grp = MapGetFirstAreaSlot_1e5760(ctx);
        }
        if (grp == 0) {
            continue;
        }
        tbl = getTbl(party->x34, slot->x8);
        if (tbl == 0) {
            continue;
        }
        {
            u8 *p = tbl;
            if (p != 0) {
                p += 0x88;
            }
            IterInit_370170(iter, p, 0, 0);
        }
        while ((el = IterNext_370040(iter)) != 0) {
            void *obj;
            f32 dist;
            f32 dy;
            if (el->x8 != 3) {
                continue;
            }
            if (el->x1C != 2) {
                continue;
            }
            obj = MapDataFindNodeByName_1e7190(grp, el->x4);
            if (obj == 0) {
                continue;
            }
            NodeGetTranslation_186650(obj, &v);
            dist = VecDistanceXZ_13d390(&v, &pos[0]);
            dy = FabsDouble_1283a0(v.y - pos[0].y);
            if (dist <= 2000.0f && dy <= 100.0f) {
                objs[n] = obj;
                dists[n] = dist;
                n++;
            }
        }
    }
    if (n >= 2) {
        bool swapped;
        do {
            void *po;
            f32 pd;
            s32 j;
            swapped = false;
            po = objs[0];
            pd = dists[0];
            for (j = 1; j < n; j++) {
                void **op0 = &objs[j];
                f32 *dp0 = &dists[j];
                void *co = *op0;
                f32 cd = *dp0;
                bool r = false;
                if (pd > cd) {
                    r = true;
                }
                if (r) {
                    swapped = true;
                    putS(&objs[j], &dists[j], co, cd, po, pd);
                } else {
                    po = co;
                    pd = cd;
                }
            }
        } while (swapped);
    }
    listBegin(list);
    for (;;) {
        it = listNext(list);
        if (it == 0) {
            break;
        }
        HatenaMarkSetAssigned_345110(it, 0);
    }
    listEnd(list);
    for (i = 0; i < n; i++) {
        void **slotp = &objs[i];
        void *o = *slotp;
        listBegin(list);
        for (;;) {
            it = listNext(list);
            if (it == 0) {
                break;
            }
            if (it->xA4 != o) {
                continue;
            }
            HatenaMarkSetAssigned_345110(it, 1);
            *slotp = 0;
        }
        listEnd(list);
    }
    listBegin(list);
    for (;;) {
        bool found;
        it = listNext(list);
        if (it == 0) {
            break;
        }
        s32 m;
        if (it->xC != 2) {
            continue;
        }
        found = false;
        for (m = 0; m < n; m++) {
            void **slotp = &objs[m];
            void *o = *slotp;
            if (o == 0) {
                continue;
            }
            HatenaMarkSetAssigned_345110(it, 1);
            HatenaMarkBindNode_345120(it, o);
            *slotp = 0;
            found = true;
        }
        if (!found) {
            break;
        }
    }
    listEnd(list);
    listBegin(list);
    for (;;) {
        s32 j;
        it = listNext(list);
        if (it == 0) {
            break;
        }
        if (it->xA8 != 0) {
            HatenaMarkLatchState_345290(it);
            for (j = 0; j < 1; j++) {
                HatenaMarkProximityCheck_3452b0(it, &pos[j], j);
                if (it->xC == 1) {
                    break;
                }
            }
            HatenaMarkCheckStateChange_345230(it);
        } else {
            HatenaMarkSetState_345190(it, 2);
        }
    }
    listEnd(list);
}
#pragma pop
