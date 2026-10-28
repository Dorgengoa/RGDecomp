/* rgp:protos */
#line 1
#include "types.h"


struct Obj100 {
    u8 p0[8];
    s16 h8;
    u8 pA[4];
    s16 hE;
    s16 h10;
    u8 p12[2];
    s32 f14;
    u8 p18[0x70 - 0x18];
};
struct Obj70 {
    Obj100 *o;
    u8 p4[0x44];
    u64 z48;
    u64 z50;
    u64 z58;
    u64 z60;
    u8 p68[0x90 - 0x68];
};
class VA {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f158(Obj100 * a0) { VCM(void, (void *, Obj100 *), 0x280, a0); }
};
class VB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f159(Obj70 * a0) { VCM(void, (void *, Obj70 *), 0x284, a0); }
};
struct Ent {
    f32 f0;
    f32 f4;
    u16 h8;
    s16 hA;
    u8 pC[0x18 - 0xC];
    f32 f18;
    f32 f1C;
    u8 p20[4];
    f32 spiral[32][4];
};
struct Self {
    Ent *list;
    s16 h4;
    u8 p6[2];
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    s32 i10;
    u8 p14[4];
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
};

extern "C" {
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
s32 PadIsTriggered_1839f0(u8 *, s32);
f32 RandRangeFloat_1ca5d0(f32);
f32 GameSceneGetTimeStep_1ceba0(s32);
void GameSceneSoundSlot5PlaySe_1d05a0(s32, s32);
s32 GetCurrentScene_1f5be0();
u8 *GetGameData_1fede0();
s32 GameFlowGetChainTargetId_285f40();
s32 GameFlowGetChainCharaId_285f50();
void AttackChainMarkersShow_382c40(Self *);
s16 AttackChainGetInputCount_382e90(Self *);
s16 AttackChainGetHitCount_382ea0(Self *);
s32 AttackChainGetPhase_382eb0(Self *);
s32 ActionResultSumDamage_3a6d20(Obj70 *);
void ActionResultClear_3a6e60(Obj70 *);
void ExecInfoInitFromChara_3a7830(Obj100 *, s32, s32, s32, u8 *);
void ExecInfoInit_3a7940(Obj100 *);
VA *CharaMgrPoolFindById_3a8c60(s32, s32);
VB *ActorFindById_3eb870(u8 *, s32);
void func_4F6A00(u8 *);
void func_4F6B30(u8 *);
void func_4F6B90(u8 *);
extern u8 D_00463E10[];
extern f32 D_0047D1FC;
extern f32 D_0047DC2C;
extern u8 D_004B2570[];
extern u8 D_00527020[];
void AttackChainStep_382270(Self *self);
}

