#include "types.h"

extern "C" {

class Tbl {
public:
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual s8 *Find(s16 id);
};

typedef struct X40 {
    u8 pad0[8];
    Tbl *tbl;
} X40;

typedef struct Z98 {
    u8 pad0[0x10];
    u8 *p10;
} Z98;

typedef struct X8 {
    u8 pad0[0x40];
    X40 *p40;
    u8 pad44[0x54];
    Z98 *p98;
} X8;

typedef struct Hdl {
    u8 pad0[4];
    s16 h4;
    u8 pad6[0x34];
    s16 n3A;
    s16 n3C;
} Hdl;

typedef struct Ctx {
    u8 pad0[8];
    X8 *p8;
    u8 padC[0xC];
    Hdl *p18;
} Ctx;

typedef struct Unit {
    u8 pad0[0x10];
    s16 *p10;
    u8 pad14[4];
    s16 *p18;
} Unit;

typedef struct Ent4 {
    s16 id;
    u8 w;
    u8 k;
} Ent4;

typedef struct Grp {
    u8 pad0[2];
    s16 n;
    Ent4 *e;
} Grp;

typedef struct Node {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    u8 pad6[4];
    s16 n;
    u8 padC[8];
    Grp **g;
} Node;

typedef struct Info {
    u8 pad0[0x20];
    s16 lv[3];
    s16 h26;
    s16 h28;
    s16 h2A;
} Info;

typedef struct ActB {
    u8 pad0[0xA];
    bool bA : 1;
    u8 padB[3];
    bool bE : 1;
} ActB;

typedef struct Iter {
    u8 d[8];
} Iter;

f32 RandFloat_13c010(void);
Node *IterNext_370040(Iter *);
Node *IterReset_3700f0(Iter *);
void IterInit_370170(Iter *, u8 *);
s16 *PartyLookupRadiusZoneMaybe_3cb060(Hdl *, s32);
s16 *PartyLookupKeyedZoneMaybe_3cb0b0(Hdl *, s32);
u8 *CageRecAddEntry_3d0830(Unit *);
void CageRecClearEntries_3d0950(Unit *);
Info *ItemDefGetInsectData_40e0b0(s8 *);
extern s32 D_00466B00[];
extern s32 D_00466B20[];

#pragma optimization_level 3
#pragma opt_dead_assignments off
s32 CageRecRollCatchesMaybe_3e8510(Ctx *c, Unit *u)
{
    Iter it;
    s32 ids[16];
    s16 cid[128];
    s16 cw[128];
    s16 cwt[128];
    s32 k16;
    Hdl *h;
    s32 n;
    s32 m;
    s32 i;
    s16 *e;
    s32 me;
    s32 lim;
    Node *found;
    Node *fb;
    Node *nd;
    s32 pass;
    bool hit;
    s32 j;
    s32 lo;
    s32 hi;
    bool flag2;
    s32 cnt;
    s32 total;
    s32 r;
    s32 *pr;
    s32 pick;
    s32 id;
    s32 idx;
    s32 prev;
    s32 w2;
    s32 acc;
    s8 *ent;
    Info *info;
    s32 lv;
    bool b;
    s32 rr;
    u8 *act;
    bool done;
    Grp **gl;
    s32 k;
    Grp *g;
    Ent4 *ea;
    s32 num;
    u8 *q;
    s8 *self;

    if (u == 0) {
        return 0;
    }
    CageRecClearEntries_3d0950(u);
    k16 = *u->p10;
    self = c->p8->p40->tbl->Find(k16);
    if (self == 0) {
        return 0;
    }
    self = (s8 *)(u32)self;
    k16 = u->p18[1];
    if (c->p8->p40->tbl->Find(k16) == 0) {
        return 0;
    }
    n = 0;
    m = 0;
    me = c->p18->h4;
    lim = c->p18->n3C;
    for (i = 0; i < lim; i++) {
        e = PartyLookupRadiusZoneMaybe_3cb060(c->p18, i);
        if (e == 0) {
            continue;
        }
        if (m >= 16) {
            break;
        }
        n++;
        ids[m++] = *e;
    }
    lim = c->p18->n3A;
    for (i = 0; i < lim; i++) {
        e = PartyLookupKeyedZoneMaybe_3cb0b0(c->p18, i);
        if (e == 0) {
            continue;
        }
        if (m >= 16) {
            break;
        }
        ids[m++] = *e;
    }
    q = c->p8->p98->p10;
    found = 0;
    if (q != 0) {
        q += 0x88;
    }
    IterInit_370170(&it, q);
    fb = 0;
    for (pass = 1; pass <= 2; pass++) {
        IterReset_3700f0(&it);
        while ((nd = IterNext_370040(&it)) != 0) {
            if (nd->h2 != me) {
                continue;
            }
            hit = false;
            lo = 0;
            hi = n;
            if (pass == 2) {
                lo = n;
                hi = m;
            }
            for (j = lo; j < hi; j++) {
                s32 v = ids[j];
                if (fb == 0 && nd->h4 < 0) {
                    fb = nd;
                }
                if (v == nd->h4) {
                    hit = true;
                    break;
                }
            }
            if (hit) {
                found = nd;
                break;
            }
        }
        if (found != 0) {
            break;
        }
    }
    if (found == 0 && fb != 0) {
        found = fb;
    }
    flag2 = false;
    if (found != 0) {
        cnt = 0;
        total = 0;
        gl = found->g;
        for (k = 0; k < found->n; k++, gl++) {
            g = *gl;
            if (g == 0) {
                continue;
            }
            ea = g->e;
            num = g->n;
            for (j = 0; j < num; j++, ea++) {
                if (ea->id == 0x424A) {
                    if (k16 != 0x410D) {
                        continue;
                    }
                    flag2 = true;
                }
                {
                    s32 kk = ea->k;
                    s32 x = cnt;
                    cwt[x] = D_00466B00[kk];
                    cw[x] = ea->w;
                    cid[x] = ea->id;
                    cnt++;
                    total += D_00466B00[kk];
                }
            }
        }
        for (r = 0; r < 5; r++) {
            done = true;
            pick = (s32)((f32)total * RandFloat_13c010());
            pr = &D_00466B20[r];
            acc = 0;
            for (idx = 0; idx < cnt; idx++) {
                prev = acc;
                w2 = cw[idx];
                id = cid[idx];
                acc += cwt[idx];
                if (id < 0) {
                    continue;
                }
                if (pick < prev) {
                    continue;
                }
                if (!(pick < acc)) {
                    continue;
                }
                ent = c->p8->p40->tbl->Find(id);
                if (ent == 0) {
                    continue;
                }
                info = ItemDefGetInsectData_40e0b0(ent);
                if (info == 0) {
                    continue;
                }
                lv = info->lv[self[3]];
                if (lv <= 0) {
                    continue;
                }
                b = false;
                if (info->h2A == k16) {
                    b = true;
                }
                if (!flag2 && k16 == 0x410D) {
                    b = true;
                }
                if (b) {
                    act = CageRecAddEntry_3d0830(u);
                    *(s16 *)(act + 2) = *pr * 1800;
                    *(s16 *)(act + 4) = 3;
                    *(s16 *)(act + 8) = idx;
                    ((ActB *)act)->bA = false;
                    ((ActB *)act)->bE = false;
                    continue;
                }
                if (info->h26 != k16 && info->h28 != k16) {
                    lv -= 30;
                }
                if (lv < 0) {
                    lv = 0;
                }
                rr = (s32)(100.0f * RandFloat_13c010());
                if (r >= 5) {
                    rr = 0;
                }
                if (flag2) {
                    rr = 0;
                }
                if (rr <= lv) {
                    if (flag2) {
                        id = 0x424A;
                        w2 = 0;
                    }
                    act = CageRecAddEntry_3d0830(u);
                    done = false;
                    *(s16 *)(act + 2) = *pr * 1800;
                    *(s16 *)(act + 4) = 1;
                    *(s16 *)(act + 8) = idx;
                    *(s16 *)(act + 0xA) = id;
                    *(s16 *)(act + 0xC) = w2;
                    ((ActB *)act)->bE = false;
                } else {
                    act = CageRecAddEntry_3d0830(u);
                    done = false;
                    *(s16 *)(act + 2) = *pr * 1800;
                    *(s16 *)(act + 4) = 2;
                    *(s16 *)(act + 8) = idx;
                    ((ActB *)act)->bA = true;
                    ((ActB *)act)->bE = false;
                }
                break;
            }
            if (!done) {
                break;
            }
        }
    }
    return 1;
}

}
