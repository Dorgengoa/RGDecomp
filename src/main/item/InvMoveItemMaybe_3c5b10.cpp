#include "types.h"

typedef struct X5b10 {
    s16 m0;
    u8 pad2[0x16];
    u8 m18;
} X5b10;

class VObj5b10 {
public:
    virtual void u18_0();
    virtual void u18_1();
    virtual void u18_2();
    virtual void u18_3();
    virtual void u18_4();
    virtual void u18_5();
    virtual void u18_6();
    virtual void u18_7();
    virtual void u18_8();
    virtual void u18_9();
    virtual void u18_10();
    virtual void u18_11();
    virtual void u18_12();
    virtual void u18_13();
    virtual void u18_14();
    virtual void u18_15();
    virtual void u18_16();
    virtual void u18_17();
    virtual s32 v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C(s32);
};

typedef struct Obj5b10 {
    VObj5b10 v;
    u8 pad4[2];
    s16 m6;
    u8 pad8[2];
    u8 b0:1;
    u8 b1:1;
    u8 b2:6;
    u8 padB[5];
    X5b10 *m10;
} Obj5b10;

typedef struct Ctx5b10 {
    u8 pad0[0x168];
    s32 m168;
} Ctx5b10;

extern "C" {
Obj5b10 *InvFindByInvId_3c87d0(Ctx5b10 *, s32, s32);
s32 InvFindFreeSlotId_3c4900(Ctx5b10 *, s32, s32);
s32 InvAddItemCoreMaybe_3c6540(Ctx5b10 *, s32, s32, s32, s32, s32, s32);
s32 InvCountById_3c78d0(Ctx5b10 *, s32, s32, s32);
void ItemMarkRemoved_3d4130(Obj5b10 *, s32);
void ItemConsume_3d41b0(Obj5b10 *, s32, s32);
s32 ItemHasCountFlag_3d44e0(Obj5b10 *);
s32 ItemInInvCategory0Or1Or9_3d4890(Obj5b10 *);
s32 PartyFindItemHolder_3d4c20(Obj5b10 *);
s32 InvGetCategoryOfId_3d56f0(s32);
s32 ItemDefGetStackLimit_40e070(X5b10 *);
extern s32 D_00465B50[];
extern s32 D_00465B60[];
extern s32 D_00483894;
}

