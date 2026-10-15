#include "types.h"

typedef struct Dat Dat;

class Item {
public:
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5();
    virtual void vf6(); virtual void vf7(); virtual void vf8(); virtual void vf9();
    virtual void Kill(void); /* 0x30 */
    virtual void vf11(); virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15(); virtual void vf16();
    virtual void vf17();
    virtual s32 Num(void); /* 0x50 */
    virtual void vf19(); virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23(); virtual void vf24();
    virtual void vf25(); virtual void vf26(); virtual void vf27(); virtual void vf28(); virtual void vf29(); virtual void vf30();
    virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35(); virtual void vf36();
    virtual void vf37(); virtual void vf38(); virtual void vf39(); virtual void vf40();
    virtual s32 Rank(void); /* 0xAC */
    u8 pad4[2];
    s16 x6;
    u8 pad8[2];
    u8 xA0 : 1;
    u8 xA1 : 1;
    u8 xA2 : 6;
    u8 padB[5];
    Dat *x10;
};

struct Dat {
    s16 x0;
    s8 x2;
    s8 x3;
    s16 x4;
    s16 x6;
    s16 x8;
};

typedef struct Inv {
    u8 pad0[0x168];
    s32 x168;
} Inv;

extern "C" {
void PoolFreeElem_36a8e0(s32, s32);
Item *PoolGetUsedElem_36acb0(s32, s32);
s32 InvMoveItemMaybe_3c5b10(Inv *, Item *, s32, s32, s32, s32, s32, s32);
Item *InvFindInCategoryRange_3c8370(Inv *, s32, s32, s32, s32, s32);
Item *InvFindByInvId_3c87d0(Inv *, s32, s32);
void InvFreeCategory8Items_3c8d70(Inv *);
s32 ItemGetStackLimit_3d4480(Item *);
s32 ItemHasCountFlag_3d44e0(Item *);
extern s32 D_004659E8[];
extern s32 D_00465A00[];
extern s32 D_00465A08[];
extern s32 D_00465A10[];
extern s32 D_00465A18[];
extern s32 D_00465A30[];
extern s32 D_00465A38[];
extern s32 D_00465A40[];
extern s32 D_00465B50[];
bool InvOrganizeMaybe_3c50c0(Inv *self, s32 kind, s32 cat, u32 flags);
}

static inline s32 Key(s32 k) {
    if ((u32)k < 4) {
        k = -1;
    }
    return k;
}

