/* SkillTriggerEvalMaybe_3e1200 (s88m lane 3e1): rewritten from retail asm; MATCH.
   Levers: a/mc/n/slot in an inner block = homed after the function-scope homes;
   `u32 a` = 16-byte home slot; `n = (s32)(u32)n` = sw home not sq spill;
   `e = e` (multi-def) = e in s0; `k <= 4` / `pass <= 2` = slti at;
   `bool bad = !SkillCanUseMaybe_3e1970()` = sltu/xori/andi; objs[i] call-result store via
   a fresh `Obj **po` = unfolded address recompute after the call. */
#include "types.h"
#pragma opt_dead_assignments off
#pragma opt_arithtransformation off

#define VF(n) virtual void n();
#define VF10(p) VF(p##0) VF(p##1) VF(p##2) VF(p##3) VF(p##4) VF(p##5) VF(p##6) VF(p##7) VF(p##8) VF(p##9)
#define VF100(p) VF10(p##0) VF10(p##1) VF10(p##2) VF10(p##3) VF10(p##4) VF10(p##5) VF10(p##6) VF10(p##7) VF10(p##8) VF10(p##9)

struct Part { u8 pad0[2]; s16 h2; s32 w4; };

struct Ent {
    u8 pad0[4];
    s32 m4;
    s16 m8;
    u8 padA[4];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
    u8 f0 : 1;
    u8 f1 : 1;
    u8 frest : 6;
    Part *p10;
    Part *p14;
    Part *p18;
    Part *p1C;
    u8 pad20[8];
    s16 m28;
};

class Obj {
public:
    VF10(a) VF10(b) VF(c0)
    virtual s32 v5C();
};

class Unit {
public:
    VF10(a) VF(b0) VF(b1) VF(b2) VF(b3) VF(b4) VF(b5)
    virtual u8 v48();
    VF(c0) VF(c1) VF(c2) VF(c3)
    virtual s32 v5C();
    VF10(d) VF10(e) VF(f0) VF(f1) VF(f2) VF(f3)
    virtual s32 vC0();
    u8 pad4[8];
    s32 mC;
};

class Team {
public:
    VF10(a) VF(b0) VF(b1) VF(b2) VF(b3) VF(b4) VF(b5) VF(b6) VF(b7) VF(b8) VF(b9) VF(c0)
    virtual s32 v5C();
    VF100(d) VF100(e) VF10(f0) VF10(f1) VF10(f2) VF10(f3) VF10(f4) VF(g0) VF(g1) VF(g2) VF(g3) VF(g4) VF(g5)
    virtual s32 v460();
};

struct Msg {
    s16 m0;
    u8 m2;
    u8 m3;
    u8 m4;
    u8 pad5[0xB];
    Obj *m10;
    Obj *m14;
};

struct Slot { s16 unk0; u8 pad2[0xD]; u8 unkF; u8 pad10[0x2C]; s16 unk3C; u8 pad3E[0xA]; };
struct Stat { s8 cnt; u8 found : 1; u8 all : 1; };

struct Elem { u8 d[0x38]; };
struct Big {
    u8 hdr[8];
    Elem e[64];
    u8 pad[4];
    u8 flag : 1;
    u8 rest : 7;
};

struct Res { u8 d[12]; };
struct It { u8 d[8]; };

struct G18 { u8 pad0[0x42D0]; u8 m42D0; };
struct G20 { u8 pad0[0x24C]; u8 m24C; };
struct GC { u8 pad0[0x20]; s16 m20; };
struct Glob { u8 pad0[0xC]; GC *mC; u8 pad10[8]; G18 *m18; u8 pad1C[4]; G20 *m20; };

