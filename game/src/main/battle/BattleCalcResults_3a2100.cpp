#include "types.h"
#pragma usefloatacc off
#pragma opt_loop_invariants off

typedef struct { u8 b0:1; u8 b1:1; u8 b2:1; u8 b3:1; u8 b4:1; u8 b5:1; u8 b6:1; u8 b7:1; } Bits;

struct Unit {
    u8 pad0[0x7D];
    s8 lo7D : 2;
    s8 n7D : 6;
    s8 b7E : 1;
    s8 r7E : 7;
    u8 pad7F[0x88 - 0x7F];
    s16 **m88;
};

struct Sub {
    u8 pad0[0x18];
    Unit *m18;
    u8 pad1C[0x2C - 0x1C];
    s16 m2C;
    s16 m2E;
    u8 pad30[0x170 - 0x30];
    s16 m170;
    Bits m172;
    u8 pad173[0x1C2 - 0x173];
    s16 m1C2;
    s16 m1C4;
    u8 m1C6;
};

struct Slot {
    s16 id;
    s16 n;
};

struct EqEnt {
    s16 x10;
    s16 x12;
};

struct Ent {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s32 x8;
    s32 xC;
    EqEnt e[2];
};

struct Res {
    s32 m0;
    Ent ent[10];
    s16 mF4;
    s16 cnt;
    Slot slot[1];
};

struct Item {
    s16 id;
    s16 type;
    u8 pad4[0xC];
};

struct Obj {
    u8 pad0[0x238];
    Sub *m238;
    Item *m23C;
    s32 m240;
    u8 pad244[4];
    Res *m248;
};

struct PM {
    u8 pad0[4];
    s16 m4;
    u8 pad6[0x160 - 6];
    s64 m160;
};

struct Glob {
    u8 pad0[0x10];
    s32 m10;
    void *m14;
    PM *m18;
    u8 pad1C[4];
    s32 m20;
};

struct DefE {
    s16 id;
    s16 pct;
};

struct Def {
    s16 m0;
    u8 pad2[0x2C - 2];
    u16 m2C;
    u8 pad2E[0x94 - 0x2E];
    s16 m94;
    s16 m96;
    s16 m98;
    s16 m9A;
    DefE *m9C;
};

struct LvE {
    u8 pad0[2];
    s16 m2;
};

struct MemD {
    u8 pad0[0xC];
    s32 mC;
    u8 pad10[0x234 - 0x10];
    Bits m234;
};

struct EqD {
    u8 pad0[4];
    s16 m4;
};

class Lookup {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Def * Get(s32 a0) { return VCM(Def *, (void *, s32), 0x70, a0); }
};

class Clock {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Now() { return VCM0(s32, 0xE8); }
};

class Equip {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v60() { return VCM0(s32, 0x60); }
    s32 v64() { return VCM0(s32, 0x64); }
    
    void v6C(s32 a0) { VCM(void, (void *, s32), 0x6C, a0); }
    
    
    
    
    
    
    
    
    s32 v90(s32 a0) { return VCM(s32, (void *, s32), 0x90, a0); }
    s32 v94(s32 a0) { return VCM(s32, (void *, s32), 0x94, a0); }
    
    
    
    void vA4(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0xA4, a0, a1); }
};

