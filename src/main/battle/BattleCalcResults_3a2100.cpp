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
    virtual void d0();
    virtual void d1();
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
    virtual Def *Get(s32);
};

class Clock {
public:
    virtual void d0();
    virtual void d1();
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
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual s32 Now();
};

class Equip {
public:
    virtual void d0();
    virtual void d1();
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
    virtual s32 v60();
    virtual s32 v64();
    virtual void d24();
    virtual void v6C(s32);
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual s32 v90(s32);
    virtual s32 v94(s32);
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void vA4(s32, s32);
};

class Mem {
public:
    virtual void d0();
    virtual void d1();
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
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual s32 vE8();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void d109();
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual void d137();
    virtual void d138();
    virtual void d139();
    virtual void d140();
    virtual void d141();
    virtual void d142();
    virtual void d143();
    virtual void d144();
    virtual void d145();
    virtual void d146();
    virtual void d147();
    virtual void d148();
    virtual void d149();
    virtual void d150();
    virtual void d151();
    virtual void d152();
    virtual void d153();
    virtual void d154();
    virtual void d155();
    virtual void d156();
    virtual void d157();
    virtual void d158();
    virtual void d159();
    virtual void d160();
    virtual void d161();
    virtual void d162();
    virtual void d163();
    virtual void d164();
    virtual void d165();
    virtual void d166();
    virtual void d167();
    virtual void d168();
    virtual void d169();
    virtual void d170();
    virtual void d171();
    virtual void d172();
    virtual void d173();
    virtual void d174();
    virtual void d175();
    virtual void d176();
    virtual void d177();
    virtual void d178();
    virtual void d179();
    virtual void d180();
    virtual void d181();
    virtual void d182();
    virtual void d183();
    virtual void d184();
    virtual void d185();
    virtual void d186();
    virtual void d187();
    virtual void d188();
    virtual void d189();
    virtual void d190();
    virtual void d191();
    virtual void d192();
    virtual void d193();
    virtual void d194();
    virtual void d195();
    virtual void d196();
    virtual void d197();
    virtual void d198();
    virtual void d199();
    virtual void d200();
    virtual void d201();
    virtual void d202();
    virtual void d203();
    virtual void d204();
    virtual void d205();
    virtual void d206();
    virtual void d207();
    virtual void d208();
    virtual void d209();
    virtual void d210();
    virtual void d211();
    virtual void d212();
    virtual void d213();
    virtual void d214();
    virtual void d215();
    virtual void d216();
    virtual void d217();
    virtual void d218();
    virtual void d219();
    virtual void d220();
    virtual void d221();
    virtual void d222();
    virtual Equip *GetEquip(s32);
    virtual void d224();
    virtual void d225();
    virtual void d226();
    virtual void d227();
    virtual void d228();
    virtual void d229();
    virtual void d230();
    virtual void d231();
    virtual void d232();
    virtual void d233();
    virtual void d234();
    virtual void d235();
    virtual void d236();
    virtual void d237();
    virtual void d238();
    virtual void d239();
    virtual void d240();
    virtual void d241();
    virtual void d242();
    virtual void d243();
    virtual void d244();
    virtual void d245();
    virtual void d246();
    virtual void d247();
    virtual void d248();
    virtual void d249();
    virtual void d250();
    virtual void d251();
    virtual void d252();
    virtual void d253();
    virtual void d254();
    virtual void d255();
    virtual void d256();
    virtual void d257();
    virtual void d258();
    virtual void d259();
    virtual void d260();
    virtual void d261();
    virtual s32 v420();
    virtual void d263();
    virtual void d264();
    virtual void d265();
    virtual void d266();
    virtual void d267();
    virtual void d268();
    virtual void d269();
    virtual void d270();
    virtual void d271();
    virtual void d272();
    virtual void v44C(s32, s32 *);
    virtual void d274();
    virtual void d275();
    virtual void d276();
    virtual void d277();
    virtual void d278();
    virtual void d279();
    virtual void d280();
    virtual void d281();
    virtual void d282();
    virtual void d283();
    virtual void d284();
    virtual void d285();
    virtual void d286();
    virtual void d287();
    virtual void d288();
    virtual void d289();
    virtual void d290();
    virtual void d291();
    virtual void d292();
    virtual void d293();
    virtual void d294();
    virtual s32 v4A4();
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
    s32 ids[16];
    s32 cnts[16];
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