extern "C" bool InvOrganizeMaybe_3c50c0(Inv *self, s32 kind, s32 cat, u32 flags)
{
    s32 i2;
    s32 n;
    bool sw;
    s32 i;
    s32 j;
    s32 mode;
    Item *a;
    bool changed;
    s32 t;
    s32 lo;
    s32 s2;
    s32 r;
    Item *f;
    s32 last;
    s32 hi;
    Item *b;
    bool gt;
    s32 s;
    s32 d;
    s32 k;
    s32 cnt;
    Item *e;
    s32 id;

    if (self->x168 == 0) {
        return 0;
    }
    InvFreeCategory8Items_3c8d70(self);
    if (self->x168 != 0) {
        n = D_00465B50[0];
        for (i = 0; i < n; i++) {
            { Item *t_bt = PoolGetUsedElem_36acb0(self->x168, i); e = t_bt; }
            if (e == 0) {
                continue;
            }
            if (e->xA1) {
                e->Kill();
                PoolFreeElem_36a8e0(self->x168, i);
            }
        }
    }
    lo = -1;
    hi = lo;
    switch (kind) {
    case 0:
        lo = D_00465A08[0];
        hi = D_00465A10[0];
        if (cat >= 0 && cat < D_004659E8[0]) {
            lo += D_00465A00[0] * cat;
            hi = lo + D_00465A00[0] - 1;
        }
        break;
    case 1:
        lo = D_00465A38[0];
        hi = D_00465A40[0];
        if (cat >= 0 && cat < D_00465A18[0]) {
            lo += D_00465A30[0] * cat;
            hi = lo + D_00465A30[0] - 1;
        }
        break;
    }
    if (lo < 0) {
        goto fail;
    }
    if (hi < 0) {
    fail:
        return 0;
    }
    changed = false;
    if (flags & 1) {
        n = D_00465B50[0];
        for (i2 = 0; i2 < n; i2++) {
            e = PoolGetUsedElem_36acb0(self->x168, i2);
            if (e == 0) {
                continue;
            }
            if (e->xA1) {
                continue;
            }
            id = e->x6;
            if (id < lo || id > hi) {
                continue;
            }
            if (!ItemHasCountFlag_3d44e0(e)) {
                continue;
            }
            if (!(e->Num() < ItemGetStackLimit_3d4480(e))) {
                continue;
            }
            t = e->x10->x0;
            k = e->x6 + 1;
            for (j = id; j < hi; j++) {
                f = InvFindInCategoryRange_3c8370(self, t, kind, k, 0, 0);
                if (f == 0) {
                    break;
                }
                k = f->x6 + 1;
                r = InvMoveItemMaybe_3c5b10(self, f, id, -1, 0, 0, 0, 0);
                if (r != 0) {
                    changed = true;
                }
                if (r == 0) {
                    break;
                }
                if (r == 5) {
                    break;
                }
            }
        }
    }
    cnt = 0;
    n = D_00465B50[0];
    for (i = 0; i < n; i++) {
        e = PoolGetUsedElem_36acb0(self->x168, i);
        if (e == 0) {
            continue;
        }
        if (e->xA1) {
            continue;
        }
        id = e->x6;
        if (id < lo || id > hi) {
            continue;
        }
        cnt++;
    }
    if (cnt == 0) {
        return 0;
    }
    if (flags & 2) {
        for (s = lo; s < hi; s++) {
            if (InvFindByInvId_3c87d0(self, s, 0) != 0) {
                continue;
            }
            d = s;
            for (t = s + 1; !(hi < t); t++) {
                f = InvFindByInvId_3c87d0(self, t, 0);
                if (f == 0) {
                    continue;
                }
                f->x6 = d;
                d++;
                changed = true;
                if (!(d < t)) {
                    break;
                }
            }
            if (d == s) {
                break;
            }
        }
    }
    mode = flags & 0x70;
    if (mode != 0) {
        last = lo + cnt - 1;
        do {
            a = InvFindByInvId_3c87d0(self, lo, 0);
            if (a == 0) {
                break;
            }
            sw = false;
            for (s2 = lo + 1; !(last < s2); s2++) {
                s32 x;
                s32 y;
                Dat *da;
                Dat *db;
                s32 ka;
                s32 kb;
                b = InvFindByInvId_3c87d0(self, s2, 0);
                if (b == 0) {
                    break;
                }
                gt = false;
                da = a->x10;
                db = b->x10;
                ka = da->x2;
                kb = db->x2;
                x = ka;
                y = (s32)(u32)kb;
                if ((u32)ka < 4) {
                    x = -1;
                }
                if ((u32)y < 4) {
                    y = -1;
                }
                switch (mode) {
                case 0x10:
                    break;
                case 0x20:
                    if (x == 4) {
                        x = -3;
                    } else if (x == 5 || x == 0xF) {
                        x = -2;
                    }
                    if (y == 4) {
                        y = -3;
                    } else if (y == 5 || y == 0xF) {
                        y = -2;
                    }
                    break;
                case 0x30:
                    if (x == 5 || x == 0xF) {
                        x = -3;
                    } else if (x == 4) {
                        x = -2;
                    }
                    if (y == 5 || y == 0xF) {
                        y = -3;
                    } else if (y == 4) {
                        y = -2;
                    }
                    break;
                }
                if (y < x) {
                    gt = true;
                } else if (x == y) {
                    s32 va = a->x10->x8;
                    s32 vb = b->x10->x8;
                    if (va < 0) {
                        va = 99999;
                    }
                    if (vb < 0) {
                        vb = 99999;
                    }
                    if (vb < va) {
                        gt = true;
                    } else if (va == vb) {
                        if (kb < ka) {
                            gt = true;
                        } else if (ka == kb) {
                            if (b->x10->x4 < a->x10->x4) {
                                gt = true;
                            } else if (a->x10->x4 == b->x10->x4) {
                                if (b->x10->x3 < a->x10->x3) {
                                    gt = true;
                                } else if (a->x10->x3 == b->x10->x3) {
                                    if (b->x10->x6 < a->x10->x6) {
                                        gt = true;
                                    } else if (a->x10->x6 == b->x10->x6) {
                                        s32 ra = a->Rank();
                                        s32 rb = b->Rank();
                                        if (rb < ra) {
                                            gt = true;
                                        } else if (ra == rb) {
                                            if (b->x10->x0 < a->x10->x0) {
                                                gt = true;
                                            } else if (a->x10->x0 == b->x10->x0) {
                                                s32 na = a->Num();
                                                s32 nb = b->Num();
                                                if (na < nb) {
                                                    gt = true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (gt) {
                    sw = true;
                    a->x6 = s2;
                    b->x6 = s2 - 1;
                    changed = sw;
                } else {
                    a = b;
                }
            }
        } while (sw);
    }
    return changed;
}
