#include "types.h"

#define V1(n) virtual void v##n();
#define V4(n) V1(n##0) V1(n##1) V1(n##2) V1(n##3)
#define V16(n) V4(n##0) V4(n##1) V4(n##2) V4(n##3)

class Unit {
public:
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
    virtual void f6(); virtual void f7(); virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
    virtual void f12(); virtual void f13(); virtual void f14();
    virtual s32 IsFoe(void); /* 0x44 */
    virtual s32 IsPc(void); /* 0x48 */
    virtual s32 IsBack(void); /* 0x4C */
    virtual void f18(); virtual void f19(); virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
    virtual void f24(); virtual void f25(); virtual void f26(); virtual void f27(); virtual void f28(); virtual void f29();
    virtual void f30(); virtual void f31(); virtual void f32(); virtual void f33(); virtual void f34(); virtual void f35();
    virtual void f36(); virtual void f37(); virtual void f38(); virtual void f39(); virtual void f40(); virtual void f41();
    virtual void f42(); virtual void f43(); virtual void f44(); virtual void f45();
    virtual s32 IsAlive(void); /* 0xC0 */
    virtual void f47(); virtual void f48(); virtual void f49(); virtual void f50(); virtual void f51(); virtual void f52();
    virtual void f53(); virtual void f54(); virtual void f55(); virtual void f56(); virtual void f57(); virtual void f58();
    virtual void f59(); virtual void f60(); virtual void f61(); virtual void f62(); virtual void f63(); virtual void f64();
    virtual void f65(); virtual void f66(); virtual void f67(); virtual void f68(); virtual void f69(); virtual void f70();
    virtual void f71(); virtual void f72(); virtual void f73(); virtual void f74(); virtual void f75(); virtual void f76();
    virtual void f77(); virtual void f78(); virtual void f79(); virtual void f80(); virtual void f81(); virtual void f82();
    virtual void f83(); virtual void f84(); virtual void f85(); virtual void f86(); virtual void f87(); virtual void f88();
    virtual void f89(); virtual void f90(); virtual void f91(); virtual void f92(); virtual void f93(); virtual void f94();
    virtual void f95(); virtual void f96(); virtual void f97(); virtual void f98(); virtual void f99(); virtual void f100();
    virtual void f101(); virtual void f102(); virtual void f103(); virtual void f104(); virtual void f105(); virtual void f106();
    virtual void f107(); virtual void f108(); virtual void f109(); virtual void f110(); virtual void f111(); virtual void f112();
    virtual void f113(); virtual void f114(); virtual void f115(); virtual void f116(); virtual void f117(); virtual void f118();
    virtual void f119(); virtual void f120(); virtual void f121(); virtual void f122(); virtual void f123(); virtual void f124();
    virtual void f125(); virtual void f126(); virtual void f127(); virtual void f128(); virtual void f129(); virtual void f130();
    virtual void f131(); virtual void f132(); virtual void f133(); virtual void f134(); virtual void f135();
    virtual s32 Guard(void); /* 0x228 */
    virtual void f137(); virtual void f138(); virtual void f139(); virtual void f140(); virtual void f141(); virtual void f142();
    virtual void f143(); virtual void f144(); virtual void f145(); virtual void f146(); virtual void f147(); virtual void f148();
    virtual void f149(); virtual void f150(); virtual void f151(); virtual void f152(); virtual void f153(); virtual void f154();
    virtual void f155(); virtual void f156(); virtual void f157(); virtual void f158(); virtual void f159(); virtual void f160();
    virtual void f161(); virtual void f162(); virtual void f163(); virtual void f164(); virtual void f165(); virtual void f166();
    virtual void f167(); virtual void f168(); virtual void f169(); virtual void f170(); virtual void f171(); virtual void f172();
    virtual void f173(); virtual void f174(); virtual void f175(); virtual void f176(); virtual void f177(); virtual void f178();
    virtual void f179(); virtual void f180(); virtual void f181(); virtual void f182(); virtual void f183(); virtual void f184();
    virtual void f185(); virtual void f186(); virtual void f187(); virtual void f188(); virtual void f189(); virtual void f190();
    virtual void f191(); virtual void f192(); virtual void f193(); virtual void f194(); virtual void f195(); virtual void f196();
    virtual void f197(); virtual void f198(); virtual void f199(); virtual void f200(); virtual void f201(); virtual void f202();
    virtual void f203(); virtual void f204(); virtual void f205(); virtual void f206(); virtual void f207(); virtual void f208();
    virtual void f209(); virtual void f210(); virtual void f211(); virtual void f212(); virtual void f213(); virtual void f214();
    virtual void f215(); virtual void f216(); virtual void f217(); virtual void f218(); virtual void f219(); virtual void f220();
    virtual void f221(); virtual void f222();
    virtual s32 Aff(s32); /* 0x384 */
    virtual void f224(); virtual void f225(); virtual void f226(); virtual void f227(); virtual void f228(); virtual void f229();
    virtual void f230(); virtual void f231(); virtual void f232(); virtual void f233(); virtual void f234(); virtual void f235();
    virtual void f236(); virtual void f237(); virtual void f238(); virtual void f239(); virtual void f240(); virtual void f241();
    virtual void f242(); virtual void f243(); virtual void f244(); virtual void f245(); virtual void f246(); virtual void f247();
    virtual void f248(); virtual void f249(); virtual void f250(); virtual void f251(); virtual void f252(); virtual void f253();
    virtual void f254(); virtual void f255(); virtual void f256(); virtual void f257(); virtual void f258(); virtual void f259();
    virtual void f260(); virtual void f261(); virtual void f262();
    virtual s32 Busy(void); /* 0x424 */
    virtual void f264(); virtual void f265(); virtual void f266(); virtual void f267(); virtual void f268(); virtual void f269();
    virtual void f270(); virtual void f271(); virtual void f272(); virtual void f273(); virtual void f274(); virtual void f275();
    virtual void f276(); virtual void f277(); virtual void f278(); virtual void f279(); virtual void f280(); virtual void f281();
    virtual void f282(); virtual void f283(); virtual void f284(); virtual void f285(); virtual void f286(); virtual void f287();
    virtual void f288(); virtual void f289(); virtual void f290(); virtual void f291(); virtual void f292(); virtual void f293();
    virtual void f294(); virtual void f295(); virtual void f296();
    virtual void Hurt(void); /* 0x4AC */
    u8 pad4[0xC - 0x4];
    s32 xC;
    u8 pad10[0x1D4 - 0x10];
    s16 x1D4;
    s16 x1D6;
};