extern "C" s32 InvMoveItemMaybe_3c5b10(Ctx5b10 *ctx, Obj5b10 *obj, s32 id, s32 n, s32 *out1, s32 *out2, Obj5b10 **out3, bool flag)
{
    s32 rem;
    s32 n0;
    s32 r;
    s32 t14C;
    s32 lim2;
    bool same;
    s32 avail;
    s32 lim;
    X5b10 *x;
    s32 m6;
    X5b10 *y;
    s32 kd;
    s32 kc;
    s32 max2;
    s32 tA0;
    s32 max;
    s32 t;
    s32 res;
    Obj5b10 *o;
    bool ok;

    if (D_00483894 == 0) {
        return 0;
    }
    if (obj == 0) {
        return 0;
    }
    if (ctx->m168 == 0) {
        return 0;
    }
    if (id < 0 || id >= D_00465B50[0]) {
        return 0;
    }
    x = obj->m10;
    if (x == 0) {
        return 0;
    }
    max = obj->v.v50();
    rem = 0;
    if (n < 0 || max < n) {
        n = max;
    }
    n0 = n;
    if (out1 != 0) {
        *out1 = 0;
    }
    if (out2 != 0) {
        *out2 = max;
    }
    if (out3 != 0) {
        *out3 = 0;
    }
    r = -1;
    m6 = obj->m6;
    if (id == m6 || n == 0) {
        return 2;
    }
    if (ItemInInvCategory0Or1Or9_3d4890(obj) == 0) {
        return 0;
    }
    t14C = InvGetCategoryOfId_3d56f0(m6);
    t = InvGetCategoryOfId_3d56f0(id);
    {
        bool on = PartyFindItemHolder_3d4c20(obj);
        if (on && t != 0) {
            return 0;
        }
    }
    if ((x->m18 & 1) == 0 && t == 1) {
        return 0;
    }
    o = InvFindByInvId_3c87d0(ctx, id, 0);
    ok = false;
    if (o != 0 && !o->b1) {
        ok = true;
    }
    if (ok) {
        y = o->m10;
        max2 = o->v.v50();
        lim = D_00465B60[0];
        lim2 = lim;
        if (t == 0 && y != 0) {
            lim2 = ItemDefGetStackLimit_40e070(y);
        }
        if (t == 0) {
            if (t14C != 0) {
                bool on2 = PartyFindItemHolder_3d4c20(o);
                if (on2) {
                    return 0;
                }
                if (y != 0 && (y->m18 & 1) == 0 && t14C == 1) {
                    return 0;
                }
            }
        }
        same = false;
        kd = obj->m10->m0;
        kc = o->m10->m0;
        if (kd == kc) {
            if (ItemHasCountFlag_3d44e0(obj) != 0) {
                same = true;
            }
        }
        if (same) {
            if (t14C != t) {
                avail = lim2 - max2;
                if (t == 0) {
                    avail = lim2 - InvCountById_3c78d0(ctx, kd, t, 0);
                }
                if (avail <= 0) {
                    return 0;
                }
                if (n <= avail) {
                    if (n == max) {
                        if (out1 != 0) {
                            *out1 = n;
                        }
                        if (out2 != 0) {
                            *out2 = 0;
                        }
                        res = 4;
                    } else {
                        if (out1 != 0) {
                            *out1 = n;
                        }
                        if (out2 != 0) {
                            *out2 = max - n;
                        }
                        res = 5;
                    }
                } else if (n == max) {
                    n = avail;
                    if (out1 != 0) {
                        *out1 = avail;
                    }
                    if (out2 != 0) {
                        *out2 = max - avail;
                    }
                    res = 5;
                } else {
                    r = InvFindFreeSlotId_3c4900(ctx, obj->m10->m0, InvGetCategoryOfId_3d56f0(obj->m6));
                    if (r < 0) {
                        return 0;
                    }
                    n = avail;
                    rem = n0 - avail;
                    if (out1 != 0) {
                        *out1 = avail;
                    }
                    if (out2 != 0) {
                        *out2 = max - n0;
                    }
                    res = 8;
                }
            } else {
                if (t14C == 0) {
                    if (x != 0) {
                        lim = ItemDefGetStackLimit_40e070(x);
                    }
                }
                t = lim - max2;
                if (n <= t) {
                    if (n == max) {
                        if (out1 != 0) {
                            *out1 = n;
                        }
                        if (out2 != 0) {
                            *out2 = 0;
                        }
                        res = 4;
                    } else {
                        if (out1 != 0) {
                            *out1 = n;
                        }
                        if (out2 != 0) {
                            *out2 = max - n;
                        }
                        res = 5;
                    }
                } else if (t <= 0 || n == max) {
                    n = (s32)(u32)t;
                    if (out1 != 0) {
                        *out1 = t;
                    }
                    if (out2 != 0) {
                        *out2 = max - n;
                    }
                    res = 5;
                } else {
                    r = InvFindFreeSlotId_3c4900(ctx, obj->m10->m0, InvGetCategoryOfId_3d56f0(obj->m6));
                    if (r < 0) {
                        return 0;
                    }
                    n = t;
                    rem = n0 - t;
                    if (out1 != 0) {
                        *out1 = t;
                    }
                    if (out2 != 0) {
                        *out2 = max - n0;
                    }
                    res = 8;
                }
            }
        } else {
            if (t14C != t) {
                if (t == 0) {
                    if (ItemHasCountFlag_3d44e0(obj) != 0) {
                        t = InvCountById_3c78d0(ctx, kd, t, 0);
                        if (x != 0) {
                            lim = ItemDefGetStackLimit_40e070(x);
                        }
                        if (lim < n + t) {
                            return 0;
                        }
                    }
                } else if (t14C == 0) {
                    if (ItemHasCountFlag_3d44e0(o) != 0) {
                        t = o->v.v50();
                        tA0 = InvCountById_3c78d0(ctx, kc, t14C, 0);
                        if (y != 0) {
                            lim = ItemDefGetStackLimit_40e070(y);
                        }
                        if (lim < t + tA0) {
                            return 0;
                        }
                    }
                }
            }
            if (n == max) {
                res = 3;
            } else {
                r = InvFindFreeSlotId_3c4900(ctx, obj->m10->m0, InvGetCategoryOfId_3d56f0(obj->m6));
                if (r < 0) {
                    return 0;
                }
                if (out1 != 0) {
                    *out1 = n;
                }
                if (out2 != 0) {
                    *out2 = max - n;
                }
                res = 7;
            }
        }
    } else {
        if (t14C != t && t == 0) {
            if (ItemHasCountFlag_3d44e0(obj) != 0) {
                s32 v;
                t = InvCountById_3c78d0(ctx, obj->m10->m0, t, 0);
                v = D_00465B60[0];
                if (x != 0) {
                    v = ItemDefGetStackLimit_40e070(x);
                }
                v -= t;
                if (v < n) {
                    n = v;
                }
                if (n <= 0) {
                    return 0;
                }
            }
        }
        if (n == max) {
            res = 1;
        } else {
            if (out1 != 0) {
                *out1 = n;
            }
            if (out2 != 0) {
                *out2 = max - n;
            }
            res = 6;
        }
    }
    if (!flag && res != 0 && res != 2) {
    switch (res) {
    case 1:
        obj->m6 = id;
        break;
    case 3:
        obj->m6 = id;
        o->m6 = m6;
        break;
    case 4:
        ItemMarkRemoved_3d4130(obj, 1);
        o->v.v5C(n);
        break;
    case 5:
        ItemConsume_3d41b0(obj, n, 1);
        o->v.v5C(n);
        break;
    case 6:
        {
            s32 k;
            ItemConsume_3d41b0(obj, n, 1);
            k = obj->m10->m0;
            InvAddItemCoreMaybe_3c6540(ctx, k, InvGetCategoryOfId_3d56f0(id), n, id, 0, 0);
        }
        break;
    case 7:
        {
            s32 k;
            ItemConsume_3d41b0(obj, n, 1);
            o->m6 = r;
            k = obj->m10->m0;
            InvAddItemCoreMaybe_3c6540(ctx, k, InvGetCategoryOfId_3d56f0(id), n, id, 0, 0);
            if (out3 != 0) {
                *out3 = o;
            }
        }
        break;
    case 8:
        {
            s32 k;
            s32 q;
            ItemConsume_3d41b0(obj, n0, 1);
            o->v.v5C(n);
            k = obj->m10->m0;
            q = InvAddItemCoreMaybe_3c6540(ctx, k, InvGetCategoryOfId_3d56f0(r), rem, r, 0, 0);
            if (out3 != 0) {
                *(s32 *)out3 = q;
            }
        }
        break;
    }
    }
    return res;
}