void AttackChainStep_382270(Self *self) {
    f32 prev; f32 d; f32 dt; f32 ang; f32 r1; f32 r2; f32 *sp; s32 h; Ent *e; s32 i; s32 k; s32 r; Ent *e2; u8 *g; VB *vb; Obj100 o100; Obj70 o70;

    if (self->list == 0) return;
    if (((short)AttackChainGetPhase_382eb0(self)) == 0) return;
    prev = self->f18;
    h = GetCurrentScene_1f5be0();
    self->f18 = self->f18 + GameSceneGetTimeStep_1ceba0(h);
    if (((short)AttackChainGetPhase_382eb0(self)) == 4) {
        self->h8 = 5;
        return;
    }
    if (((short)AttackChainGetPhase_382eb0(self)) == 6) {
        if (*(f32 *)((u8 *)self->list + self->hA * 0x224 + 4) <= self->f18) {
            self->h8 = 0xB;
        }
        return;
    }
    if (((short)AttackChainGetPhase_382eb0(self)) > 6 && ((short)AttackChainGetPhase_382eb0(self)) <= 0xB) return;
    if (((short)AttackChainGetPhase_382eb0(self)) == 1 || ((short)AttackChainGetPhase_382eb0(self)) == 2) {
        self->f1C = self->f18;
    }
    if (((short)AttackChainGetPhase_382eb0(self)) == 2) {
        e = self->list;
        for (i = 0; i < self->h4; i++, e++) {
            d = e->f0 - 30.0f;
            if ((prev < d && d <= self->f1C) || (d <= 0.0f && 0.0f == prev)) {
                GameSceneSoundSlot5PlaySe_1d05a0(h, 0x44);
            }
            d = e->f0 - 45.0f;
            if ((prev < d && d <= self->f1C) || (d <= 0.0f && 0.0f == prev)) {
                GameSceneSoundSlot5PlaySe_1d05a0(h, 0x49);
            }
        }
        if (self->hA < self->h4) {
            e = &self->list[self->hA];
            dt = e->f0 - self->f1C;
            if (PadIsTriggered_1839f0(D_004B2570, 0xF0) != 0) {
                if (dt <= 30.0f) {
                    if (PadIsTriggered_1839f0(D_004B2570, e->h8) != 0 && PadIsTriggered_1839f0(D_004B2570, ~e->h8 & 0xF0) == 0 &&
                        -8.0f <= dt && dt <= 8.0f) {
                        self->hA++;
                        func_4F6A00(D_00527020);
                        if (self->hA == self->h4) {
                            GameSceneSoundSlot5PlaySe_1d05a0(h, 0x4A);
                        } else {
                            GameSceneSoundSlot5PlaySe_1d05a0(h, 0x4C);
                        }
                        sp = e->spiral[0];
                        e->f18 = self->f1C;
                        for (k = 0; k < 32; k++, sp += 4) {
                            ang = RandRangeFloat_1ca5d0(D_0047DC2C) - D_0047D1FC;
                            r1 = 8.0f + RandRangeFloat_1ca5d0(8.0f);
                            r2 = 16.0f + RandRangeFloat_1ca5d0(32.0f);
                            if (k >= 16) {
                                r1 = r1 * 2.0f;
                                r2 = r2 * 4.0f;
                            }
                            sp[0] = r1 * Cosf_128d30(ang);
                            sp[1] = r1 * Sinf_128fd0(ang);
                            sp[2] = r2 * Cosf_128d30(ang);
                            sp[3] = r2 * Sinf_128fd0(ang);
                        }
                        if (!(self->hA < self->h4)) {
                            func_4F6B90(D_00527020);
                            self->h8 = 3;
                        }
                    } else {
                        self->h8 = 4;
                        self->f20 = self->f1C;
                    }
                }
            }
            if (dt < -8.0f) {
                self->h8 = 4;
                self->f20 = self->f1C;
            }
        }
        AttackChainMarkersShow_382c40(self);
    }
    if (self->hE <= self->hA && self->hC < self->hE) {
        g = GetGameData_1fede0();
        vb = ActorFindById_3eb870(g, ((short)GameFlowGetChainTargetId_285f40()));
        r = 0;
        if (vb != 0) {
            ExecInfoInit_3a7940(&o100);
            ExecInfoInitFromChara_3a7830(&o100, ((short)GameFlowGetChainCharaId_285f50()), 0, 0, D_00463E10);
            o100.hE = AttackChainGetHitCount_382ea0(self);
            o100.h10 = AttackChainGetInputCount_382e90(self);
            *(f32 *)&o100.f14 = 1.0f;
            CharaMgrPoolFindById_3a8c60(*(s32 *)(g + 0x14), o100.h8)->f158(&o100);
            o70.z48 = 0;
            o70.z50 = 0;
            o70.z58 = 0;
            o70.z60 = 0;
            ActionResultClear_3a6e60(&o70);
            o70.o = &o100;
            vb->f159(&o70);
            r = ActionResultSumDamage_3a6d20(&o70);
        }
        e2 = &self->list[self->hC];
        e2->hA = r;
        e2->f1C = self->f18;
        self->i10 = self->i10 + r;
        self->hC++;
        if (self->hC == self->h4) {
            self->f24 = self->f18;
        }
    }
    if (((short)AttackChainGetPhase_382eb0(self)) == 4) {
        func_4F6B30(D_00527020);
        GameSceneSoundSlot5PlaySe_1d05a0(h, 0x4F);
    }
}