extern "C" {

f32 RandFloat_13c010(void);
s32 GetGameMode_1f59c0(void);
s32 VariantIsZero_36ed10(s32);
void VariantInit_36ff00(Elem *);
Ent *IterNext_370040(It *);
void IterInit_370170(It *, Res *);
void ActorCastToUnit_3b8770(Unit *);
Team *ActorCastToChara_3b87b0(Unit *);
s32 PartyCountExcludingLeader_3c2610(G18 *, s32, s32);
Obj *PartyGetNonLeaderChara_3c2700(G18 *, s32);
Obj *PartyGetLeaderChara_3c2820(G18 *);
s32 PartyGetLocationGroupIdMaybe_3cb150(G18 *);
s32 ScriptExecOpStream_3dffa0(Big *, s16, s32, Msg *);
void VariantPoolReset_3e01f0(Big *);
s32 SkillActionFindFreeSlot_3e10b0(void);
u8 SkillCanUseMaybe_3e1970(s32, Ent *);
bool SkillActionQueryByCharaMaybe_3e1a00(s32, Stat *);
void SkillActionInitFromDef_3e3d50(Slot *, s32, Ent *);
void RowRangeIterCtor_40f4e0(Res *, Glob *, s32, s32, u8, s32, u8 *);

extern Glob *D_00483990;
extern u8 D_004839A0;
extern u8 D_004839A4;
extern u8 D_004839A8;
extern Slot D_004E9770[];

static inline void SetP(Obj **p, Obj *v) { *p = v; }
static inline void SetI(s32 *p, s32 v) { *p = v; }
static inline Obj *GetP(Obj **p, s32 i) { return p[i]; }
bool SkillTriggerEvalMaybe_3e1200(Msg *msg, Unit *u)
{
    bool ok;
    s32 t;
    u8 b;
    s32 cur;
    s32 id1;
    s32 id2;
    Slot *bestp;
    bool fail;
    s32 pass;
    Elem *el;
    s32 id;
    Team *tm;
    s32 c0;
    Stat st;
    s32 b0;
    s32 a0;
    s32 idx;
    Obj *o;
    s32 i;
    Obj *objs[2];
    s32 ids[2];
    Ent *best;
    Res res;
    It it;
    Ent *e;
    bool r;

    if (u == NULL) {
        return 0;
    }
    if (D_00483990 == NULL) {
        return 0;
    }
    if (D_004839A0 == 0) {
        return 1;
    }
    if (D_004839A4 != 0) {
        return 1;
    }
    if (D_004839A8 != 0) {
        return 1;
    }
    if (D_00483990->mC->m20 == 0) {
        return 1;
    }
    ok = 1;
    t = GetGameMode_1f59c0();
    if ((u32)(t - 0x11) < 2) {
        if (msg->m2 != 6 || msg->m3 != 0x22 || msg->m4 != 0x33) {
            ok = 0;
        }
    } else if (t != 7 && t != 6) {
        ok = 0;
    }
    if (!ok) {
        return 0;
    }
    if (msg->m0 <= 0) {
        return 0;
    }
    if (msg->m2 == 0xFF) {
        return 0;
    }
    {
    u32 a;
    s32 mc;
    s32 n;
    Slot *slot;
    a = PartyGetLocationGroupIdMaybe_3cb150(D_00483990->m18);
    mc = u->mC;
    id = u->v5C();
    b = u->v48();
    tm = ActorCastToChara_3b87b0(u);
    ActorCastToUnit_3b8770(u);
    c0 = D_00483990->m20->m24C & 1;
    SkillActionQueryByCharaMaybe_3e1a00(mc, &st);
    b0 = st.cnt;
    a0 = (u8)st.all;
    if (st.found) {
        return 0;
    }
    idx = SkillActionFindFreeSlot_3e10b0();
    if (idx < 0) {
        return 0;
    }
    o = PartyGetLeaderChara_3c2820(D_00483990->m18);
    cur = -1;
    if (o != NULL) {
        cur = o->v5C();
    }
    n = PartyCountExcludingLeader_3c2610(D_00483990->m18, 1, 1);
    n = (s32)(u32)n;
    for (i = 0; i < 2; i++) {
        objs[i] = 0;
        ids[i] = -1;
        if (i < n) {
            Obj *oo = PartyGetNonLeaderChara_3c2700(D_00483990->m18, i);
            Obj **po = &objs[i];
            *po = oo;
            if (oo != NULL) {
                ids[i] = oo->v5C();
            }
        }
    }
    id1 = -1;
    if (msg->m2 == 6) {
        o = msg->m10;
        if (o != NULL) {
            id1 = o->v5C();
        }
    }
    id2 = -1;
    if (msg->m2 == 6) {
        o = msg->m14;
        if (o != NULL) {
            id2 = o->v5C();
        }
    }
    bestp = 0;
    slot = &D_004E9770[idx];
    best = 0;
    for (pass = 1; pass <= 2; pass++) {
        s32 q = a;
        if (pass == 2) {
            q = -1;
        }
        RowRangeIterCtor_40f4e0(&res, D_00483990, q, id, b, msg->m0, &msg->m2);
        IterInit_370170(&it, &res);
        while (e = IterNext_370040(&it), e != NULL) {
            e = e;
            if (c0 != 0) {
                if (!e->b3) continue;
            } else {
                if (!e->b2) continue;
            }
            if (e->b4 && cur != id) continue;
            if (e->b5) {
                bool found = 0;
                s32 *p = ids;
                s32 j;
                for (j = 0; j < n; j++, p++) {
                    if (*p == id) {
                        found = 1;
                        break;
                    }
                }
                if (!found) continue;
            }
            if (!e->f1 && u->vC0() != 0) continue;
            if (tm != NULL && tm->v460() != 0) {
                bool hit = 0;
                if (e->m4 == 0x8ADC2A || e->m4 == 0x8ADC34) {
                    hit = 1;
                }
                if (!hit) continue;
            }
            if (tm != NULL && (D_00483990->m18->m42D0 & 1) && tm->v5C() != 0x2AF9) continue;
            if (e->b3) {
                if (e->b6 && id1 != id) continue;
                if (e->b7 && id2 != id) continue;
            }
            if (b0 > 0) {
                if (a0 == 0) continue;
                if (!e->f0) continue;
            }
            { bool bad = !SkillCanUseMaybe_3e1970(mc, e); if (bad) continue; }
            if (best != NULL && best->m28 >= e->m28) continue;
            if ((s16)(100.0f * (100.0f * RandFloat_13c010())) > e->m8) continue;
            {
                fail = 0;
                s32 k;
                for (k = 1; k <= 4; k++) {
                    Part *x = 0;
                    switch (k) {
                    case 1: x = e->p10; break;
                    case 2: x = e->p14; break;
                    case 3: x = e->p18; break;
                    case 4: x = e->p1C; break;
                    }
                    if (x != NULL && x->h2 > 0 && x->w4 != 0) {
                        Big big;
                        s32 rr;
                        el = big.e;
                        do {
                            VariantInit_36ff00(el);
                            el++;
                        } while (el < &big.e[64]);
                        VariantPoolReset_3e01f0(&big);
                        big.flag = 1;
                        rr = ScriptExecOpStream_3dffa0(&big, x->h2, x->w4, msg);
                        if (rr == 0) {
                            fail = 1;
                            break;
                        }
                        if (VariantIsZero_36ed10(rr) != 0) {
                            fail = 1;
                            break;
                        }
                    }
                }
                if (!fail) {
                    best = e;
                    bestp = slot;
                }
            }
        }
    }
    }
    r = 0;
    if (bestp != NULL && best != NULL) {
        r = 1;
        SkillActionInitFromDef_3e3d50(bestp, u->mC, best);
    }
    return r;
}

}