typedef struct Src {
    u8 pad0[0x4];
    s16 x4;
    u8 pad6[2];
    s16 x8;
    s16 xA;
    u8 padC[0x1C - 0xC];
    s16 x1C;
} Src;

typedef struct Slot8 {
    s8 x0;
    u8 pad1[7];
} Slot8;

typedef struct Hit {
    Src *x0;
    u8 pad4[0x1A - 0x4];
    s16 x1A;
    Slot8 x1C[4];
    u8 pad3C[0x41 - 0x3C];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 1;
    u8 f4 : 1;
    u8 f5 : 1;
    u8 f6 : 1;
    u8 f7 : 1;
    u8 pad42[0x80 - 0x42];
    u8 g0 : 1;
    u8 g1 : 1;
    u8 g2 : 1;
    u8 g3 : 1;
    u8 g4 : 1;
    u8 g5 : 1;
    u8 g6 : 1;
    u8 g7 : 1;
} Hit;

typedef struct Tally {
    s32 n;
    s32 sum;
    s16 avg;
    s16 max;
    s32 c3;
    s32 c5;
} Tally;

typedef struct Stats {
    u8 pad0[0xA];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 1;
    u8 f4 : 1;
    u8 f5 : 1;
    u8 f6 : 1;
    u8 f7 : 1;
    u8 padB[0x2C - 0xB];
    Tally t2C;
    Tally t40;
} Stats;

