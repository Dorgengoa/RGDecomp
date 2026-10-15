#pragma opt_loop_invariants off
#include "types.h"
#pragma optimization_level 3

typedef struct Nib {
    s8 lo:4;
    s8 hi:4;
} Nib;

typedef struct UNib {
    u8 lo:4;
    u8 hi:4;
} UNib;

typedef struct Unit4440 {
    s16 m0;
    u8 pad2[0x2A];
    u16 m2C;
} Unit4440;

typedef struct Item4440 {
    Unit4440 *u;
    Nib m4;
    Nib m5;
    u8 pad6[6];
} Item4440;

typedef struct Src4440 {
    u8 pad0[0xA];
    s16 mA;
    u8 padC[4];
    Nib m10;
    Nib m11;
    Nib m12;
    u8 pad13;
    UNib m14;
    u8 m15:7;
    u8 m15b:1;
    Nib m16;
    u8 pad17;
    Item4440 *items;
} Src4440;

typedef struct Ent4440 {
    s16 a;
    s16 b;
    void *obj;
} Ent4440;

typedef struct Desc4440 {
    u64 m0;
    s16 m8;
    s16 mA;
    s16 mC;
    u8 padE[2];
    s32 m10;
    Src4440 *m14;
    s32 m18;
    u8 pad1C[0xC];
    s32 m28;
    s16 m2C;
    s16 m2E;
    f32 m30;
    u8 pad34[0xC];
    f32 m40;
    s16 m44;
    u8 pad46[2];
    Ent4440 ent[28];
    u8 pad128[0x162 - 0x128];
    s16 m162;
    s16 m164;
    s16 m166;
    u8 m168[4];
    s32 m16C;
    u8 pad170[2];
    u8 b0:1;
    u8 b1:1;
    u8 b2:1;
    u8 b3:1;
    u8 b4:1;
    u8 b5:3;
    u8 pad173[0x1C8 - 0x173];
} Desc4440;

typedef struct Base4440 {
    u8 pad0[0xC6];
    s16 mC6;
    s16 mC8;
    u8 padCA[3];
    s8 mCD;
    s8 mCE;
    s8 mCF;
    s8 mD0;
} Base4440;

typedef struct S54 {
    u8 pad0[8];
    Base4440 *m8;
} S54;

typedef struct S8 {
    u8 pad0[0x54];
    S54 *m54;
} S8;

typedef struct Sub20 {
    u8 pad0[0x24C];
    u8 m24C;
} Sub20;

typedef struct Glob4C0 {
    u8 pad0[8];
    S8 *m8;
    u8 padC[4];
    s32 m10;
    u8 pad14[4];
    s32 m18;
    s32 m1C;
    Sub20 *m20;
} Glob4C0;

typedef struct Glob4C4 {
    u8 pad0[0x70];
    s32 m70;
} Glob4C4;

typedef struct Cand4440 {
    u8 pad0[0xC];
    s32 mC;
    u8 pad10[0x234 - 0x10];
    u8 c0:1;
    u8 c1:1;
    u8 c2:1;
    u8 c3:5;
    u8 pad235[0x4B4 - 0x235];
    u8 m4B4;
} Cand4440;

typedef struct T3710 {
    u8 pad0[0x10];
    s16 m10;
    u8 pad12[2];
    s16 m14;
} T3710;

typedef struct Obj4440 {
    u8 pad0[0x250];
    f32 m250;
} Obj4440;

extern "C" {
f32 RandFloat_13c010(void);
void PlayStatBumpMemberChallengeStartedMaybe_3a1940(Obj4440 *, s32);
s32 PartyCountStealthMembers_3a1d00(Obj4440 *);
T3710 *CharaSysStateRuleLookupRelated_3a3710(Obj4440 *);
s32 BattleSetupEncounter_3a3970(Obj4440 *, Desc4440 *, u8);
void CharaSysEncounterDistRoll_3a59d0(Obj4440 *, s32);
void CharaStateReset_3a79b0(Desc4440 *, s32, s32, s32, s32);
void BattleRecordReset_3a7fd0(void *);
s32 CharaCanBeLeader_3ae200(Cand4440 *, s32);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyHpPercent_3c2890(s32);
s32 PartyAverageLevel_3c2a00(s32);
Cand4440 *PartyGetSlotChara_3c2fb0(s32, s32);
s32 StateFlagTest_3ccd70(s32, s32);
s32 GroupGetRecordById_402240(s32, s16, s16);
extern Glob4C0 *D_004837C0;
extern Glob4C4 *D_004837C4;
extern f32 D_00465C98[];
extern f32 D_00465CA0[];
extern f32 D_00465CA8[];
extern f32 D_00465CB0[];
extern f32 D_00465CB8[];
extern s32 D_00465CC0[];
}

#pragma divbyzerocheck on

