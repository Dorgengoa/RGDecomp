/* rgp:protos */
#line 1
#include "types.h"
#pragma bool off

class Item {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Count() { return VCM0(s32, 0x50); }
    
    
    void Add(s32 a0) { VCM(void, (void *, s32), 0x5C, a0); }
    u8 pad4[2];
    s16 f6;
    u8 pad8[2];
    u8 fA0 : 1;
    u8 fA1 : 1;
    u8 fA2 : 6;
    u8 padB;
    s16 fC;
};

struct Info {
    u8 pad0[0x14];
    s8 f14;
    u8 pad15[2];
    u8 f17a : 6;
    u8 f17b : 1;
    u8 f17c : 1;
};

class Db {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info * Get(s16 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(Info *, (void *, s16, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};

struct Sys {
    u8 pad0[0x40];
    struct {
        u8 pad0[8];
        Db *db;
    } *f40;
};

struct Inv {
    u8 pad0[0x168];
    s32 f168;
};

struct Ent {
    s32 id;
    s32 v;
};

extern "C" {
Item *PoolGetUsedElem_36acb0(s32, s32);
s32 InvFindFreeSlotId_3c4900(Inv *, s32, s32, int);
Item * InvObjCreateForItem_3c7110(Inv *, s32, s32, int);
s32 InvFindByInvId_3c87d0(Inv *, s32, s32);
void StateFlagSet_3ccb70(s32, s32, s32, s32);
s32 InvCategoryGetMaxId_3d5170(s32);
s32 InvCategoryGetMinId_3d5210(s32);
s32 InvGetCategoryOfId_3d56f0(s32);
s32 ItemDefGetStackLimit_40e070(Info *);

extern s32 D_00465B50[];
extern s32 D_00465B60[];
extern Ent D_00466200[];
extern struct {
    u8 pad0[0x10];
    s32 f10;
} *D_00483890;
extern Sys *D_00483894;
extern s32 D_004801A0[2];
extern s32 D_004801A8[2];
extern s32 D_004801B0[2];
}
typedef struct { s32 v[2]; } S2;
extern "C" {
}

static inline s32 KindIdx(s32 *kinds, s32 r) {
    s32 x = -1;
    if (kinds[0] == r) x = 0;
    else if (kinds[1] == r) x = 1;
    return x;
}

extern "C" Item *InvAddItemCoreMaybe_3c6540(Inv *inv, s32 id, s32 kind, s32 n, s32 slot, u8 flag, s32 *out) {
    Info *info;
    u8 b220;
    s32 total;
    s32 lo;
    s32 hi;
    u8 b1E0;
    s32 d1D0;
    s32 j;
    s32 k;
    s32 kk;
    s32 v190;
    s32 kv;
    s32 cnt;
    s32 m;
    s32 i;
    s32 t;
    s32 idx;
    s32 q;
    s32 r;
    s32 pos;
    s32 x;
    s32 amt;
    s32 t2;
    s32 s;
    s32 a1v;
    s32 lim;
    u8 use;
    Item *res;
    Item *it;
    Item *e;
    Item *it2;
    Sys *sys;
    Ent *en;
    s32 kq;
    s32 kr;

    if (out != 0) *out = -1;
    if (id < 0 || n <= 0) return 0;
    if (inv->f168 == 0) return 0;
    sys = D_00483894;
    if (sys == 0) return 0;
    {
        Info *p_ = sys->f40->db->Get(id, (int)(long)(kind), (int)(long)(n));
        info = p_;
    }
    if (info == 0) return 0;
    S2 kinds __attribute__((aligned(16))) = *(S2 *)D_004801A0;
    cnt = 1;
    kinds.v[0] = kind;
    if (kind == 10) {
        kinds.v[1] = 1;
        kinds.v[0] = 0;
        cnt = 2;
    }
    if (kind != 8) {
        if (info->f14 == 2 || info->f14 == 3 || info->f14 == 4 || info->f14 == 6) {
            kinds.v[0] = info->f14;
            kinds.v[1] = -1;
            cnt = 1;
        }
    }
    S2 a __attribute__((aligned(16))) = *(S2 *)D_004801A8;
    S2 b __attribute__((aligned(16))) = *(S2 *)D_004801B0;
    res = 0;
    m = 0;
    b220 = 0;
    s32 A[2] = {0};
    s32 B[2] = {0};
    s32 C[2] = {0};
    total = 0;
    s32 D[2] = {0};
    s32 E[2] = {0};
    Item *list[99];
    lo = -1;
    hi = -1;
    i = 0;
    v190 = D_00465B60[0];
    for (; i < cnt; i++) {
        t = v190;
        if (*(s32 *)((u32)&kinds.v[(u32)i]) == 0) t = ItemDefGetStackLimit_40e070(info);
        E[i] = t;
        kv = *(s32 *)((u32)&kinds.v[i]);
        s32 *pa = &a.v[i];
        *pa = InvCategoryGetMinId_3d5210(kv);
        s32 *pb = &b.v[i];
        *pb = InvCategoryGetMaxId_3d5170(kv);
        {
            s32 av = *pa;
            s32 bv = *pb;
            B[i] = bv - av + 1;
            if (lo < 0 || av < lo) lo = av;
            if (hi < 0 || hi < bv) hi = bv;
        }
    }
    a1v = a.v[1];
    b1E0 = 0;
    d1D0 = 0;
    lim = D_00465B50[0];
    for (j = 0; j < lim; j++) {
        it = PoolGetUsedElem_36acb0(inv->f168, j);
        if (it == 0) continue;
        if (it->fA1) continue;
        t = it->f6;
        if (t < lo) continue;
        if (t > hi) continue;
        idx = cnt >= 2 && t >= a1v;
        A[idx]++;
        if (it->fC != id) continue;
        idx = (s32)idx;
        if (t == slot) b1E0 = 1;
        q = E[idx];
        r = it->Count();
        D[idx] += r;
        {
            u8 ok = 0;
            if (r < q) ok = 1;
            if (!ok) continue;
        }
        if (!(m < 99)) continue;
        pos = -1;
        if (t == slot) {
            pos = 0;
            d1D0 = 1;
        } else {
            for (kq = d1D0; kq < m; kq++) {
                e = list[kq];
                if (e == 0) continue;
                if (!(t < e->f6)) break;
                if (pos > kq || pos < 0) {
                    pos = kq;
                } else {
                    break;
                }
            }
        }
        if (pos >= 0) {
            for (kq = m - 1; kq >= pos; kq--) {
                list[kq + 1] = list[kq];
            }
        } else {
            pos = m;
        }
        if (pos >= 0 && pos < 99) {
            m++;
            list[pos] = it;
        }
    }
    for (kq = 0; kq < cnt; kq++) {
        total += C[kq] = B[kq] - A[kq];
    }
    if ((info->f17b) && kind != 8) {
        if (m > 0 && list[0] != 0) {
            r = InvGetCategoryOfId_3d56f0(list[0]->f6);
            if (r == kinds.v[0]) b220 = 1;
        }
        if (n > 0 && slot >= 0 && !b1E0) {
            r = InvGetCategoryOfId_3d56f0(slot);
            x = KindIdx(kinds.v, r);
            if (x >= 0) {
                amt = n;
                if (r == 0) {
                    t2 = E[x] - D[x];
                    if (t2 < n) amt = t2;
                } else {
                    t2 = *(s32 *)((u32)&E[x]);
                    if (t2 < n) amt = t2;
                }
                if (amt > 0) {
                    if (!flag) {
                        it2 = InvObjCreateForItem_3c7110(inv, id, slot, 0);
                        if (it2 != 0) {
                            it2->Add(amt - 1);
                            res = it2;
                        }
                    }
                    n -= amt;
                    D[x] += amt;
                }
            }
        }
        if (n > 0 && !b220 && D[0] < E[0]) {
            s = InvFindFreeSlotId_3c4900(inv, id, kinds.v[0], 0);
            if (s >= 0) {
                r = InvGetCategoryOfId_3d56f0(s);
                x = KindIdx(kinds.v, r);
                if (x >= 0) {
                    amt = n;
                    if (r == 0) {
                        t2 = E[x] - D[x];
                        if (t2 < n) amt = t2;
                    } else {
                        t2 = *(s32 *)((u32)&E[x]);
                        if (t2 < n) amt = t2;
                    }
                    if (amt > 0) {
                        if (!flag) {
                            Item *i2_ = InvObjCreateForItem_3c7110(inv, id, s, 0);
                            if (i2_ != 0) {
                                i2_->Add(amt - 1);
                                if (res == 0) res = i2_;
                            }
                        }
                        n -= amt;
                        D[x] += amt;
                    }
                }
            }
        }
        if (n > 0) {
            s32 k1_ = kinds.v[1];
            for (k = 0; k < m; k++) {
                e = list[k];
                if (e == 0) continue;
                q = e->Count();
                r = InvGetCategoryOfId_3d56f0(e->f6);
                x = -1;
                if (kinds.v[0] == r) x = 0;
                else if (k1_ == r) x = 1;
                if (x < 0) continue;
                amt = n;
                if (r == 0) {
                    t2 = E[x] - D[x];
                    if (t2 < n) amt = t2;
                } else {
                    t2 = E[x] - q;
                    if (t2 < n) amt = t2;
                }
                if (amt > 0) {
                    if (!flag) e->Add(amt);
                    n -= amt;
                    D[x] += amt;
                    if (res == 0) res = e;
                }
            }
        }
        for (kq = 0; kq < cnt; kq++) {
            if (n <= 0) continue;
            kr = kinds.v[kq];
            s = InvFindFreeSlotId_3c4900(inv, id, kr, 0);
            if (s < 0) continue;
            amt = n;
            if (kr == 0) {
                t2 = E[(u32)kq] - D[(u32)kq];
                if (t2 < n) amt = t2;
            } else {
                t2 = *(s32 *)((u32)&E[kq]);
                if (t2 < n) amt = t2;
            }
            if (amt > 0) {
                if (!flag) {
                    it2 = InvObjCreateForItem_3c7110(inv, id, s, 0);
                    if (it2 != 0) {
                        it2->Add(amt - 1);
                        if (res == 0) res = it2;
                    }
                }
                n -= amt;
                D[kq] += amt;
            }
        }
        if (out != 0) *out = n;
    } else if (n <= total) {
        use = slot >= 0;
        for (kq = 0; kq < cnt; kq++) {
            kk = kinds.v[kq];
            do {
                for (;;) {
                    if (use) {
                        use = 0;
                        if (InvFindByInvId_3c87d0(inv, slot, 0) != 0) continue;
                        r = slot;
                    } else {
                        r = InvFindFreeSlotId_3c4900(inv, id, kk, 0);
                    }
                    break;
                }
                if (r < 0) break;
                if (!flag) {
                    it2 = InvObjCreateForItem_3c7110(inv, id, r, 0);
                    if (res == 0) res = it2;
                }
                n--;
            } while (n > 0);
            if (n <= 0) break;
        }
        if (out != 0) *out = n;
    } else {
        s32 rem = n - total;
        if (out != 0) *out = rem;
    }
    if (res == 0) return 0;
    if (kind != 8) {
        for (i = 0;; i++) {
            en = &D_00466200[i];
            s32 eid = en->id;
            s32 v_ = en->v;
            if (eid == id) {
                StateFlagSet_3ccb70(D_00483890->f10, v_, 1, 0);
                break;
            }
            if (eid < 0) break;
        }
    }
    return res;
}
