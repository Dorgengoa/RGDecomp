/* rgp:protos */
#line 1
#include "types.h"

class Actor {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 isActive() { return VCM0(s32, 0xBC); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void setState(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x2B0, a0, a1, a2); }
};

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void reset(f32 a0) { VCM(void, (void *, f32), 0x26C, a0); }
};

struct Mgr10 { u8 pad0[0x10]; s32 unk10; };
struct World {
    u8 pad0[0x18];
    s32 unk18;
    Mgr10 *unk1C;
    s32 unk20;
};

struct Obj {
    u8 pad0[0x30];
    f32 unk30;
    u8 pad34[0xC];
    f32 unk40;
    u8 pad44[0x128];
    s32 unk16C;
    u8 pad170[0x2];
    u8 flag : 1;
    u8 pad173[0x5];
    f64 unk178;
};

struct Timer {
    u8 pad0[0x4];
    f32 unk4;
};

struct Self {
    u8 pad0[0x238];
    Obj *unk238;
    u8 pad23C[0x8];
    s32 unk244;
    u8 pad248[0x4];
    u8 unk24C;
    u8 pad24D[0x3];
    f32 unk250;
    u8 pad254[0x940];
    u8 *unkB94;
};

extern "C" {
s32 DoubleGreaterEqual_100230(f64, f64);
s32 DoubleLessEqual_100280(f64, f64);
f64 dpdiv(f64, f64);
u32 DoubleToUInt_13bb78(f64);
s32 GetGameMode_1f59c0(void);
void MesShowMsgByIndex_278fd0(s32, s32);
s32 IsInBattle_288420(void);
Actor *PoolGetUsedElem_36acb0(s32, s32);
void StatusEntryTryExpire_3a15c0(Self *, Timer *);
void BattleCheckEnd_3a1e40(Self *, s32);
s32 CharaSysStateGetChallengeKindMaybe_3a3800(Self *);
s32 CharaSysStateFlag24Bit2Related_3a3880(Self *);
s32 CharaSysHasEncounterRecMaybe_3a3950(s32);
s32 StatusEntryIsRunning_3a6190(Timer *);
void CharaEventLogTimersTick_3a6220(s32, f32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
Unit *PartyGetMemberChara_3c2420(s32, s32);
f64 dpadd(f64, f64);
f32 dptofp(f64);
f64 fptodp(f32);
extern f32 D_0045B078[];
extern s32 D_004659C8[];
extern World *D_004837C0;
}

extern "C" s32 CharaSysUpdate_3a0c10(Self *self, f32 dt) {
    Obj *obj;
    f64 d;
    f64 t;
    s32 cnt;
    s32 i;
    Actor *e;
    Timer *p;
    s32 k;
    Unit *u;
    s32 r;
    f32 w;
    u32 n;
    f32 fa;
    f32 fb;
    s32 v;

    if (D_004837C0 == 0) {
        return 0;
    }
    if (self->unk24C & 1) {
        BattleCheckEnd_3a1e40(self, 1);
        if (((unsigned char)IsInBattle_288420()) != 0) {
            obj = self->unk238;
            if (obj != 0) {
                d = fptodp(2.0f * dt);
                obj->unk178 = dpadd(obj->unk178, d);
                if (CharaSysHasEncounterRecMaybe_3a3950(D_004837C0->unk20) == 0) {
                    obj = self->unk238;
                    t = obj->unk178;
                    f32 lim = dptofp(dpdiv(dpdiv(t, fptodp(D_0045B078[0])), 2.0));
                    if (!(obj->unk40 <= 0.0f) && obj->unk40 <= lim) {
                        cnt = D_004659C8[0];
                        for (i = 0; i < cnt; i++) {
                            s32 m = D_004837C0->unk1C->unk10;
                            if (m != 0) {
                                e = PoolGetUsedElem_36acb0(m, i);
                            } else {
                                e = 0;
                            }
                            if (e == 0) continue;
                            if (e->isActive() != 0) {
                                e->setState(0, 1, 0);
                            }
                        }
                    }
                }
                p = (Timer *)(self->unkB94 + 4);
                for (k = 0; k < 32; k++, p = (Timer *)((u8 *)p + 8)) {
                    if (StatusEntryIsRunning_3a6190(p) == 0) continue;
                    {
                        f32 y = p->unk4;
                        f32 x = y - dptofp(d);
                        p->unk4 = x;
                        if (x <= 0.0f) {
                            StatusEntryTryExpire_3a15c0(self, p);
                        }
                    }
                }
            }
        }
        if (self->unk238 != 0 && CharaSysStateFlag24Bit2Related_3a3880(self) != 0) {
            t = self->unk238->unk178;
            if (((unsigned char)DoubleGreaterEqual_100230(t, 20.0)) != 0 && ((unsigned char)DoubleLessEqual_100280(t, 25.0)) != 0) {
                cnt = PartyCountMembers_3c2010(D_004837C0->unk18, 1, 1);
                for (i = 0; i < cnt; i++) {
                    u = PartyGetMemberChara_3c2420(D_004837C0->unk18, i);
                    if (u != 0) {
                        u->reset(0.0f);
                    }
                }
            }
        }
    }
    if (self->unk24C & 1) {
        if (self->unk244 != 0) {
            CharaEventLogTimersTick_3a6220(self->unk244, dt);
        }
    }
    if ((self->unk24C & 1) && ((r = CharaSysStateGetChallengeKindMaybe_3a3800(self)) == 1 || r == 2 || r == 4)) {
        obj = self->unk238;
        w = 0.0f;
        if (obj != 0) {
            w = obj->unk30;
        }
        n = (obj != 0) ? DoubleToUInt_13bb78(obj->unk178) : 0;
        fa = (f32)n - 120.0f;
        fb = 60.0f + (120.0f + w);
        if (fa <= fb) {
            v = (s32)(fb - fa);
            if (v < 0) {
                v = 0;
            }
            if (!((f32)v <= w)) {
                v = (s32)w;
            }
            if (obj != 0) {
                obj->unk16C = v;
                self->unk238->flag = true;
            }
        } else {
            if (obj != 0) {
                obj->unk16C = 0;
                self->unk238->flag = false;
            }
        }
    }
    r = GetGameMode_1f59c0();
    if (!(self->unk24C & 1) && r == 6) {
        f32 f = self->unk250;
        if (!(f <= 0.0f)) {
            f = f - dt;
            self->unk250 = f;
            if (f <= 0.0f) {
                self->unk250 = 0.0f;
                MesShowMsgByIndex_278fd0(4, 0xB4);
            }
        }
    }
    return 1;
}