extern "C" s32 CharaSysEncounterSetupMaybe_3a4440(Obj4440 *arg0, Src4440 *arg1, s32 a2, s32 a3, s32 a4, u8 flag)
{
    Item4440 *list[10];
    f32 w[10];
    s32 idx[10];
    s32 cnt[10];
    Desc4440 desc;
    s32 bonus;
    s32 n18;
    s32 n17;
    s32 n16;
    T3710 *t;
    s32 i;
    s32 total;
    s32 total2;
    f32 lo;
    f32 range;

    if (arg1 == 0) {
        return 0;
    }
    if (D_004837C0 == 0 || D_004837C4 == 0) {
        return 0;
    }
    if (D_004837C0->m20->m24C & 1) {
        return 0;
    }
    lo = arg1->m11.lo;
    range = 1.0f + ((f32)arg1->m11.hi - lo);
    n18 = lo + range * RandFloat_13c010();
    if (n18 <= 0) {
        return 0;
    }
    lo = arg1->m12.lo;
    range = 1.0f + ((f32)arg1->m12.hi - lo);
    n17 = lo + range * RandFloat_13c010();
    if (n17 <= 0) {
        return 0;
    }
    if (n18 < n17) {
        n17 = n18;
    }
    bonus = 1;
    t = CharaSysStateRuleLookupRelated_3a3710(arg0);
    if (t != 0) {
        bonus = t->m10;
    }
    n16 = arg1->m16.lo;
    if (n16 > 10) {
        n16 = 10;
    }
    if (n16 <= 0) {
        return 0;
    }
    if (n16 < n17) {
        n17 = n16;
    }
    for (i = 0; i < 10; i++) {
        list[i] = 0;
    }
    if (n17 == n16) {
        for (i = 0; i < n17; i++) {
            list[i] = &arg1->items[i];
        }
    } else {
        f32 sum = 0.0f;
        f32 minw;
        s32 j;
        s32 mi;
        for (i = 0; i < n16; i++) {
            Item4440 *it = &arg1->items[i];
            f32 v = it->m4.hi;
            if (it->m5.lo > 0) {
            } else if (it->m5.hi > 0) {
            } else {
                v = 0.0f;
            }
            sum += v;
            w[i] = v;
        }
        if (sum <= 0.0f) {
            sum = 1.0f;
        }
        sum = 100.0f / sum;
        for (i = 0; i < n16; i++) {
            w[i] *= sum;
        }
        for (i = 0; i < n16; i++) {
            w[i] = w[i] * RandFloat_13c010();
        }
        minw = w[0];
        j = 0;
        idx[0] = 0;
        mi = 0;
        for (j++; j < n17; j++) {
            f32 *p;
            idx[j] = j;
            p = (f32 *)(u32)&w[j];
            if (!(minw <= *p)) {
                minw = *p;
                mi = j;
            }
        }
        for (; j < n16; j++) {
            f32 *p = (f32 *)(u32)&w[j];
            if (!(*p <= minw)) {
                s32 k;
                minw = *(volatile f32 *)p;
                idx[mi] = j;
                for (k = 0; k < n17; k++) {
                    f32 *q = (f32 *)(u32)&w[idx[k]];
                    if (!(minw <= *q)) {
                        minw = *q;
                        mi = k;
                    }
                }
            }
        }
        for (j = 0; j < n17; j++) {
            s32 a = idx[j];
            if (w[a] <= 0.0f) {
                list[j] = 0;
            } else {
                list[j] = &arg1->items[a];
            }
        }
    }
    total = 0;
    for (i = 0; i < n17; i++) {
        Item4440 *it = list[i];
        s32 c;
        if (it == 0) {
            cnt[i] = 0;
            continue;
        }
        range = 1.0f + ((f32)it->m5.hi - (f32)it->m5.lo);
        c = it->m5.lo + (s32)(range * RandFloat_13c010());
        if (c <= 0) {
            c = 1;
        }
        total += c;
        cnt[i] = c;
    }
    {
        s32 p;
        for (p = 1; p <= 2; p++) {
            s32 lim = 2;
            if (p == 2) {
                lim = 1;
            }
            if (n18 < total) {
                s32 k;
                for (k = 0; k < n17; k++) {
                    s32 *pc = &cnt[k];
                    s32 c = *pc;
                    if (c < lim) {
                        continue;
                    }
                    total--;
                    *pc = c - 1;
                    if (!(n18 < total)) {
                        break;
                    }
                }
            }
        }
    }
    if (total <= 0) {
        return 0;
    }
    desc.m0 = 0;
    total2 = 0;
    BattleRecordReset_3a7fd0(desc.m168);
    CharaStateReset_3a79b0(&desc, 1, 1, 1, 1);
    desc.m44 = 0;
    {
    s32 q;
    for (q = 0; q < n17; q++) {
        s32 c = cnt[q];
        Item4440 *it;
        s32 k;
        if (c <= 0) {
            continue;
        }
        it = list[q];
        if (it == 0) {
            continue;
        }
        if (it->u == 0) {
            continue;
        }
        for (k = 0; k < c; k++) {
            Ent4440 *e = &desc.ent[desc.m44];
            e->a = it->m4.lo;
            e->b = it->u->m0;
            desc.m44++;
            total2 += it->u->m2C + bonus - 1;
        }
    }
    }
    desc.mA = a4;
    desc.m8 = a3;
    desc.mC = a2;
    desc.m10 = GroupGetRecordById_402240(D_004837C4->m70, a3, a2);
    desc.m14 = arg1;
    desc.m18 = 0;
    desc.m162 = arg1->mA;
    desc.m164 = arg1->m10.lo;
    desc.m166 = arg1->m10.hi;
    desc.m28 = -1;
    desc.b0 = false;
    desc.m2C = 0;
    desc.m2E = 0;
    desc.m30 = 0;
    desc.m16C = 0;
    desc.m40 = 0;
    desc.b1 = false;
    desc.b2 = false;
    desc.b3 = false;
    desc.b4 = false;
    if (t != 0) {
        desc.m40 = t->m14;
    }
    {
        s32 lst = D_004837C0->m18;
        s32 sum2 = PartyCountMembers_3c2010(lst, 1, 1);
        s32 all = sum2 + PartyCountReserve_3c1c20(lst, 1, 1);
        s32 lvlp = PartyAverageLevel_3c2a00(D_004837C0->m18);
        s32 kind = PartyHpPercent_3c2890(D_004837C0->m18);
        s32 v = PartyCountStealthMembers_3a1d00(arg0);
        s32 b;
        u8 bb;
        f32 chance;
        b = 1;
        if (arg0->m250 <= 0.0f) {
            b = 0;
        }
        bb = b;
        if (v > 0 || bb) {
            s32 diff = lvlp - total2 / desc.m44;
            s32 lvl = 0;
            if (v > 0) {
                Base4440 *base;
                f32 adj;
                if (bb) {
                    base = D_004837C0->m8->m54->m8;
                    lvl = base->mCF;
                } else {
                    base = D_004837C0->m8->m54->m8;
                    lvl = base->mCE;
                }
                adj = 0.0f;
                if (v >= 2) {
                    adj = (s32)((f32)(v - 1) * ((f32)base->mD0 / 10.0f));
                }
                lvl -= adj;
            } else if (bb) {
                lvl = D_004837C0->m8->m54->m8->mCD;
            }
            if (!(diff < lvl)) {
                Base4440 *base = D_004837C0->m8->m54->m8;
                f32 f = (f32)base->mC6 / 10.0f;
                if (diff > 0) {
                    f32 k = (f32)base->mC8 / 10.0f;
                    k = (f32)diff * (f32)k;
                    f += k;
                }
                if (!(f <= 100.0f * RandFloat_13c010())) {
                    CharaSysEncounterDistRoll_3a59d0(arg0, 1);
                    return 0;
                }
            }
        }
        chance = D_00465CA8[0];
        switch (arg1->m14.lo) {
        case 0:
            chance = D_00465C98[0];
            break;
        case 1:
            chance = D_00465CA0[0];
            break;
        case 2:
            chance = D_00465CA8[0];
            break;
        case 3:
            chance = D_00465CB0[0];
            break;
        case 4:
            chance = D_00465CB8[0];
            break;
        case 5:
            if (kind <= D_00465CC0[0]) {
                chance = D_00465CB8[0];
            } else {
                chance = D_00465CA0[0];
            }
            break;
        }
        if (arg1->m15 < lvlp) {
            chance = 0.0f;
        }
        if (StateFlagTest_3ccd70(D_004837C0->m10, 0x3E9) == 0) {
            chance = 0.0f;
        }
        if (100.0f * RandFloat_13c010() < chance) {
            switch (arg1->m14.hi) {
            case 0:
                desc.m2C = 0;
                break;
            case 1:
                desc.m2C = 1;
                break;
            case 2:
                desc.m2C = 2;
                break;
            case 3:
                desc.m2C = 3;
                break;
            case 4:
                desc.m2C = 4;
                break;
            case 5:
                desc.m2C = (s32)(4.0f * RandFloat_13c010()) + 1;
                break;
            }
            if (desc.m2C == 1) {
                Cand4440 *c;
                do {
                    c = PartyGetSlotChara_3c2fb0(D_004837C0->m18, (s32)((f32)all * RandFloat_13c010()));
                } while (!(bool)c || c->c2 || (c->m4B4 & 1) || CharaCanBeLeader_3ae200(c, 0) == 0);
                desc.m2E = c->mC;
                PlayStatBumpMemberChallengeStartedMaybe_3a1940(arg0, c->mC);
            }
        }
    }
    return BattleSetupEncounter_3a3970(arg0, &desc, flag);
}