typedef struct Party {
    u8 pad0[0x168];
    Stats st;
    u8 pad1BC[0x1C2 - 0x1BC];
    s16 x1C2;
    s16 x1C4;
} Party;

typedef struct Btl {
    u8 pad0[0x238];
    Party *x238;
} Btl;

typedef struct Mode {
    u8 pad0[0x24];
    s16 x24;
} Mode;

typedef struct Glob {
    u8 pad0[0xC];
    Mode *xC;
    u8 pad10[0x20 - 0x10];
    Btl *x20;
} Glob;

typedef struct Ev {
    u8 pad0[0x30];
} Ev;

extern "C" {
Unit *ActorFindById_3eb870(Glob *, s32);
Unit *ActorCastToChara_3b87b0(Unit *);
Unit *ActorCastToUnit_3b8770(Unit *);
s32 CharaIsPartyLeader_3ae1a0(Unit *);
void PlayStatBumpFoeHitMaybe_3a1b20(Btl *, s32);
void BattleRecordDefeat_3a3410(Btl *, s32, s32, s32, s32);
s32 GetCurrentScene_1f5be0(void);
void ActionPacketReset_3e3d00(Ev *);
void ActionPacketInitBattleDefeat_3e33e0(Ev *, s32, Unit *, Unit *, Hit *, bool);
void ActionPacketInitBattleGuard_3e3290(Ev *, s32, Unit *, Unit *, Hit *);
void ActionPacketInitBattleDamage_3e3140(Ev *, s32, Unit *, Unit *, Hit *);
void ActionPacketInitBattleNoDamage_3e30b0(Ev *, s32, Unit *, Unit *, Hit *);
void ActionPacketInitBattleRevive_3e3110(Ev *, s32, Unit *, Unit *, Hit *);
void ActionPacketInitBattleHeal_3e30e0(Ev *, s32, Unit *, Unit *, Hit *);
s32 EventFireTriggers_3e2660(Ev *, s32);
void SkillTriggerEvalMaybe_3e1200(Ev *, Unit *);
extern Glob *D_00483818;
s32 BattleUnitOnHit_3b2210(Unit *self, Hit *hit, s32 dmg, s32 a3, u8 f1, u8 f2);
}