class Mem {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vE8() { return VCM0(s32, 0xE8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Equip * GetEquip(s32 a0) { return VCM(Equip *, (void *, s32), 0x384, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v420() { return VCM0(s32, 0x420); }
    
    
    
    
    
    
    
    
    
    
    void v44C(s32 a0, s32 * a1) { VCM(void, (void *, s32, s32 *), 0x44C, a0, a1); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v4A4() { return VCM0(s32, 0x4A4); }
};

struct LkHold {
    u8 pad0[0xC];
    Lookup *mC;
};

struct G2 {
    u8 pad0[0x64];
    LkHold *m64;
};

extern "C" {
extern Glob *D_004837C0;
extern G2 *D_004837C4;
extern s32 D_00465C90[];
extern f32 D_0047D240;
extern f32 D_0047D248;
extern f32 D_0047D28C;
extern f32 D_0047D33C;
extern f32 D_0047D340;
extern f32 D_0047D344;
extern f32 D_0047D348;
extern f32 D_0047D34C;
void CharaSysBattleResultReset_3a31b0(Obj *);
s32 InvAddItemCoreMaybe_3c6540(PM *, s32, s32, s32, s32, s32, s32);
void StateFlagSet_3ccb70(s32, s32, s32, s32);
void PlayStatBumpChallengeClearedMaybe_3a19c0(Obj *, s32);
void PlayStatBumpMemberChallengeClearedMaybe_3a18c0(Obj *, s32);
s32 PartyCountMembers_3c2010(PM *, s32, s32);
s32 PartyCountReserve_3c1c20(PM *, s32, s32);
void PlayStatBumpExpBonusMaybe_3a1870(s32);
Clock *CharaMgrPoolFindByDataId_3a8a70(void *, s32, s32, s32, s32, s32, s32);
LvE *BestiaryCountFindMaybe_3c3440(PM *, s32);
void BestiaryCountBumpMaybe_3c3300(PM *, s32);
f32 RandFloat_13c010(void);
void PartyAddMoney_3c8e90(PM *, s64);
Mem *PartyGetSlotChara_3c2fb0(PM *, s32);
s32 CharaIsInParty_3ae1d0(Mem *);
s32 CharaIsInReserve_3ae0e0(Mem *);
void PlayStatSetLevelMaybe_3a1c20(Obj *, s32, s32);
}

static inline void Give(Obj *o, s32 id)
{
    s32 idx;
    Res *r;
    Slot *s;
    s32 n;
    s32 i;

    r = o->m248;
    idx = -1;
    n = r->cnt;
    for (i = 0, s = r->slot; i < n; i++, s++) {
        if (s->id == id) {
            idx = i;
            break;
        }
    }
    if (idx >= 0 || n < 3) {
        if (idx >= 0) {
            if (s->n < 0x63) {
                Slot *q = r->slot + idx;
                q->n++;
            }
        } else {
            Slot *q = r->slot + n;
            q->id = id;
            q->n = 1;
            o->m248->cnt++;
        }
        if (InvAddItemCoreMaybe_3c6540(D_004837C0->m18, id, 0, 1, -1, 0, 0) == 0 &&
            InvAddItemCoreMaybe_3c6540(D_004837C0->m18, id, 9, 1, -1, 0, 0) != 0) {
            StateFlagSet_3ccb70(D_004837C0->m10, 0x7F8, 1, 1);
        }
    }
}

extern "C" s32 BattleCalcResults_3a2100(Obj *o)
{
    s32 out;
    s32 ids[16] __attribute__((aligned(16)));
    s32 cnts[16] __attribute__((aligned(16)));
    bool lock;
    s32 d;
    s32 cnt;
    Def *def;
    f32 f;
    Res *r;
    s32 nids;
    s32 sum;
    f32 fp;
    s16 **lst;
    s32 v;
    f32 acc;
    PM *pm;
    s32 t;
    s32 day;
    s32 prod;
    bool found;
    bool flag;
    s32 n;
    Sub *sub;
    Item *it;
    s16 *p;
    s32 nMem;
    s32 i;
    Equip *e1;
    s32 x1;
    s32 i2;
    s32 i3;
    Unit *unit;
    LvE *le;
    s32 id;
    s32 lv;
    s32 j;
    s64 old;
    DefE *de;
    Equip *e;
    s32 bonus;
    bool dead;
    Ent *pr;
    Mem *m;
    s32 x;
    s32 val;
    s32 s;
    s32 k;
    s16 tmp;
    s32 q;
    s32 mx;
    bool ok;
    s32 y;
    s16 a;
    EqEnt *ent;

    if (o->m248 == 0) {
        return 0;
    }
    if (D_004837C0 == 0) {
        return 0;
    }
    CharaSysBattleResultReset_3a31b0(o);
    o->m238->m170 = 0;
    sub = o->m238;
    lock = 0;
    switch (sub->m2C) {
    case 1:
        if (sub->m172.b5 && sub->m172.b0 && !sub->m172.b2) {
            sub->m170 = 1;
        } else {
            sub->m170 = 2;
        }
        lock = 1;
        break;
    case 2:
        if (sub->m172.b5 && sub->m172.b0 && !sub->m172.b3 && !sub->m172.b4) {
            sub->m170 = 1;
        } else {
            sub->m170 = 2;
        }
        lock = 1;
        break;
    case 3:
        if (sub->m172.b5 && !sub->m172.b1) {
            sub->m170 = 1;
        } else {
            sub->m170 = 2;
        }
        lock = 1;
        break;
    case 4:
        if (sub->m172.b5 && sub->m172.b0) {
            sub->m170 = 1;
        } else {
            sub->m170 = 2;
        }
        lock = 1;
        break;
    }
    if (o->m238->m170 == 1) {
        r = o->m248;
        r->slot[0].id = 0x40FE;
        r->slot[0].n = 1;
        o->m248->cnt++;
        if (InvAddItemCoreMaybe_3c6540(D_004837C0->m18, 0x40FE, 0, 1, -1, 0, 0) == 0 &&
            InvAddItemCoreMaybe_3c6540(D_004837C0->m18, 0x40FE, 9, 1, -1, 0, 0) != 0) {
            StateFlagSet_3ccb70(D_004837C0->m10, 0x7F8, 1, 1);
        }
        PlayStatBumpChallengeClearedMaybe_3a19c0(o, o->m238->m2C);
        if (o->m238->m2C == 1) {
            PlayStatBumpMemberChallengeClearedMaybe_3a18c0(o, o->m238->m2E);
        }
    }
    if (o->m238 != 0) {
        unit = o->m238->m18;
    } else {
        unit = 0;
    }
    if (unit != 0) {
        n = unit->n7D;
        lst = unit->m88;
        if (n > 0 && lst != 0) {
            for (i = 0; i < n; i++, lst++) {
                p = *lst;
                if (p != 0) {
                    Give(o, *p);
                }
            }
        }
    }
    pm = D_004837C0->m18;
    nMem = PartyCountMembers_3c2010(pm, 1, 1) + PartyCountReserve_3c1c20(pm, 1, 1);
    x = PartyCountMembers_3c2010(D_004837C0->m18, 1, 1);
    flag = 0;
    if (x >= 2) {
        sub = o->m238;
        if (sub->m1C2 > sub->m1C4) {
            flag = 1;
        }
        if (unit != 0 && unit->b7E) {
            flag = 0;
        }
        if (lock) {
            flag = 0;
        }
        sub->m1C6 = flag;
    }
    if (flag) {
        PlayStatBumpExpBonusMaybe_3a1870(D_004837C0->m20);
    }
    day = CharaMgrPoolFindByDataId_3a8a70(D_004837C0->m14, 0x2AF9, 1, 1, 0, 0, 0)->Now();
    nids = 0;
    for (i = 0; i < o->m240; i++) {
        it = &o->m23C[i];
        if (it->type != 2) {
            continue;
        }
        id = it->id;
        if (D_004837C4->m64->mC->Get(id) != 0) {
            found = 0;
            for (j = 0; j < nids; j++) {
                if (id == ids[j]) {
                    found = 1;
                    cnts[j]++;
                }
            }
            if (!found) {
                ids[nids] = id;
                cnts[nids] = 1;
                nids++;
            }
        }
    }
    sum = 0;
    acc = 0.0f;
    for (i2 = 0; i2 < nids; i2++) {
        s = ids[i2];
        cnt = cnts[i2];
        def = D_004837C4->m64->mC->Get((s16)s);
        if (def == 0) {
            continue;
        }
        t = def->m2C;
        v = def->m94;
        lv = 0;
        le = BestiaryCountFindMaybe_3c3440(D_004837C0->m18, s);
        if (le != 0) {
            lv = le->m2;
        }
        f = 1.0f;
        if (lv > 100) {
            if (lv < 0x79) {
                f *= D_0047D33C;
            } else if (lv < 0x8D) {
                f *= D_0047D248;
            } else if (lv < 0xA1) {
                f *= D_0047D340;
            } else if (lv < 0xB5) {
                f *= 0.5f;
            } else if (lv < 0xC9) {
                f *= D_0047D344;
            } else if (lv < 0x12D) {
                f *= D_0047D240;
            } else {
                f *= D_0047D348;
            }
        }
        d = day - t;
        if (d > 15) {
            if (d < 0x15) {
                f *= D_0047D248;
            } else if (d < 0x1A) {
                f *= D_0047D28C;
            } else {
                f *= D_0047D34C;
            }
        }
        if (D_004837C0->m18->m4 == 0xA) {
            f = 1.0f;
        }
        prod = v * cnt;
        sum += prod;
        fp = (f32)prod * f;
        acc += fp;
    }
    o->m248->m0 = acc;
    r = o->m248;
    if (r->m0 <= 0) {
        if (sum > 0) {
            r->m0 = 1;
        } else {
            r->m0 = 0;
        }
    }
    x = D_00465C90[0];
    r = o->m248;
    if (x < r->m0) {
        r->m0 = x;
    }
    for (i3 = 0; i3 < o->m240; i3++) {
        it = &o->m23C[i3];
        if (it->type != 2) {
            continue;
        }
        def = D_004837C4->m64->mC->Get(it->id);
        if (def == 0) {
            continue;
        }
        BestiaryCountBumpMaybe_3c3300(D_004837C0->m18, def->m0);
        acc = 1.0f + ((f32)def->m98 - (f32)def->m96);
        val = def->m96 + (s32)(acc * RandFloat_13c010());
        old = D_004837C0->m18->m160;
        PartyAddMoney_3c8e90(D_004837C0->m18, val);
        o->m248->mF4 += (s16)(D_004837C0->m18->m160 - old);
        for (j = 0, de = def->m9C; j < def->m9A; j++, de++) {
            id = de->id;
            y = de->pct;
            if (id >= 0 && y > 0 && (s32)(100.0f * RandFloat_13c010()) < de->pct) {
                Give(o, id);
            }
        }
    }
    mx = D_00465C90[0];
    pr = o->m248->ent;
    for (k = 0; k < nMem; k++, pr++) {
        val = o->m248->m0;
        if (val < 0) {
            val = 0;
        }
        if (mx < val) {
            val = mx;
        }
        pr->x0 = -1;
        pr->x4 = 0;
        pr->x8 = 0;
        pr->x2 = 0;
        pr->x6 = 0;
        pr->xC = 0;
        m = PartyGetSlotChara_3c2fb0(D_004837C0->m18, k);
        if (m == 0) {
            continue;
        }
        if (CharaIsInParty_3ae1d0(m) == 0) {
            continue;
        }
        pr->x0 = ((MemD *)m)->mC;
        {
            Equip *eq[2] = {0};
            j = 0;
            do {
                e = m->GetEquip(j);
                eq[j] = e;
                a = -1;
                if (e != 0) {
                    a = ((EqD *)e)->m4;
                }
                ent = pr->e + j;
                ent->x10 = a;
                ent->x12 = 0;
                j++;
            } while (j < 2);
            pr->x4 = m->vE8();
            pr->x8 = m->v420();
            ok = 1;
            dead = 0;
            if (((MemD *)m)->m234.b2) {
                val = D_0047D248 * (f32)val;
                ok = 0;
            } else if (m->v4A4() != 0) {
                val = 0;
                ok = 0;
                dead = 1;
            } else if (CharaIsInReserve_3ae0e0(m) != 0) {
                ok = 0;
                val = D_0047D248 * (f32)val;
            }
            bonus = 0;
            if (val > 0 && flag) {
                bonus = D_0047D34C * (f32)val;
            }
            if (!dead && val <= 0) {
                if (sum > 0) {
                    val = 1;
                } else {
                    val = 0;
                }
            }
            if (val > 0) {
                val += bonus;
            }
            if (mx < val) {
                val = mx;
            }
            out = 0;
            m->v44C(val, &out);
            pr->x2 = out;
            pr->x6 = m->vE8();
            pr->xC = m->v420();
            if (ok) {
                j = 0;
                do {
                    e1 = eq[j];
                    if (e1 != 0) {
                        ent = &pr->e[j];
                        x1 = e1->v64();
                        if (e1->v60() < x1) {
                            ent->x12 |= 1;
                            e1->v6C(1);
                        } else {
                            s16 perm[5];
                            ent->x12 |= 0x100;
                            q = 0;
                            do {
                                perm[q] = q;
                                q++;
                            } while (q < 5);
                            q = 0;
                            do {
                                x1 = 5.0f * RandFloat_13c010();
                                y = 5.0f * RandFloat_13c010();
                                q++;
                                tmp = perm[x1];
                                perm[x1] = perm[y];
                                perm[y] = tmp;
                            } while (q < 20);
                            for (q = 0; q < 5; q++) {
                                s = perm[q];
                                if (e1->v90(s) < e1->v94(s)) {
                                    e1->vA4(s, 1);
                                    switch (s) {
                                    case 0:
                                        ent->x12 |= 2;
                                        break;
                                    case 1:
                                        ent->x12 |= 4;
                                        break;
                                    case 2:
                                        ent->x12 |= 8;
                                        break;
                                    case 3:
                                        ent->x12 |= 0x10;
                                        break;
                                    case 4:
                                        ent->x12 |= 0x20;
                                        break;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    j++;
                } while (j < 2);
            }
            j = 0;
            do {
                e = eq[j];
                if (e != 0) {
                    ent = &pr->e[j];
                    x = e->v64();
                    if (!(e->v60() < x)) {
                        ent->x12 |= 0x100;
                    }
                    q = 0;
                    do {
                        if (!(e->v90(q) < e->v94(q))) {
                            switch (q) {
                            case 0:
                                ent->x12 |= 0x200;
                                break;
                            case 1:
                                ent->x12 |= 0x400;
                                break;
                            case 2:
                                ent->x12 |= 0x800;
                                break;
                            case 3:
                                ent->x12 |= 0x1000;
                                break;
                            case 4:
                                ent->x12 |= 0x2000;
                                break;
                            }
                        }
                        q++;
                    } while (q < 5);
                    if ((ent->x12 & 0x3F00) == 0x3F00) {
                        ent->x12 |= 0x8000;
                    }
                }
                j++;
            } while (j < 2);
        }
    }
    for (k = 0; k < nMem; k++) {
        m = PartyGetSlotChara_3c2fb0(D_004837C0->m18, k);
        if (m != 0) {
            x = ((MemD *)m)->mC;
            PlayStatSetLevelMaybe_3a1c20(o, x, m->vE8());
        }
    }
    return 1;
}
