/* rgp:protos */
#line 1
#include "types.h"

#define V1(n) virtual void v##n();
#define V4(n) V1(n##0) V1(n##1) V1(n##2) V1(n##3)
#define V16(n) V4(n##0) V4(n##1) V4(n##2) V4(n##3)

class Unit {
public:
    VC_VPTR_MEMBER; void f0() { VCM0(void, 0x8); } void f1() { VCM0(void, 0xC); } void f2() { VCM0(void, 0x10); } void f3() { VCM0(void, 0x14); } void f4() { VCM0(void, 0x18); } void f5() { VCM0(void, 0x1C); }
    void f6() { VCM0(void, 0x20); } void f7() { VCM0(void, 0x24); }    
      
    s32 IsFoe() { return VCM0(s32, 0x44); } /* 0x44 */
    s32 IsPc() { return VCM0(s32, 0x48); } /* 0x48 */
    s32 IsBack() { return VCM0(s32, 0x4C); } /* 0x4C */
         
         
      void f32() { VCM0(void, 0x88); }   
         
       
    s32 IsAlive() { return VCM0(s32, 0xC0); } /* 0xC0 */
         
         
         
         
         
         
         
         
         
         
         
         
         
         
        
    s32 Guard() { return VCM0(s32, 0x228); } /* 0x228 */
         
         
         
         
         
         
         
         
         
         
         
         
         
         
     
    s32 Aff(s32 a0) { return VCM(s32, (void *, s32), 0x384, a0); } /* 0x384 */
         
         
         
         
         
         
      
    s32 Busy() { return VCM0(s32, 0x424); } /* 0x424 */
         
         
         
         
         
      
    void Hurt() { VCM0(void, 0x4AC); } /* 0x4AC */
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
Unit * ActorCastToChara_3b87b0(Unit *, int, int, int);
Unit * ActorCastToUnit_3b8770(Unit *, int, int, int);
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
    Ev ev1 __attribute__((aligned(16)));
    Ev ev2 __attribute__((aligned(16)));
    Ev ev3 __attribute__((aligned(16)));
    Ev ev4 __attribute__((aligned(16)));
    Ev ev5 __attribute__((aligned(16)));
    Ev ev6 __attribute__((aligned(16)));
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
                u = ActorCastToChara_3b87b0(att, 0, 0, 0);
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
        u = ActorCastToChara_3b87b0(self, 0, 0, 0);
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
            u = ActorCastToUnit_3b8770(self, 0, 0, 0);
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