extern "C" s32 BattleUnitOnHit_3b2210(Unit *self, Hit *hit, s32 dmg, s32 a3, u8 f1, u8 f2)
{
    Ev ev1;
    Ev ev2;
    Ev ev3;
    Ev ev4;
    Ev ev5;
    Ev ev6;
    Src *src;
    Unit *att;
    s32 team;
    bool isChar;
    u8 back;
    s32 aff;
    Unit *u;
    Stats *st;
    Tally *t;
    s32 total;
    s32 ctx;
    s32 k;
    bool first;
    s32 n;
    s32 i;

    if (hit == 0) {
        return 0;
    }
    src = hit->x0;
    att = 0;
    team = -1;
    isChar = false;
    back = 0;
    aff = 0;
    if (src != 0) {
        if (src->x4 == 1) {
            att = ActorFindById_3eb870(D_00483818, src->x8);
            isChar = true;
            if (att != 0) {
                team = att->xC;
                u = ActorCastToChara_3b87b0(att);
                if (u != 0) {
                    back = CharaIsPartyLeader_3ae1a0(u);
                    aff = u->Aff(src->xA);
                }
            }
        } else if (src->x4 == 2) {
            att = ActorFindById_3eb870(D_00483818, src->x8);
        }
    }
    if (D_00483818->x20->x238 != 0) {
        st = &D_00483818->x20->x238->st;
    } else {
        st = 0;
    }
    if (dmg > 0) {
        u = ActorCastToChara_3b87b0(self);
        if (u != 0) {
            u->Hurt();
        }
        if (D_00483818->x20->x238 != 0 && u != 0 && CharaIsPartyLeader_3ae1a0(u) != 0) {
            st->f1 = 1;
        }
        if (self->IsAlive()) {
            hit->f5 = 1;
            self->x1D6++;
            for (i = 0; i < hit->x1A; i++) {
                if (hit->x1C[i].x0 == 5) {
                    hit->x1C[i].x0 = 0;
                }
            }
            if (self->IsFoe()) {
                PlayStatBumpFoeHitMaybe_3a1b20(D_00483818->x20, self->xC);
            }
        } else if (self->Guard()) {
            hit->f3 = 1;
            if (!f2) {
                hit->f4 = true;
                self->x1D4++;
            }
        }
        if (st != 0) {
            t = &st->t2C;
            if (self->IsBack()) {
                t = &st->t40;
            }
            t->n++;
            t->sum += dmg;
            t->avg = (s32)((f32)t->sum / (f32)t->n);
            if (t->max < dmg) {
                t->max = dmg;
            }
            if (hit->f3) {
                t->c3++;
            }
            if (hit->f5) {
                t->c5++;
            }
        }
        total = 0;
        if (self->IsAlive()) {
            if (isChar) {
                if (self->IsPc()) {
                    Party *p = D_00483818->x20->x238;
                    if (p != 0 && D_00483818->xC->x24 != 3 && src->x1C == 1) {
                        if (back) {
                            p->x1C2++;
                        } else {
                            p->x1C4++;
                        }
                    }
                }
            }
            BattleRecordDefeat_3a3410(D_00483818->x20, self->xC, team, aff, 0);
            u = ActorCastToUnit_3b8770(self);
            if (u != 0 && u->Busy() == 0) {
                Party *p = D_00483818->x20->x238;
                if (p != 0) {
                    p->st.f5 = 1;
                }
            }
            ctx = GetCurrentScene_1f5be0();
            for (k = 1; k <= 2; k++) {
                first = true;
                if (k == 2) {
                    first = false;
                }
                ActionPacketReset_3e3d00(&ev1);
                ActionPacketInitBattleDefeat_3e33e0(&ev1, ctx, att, self, hit, first);
                n = EventFireTriggers_3e2660(&ev1, 0);
                total += n;
                if (n > 0) {
                    if (first) {
                        hit->g2 = 1;
                    } else {
                        hit->g3 = 1;
                    }
                }
                SkillTriggerEvalMaybe_3e1200(&ev1, self);
                SkillTriggerEvalMaybe_3e1200(&ev1, att);
            }
        }
        if (total <= 0) {
            ctx = GetCurrentScene_1f5be0();
            n = 0;
            if (hit->f4) {
                ActionPacketReset_3e3d00(&ev2);
                ActionPacketInitBattleGuard_3e3290(&ev2, ctx, att, self, hit);
                n = EventFireTriggers_3e2660(&ev2, 0);
                SkillTriggerEvalMaybe_3e1200(&ev2, self);
            }
            if (n <= 0) {
                ActionPacketReset_3e3d00(&ev3);
                ActionPacketInitBattleDamage_3e3140(&ev3, ctx, att, self, hit);
                EventFireTriggers_3e2660(&ev3, 0);
                SkillTriggerEvalMaybe_3e1200(&ev3, self);
            }
        }
    } else if (hit->f2) {
        ctx = GetCurrentScene_1f5be0();
        ActionPacketReset_3e3d00(&ev4);
        ActionPacketInitBattleNoDamage_3e30b0(&ev4, ctx, att, self, hit);
        EventFireTriggers_3e2660(&ev4, 0);
    }
    if (f1) {
        ctx = GetCurrentScene_1f5be0();
        ActionPacketReset_3e3d00(&ev5);
        ActionPacketInitBattleRevive_3e3110(&ev5, ctx, att, self, hit);
        EventFireTriggers_3e2660(&ev5, 0);
        SkillTriggerEvalMaybe_3e1200(&ev5, self);
    } else if (a3 > 0) {
        ctx = GetCurrentScene_1f5be0();
        ActionPacketReset_3e3d00(&ev6);
        ActionPacketInitBattleHeal_3e30e0(&ev6, ctx, att, self, hit);
        EventFireTriggers_3e2660(&ev6, 0);
        SkillTriggerEvalMaybe_3e1200(&ev6, self);
    }
    return 1;
}
