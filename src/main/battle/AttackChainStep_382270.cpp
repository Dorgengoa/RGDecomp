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
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void v112();
    virtual void v113();
    virtual void v114();
    virtual void v115();
    virtual void v116();
    virtual void v117();
    virtual void v118();
    virtual void v119();
    virtual void v120();
    virtual void v121();
    virtual void v122();
    virtual void v123();
    virtual void v124();
    virtual void v125();
    virtual void v126();
    virtual void v127();
    virtual void v128();
    virtual void v129();
    virtual void v130();
    virtual void v131();
    virtual void v132();
    virtual void v133();
    virtual void v134();
    virtual void v135();
    virtual void v136();
    virtual void v137();
    virtual void v138();
    virtual void v139();
    virtual void v140();
    virtual void v141();
    virtual void v142();
    virtual void v143();
    virtual void v144();
    virtual void v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual void v151();
    virtual void v152();
    virtual void v153();
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void f158(Obj100 *);
};
class VB {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void v112();
    virtual void v113();
    virtual void v114();
    virtual void v115();
    virtual void v116();
    virtual void v117();
    virtual void v118();
    virtual void v119();
    virtual void v120();
    virtual void v121();
    virtual void v122();
    virtual void v123();
    virtual void v124();
    virtual void v125();
    virtual void v126();
    virtual void v127();
    virtual void v128();
    virtual void v129();
    virtual void v130();
    virtual void v131();
    virtual void v132();
    virtual void v133();
    virtual void v134();
    virtual void v135();
    virtual void v136();
    virtual void v137();
    virtual void v138();
    virtual void v139();
    virtual void v140();
    virtual void v141();
    virtual void v142();
    virtual void v143();
    virtual void v144();
    virtual void v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual void v151();
    virtual void v152();
    virtual void v153();
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void f158x(Obj100 *);
    virtual void f159(Obj70 *);
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
    if (AttackChainGetPhase_382eb0(self) == 0) return;
    prev = self->f18;
    h = GetCurrentScene_1f5be0();
    self->f18 = self->f18 + GameSceneGetTimeStep_1ceba0(h);
    if (AttackChainGetPhase_382eb0(self) == 4) {
        self->h8 = 5;
        return;
    }
    if (AttackChainGetPhase_382eb0(self) == 6) {
        if (*(f32 *)((u8 *)self->list + self->hA * 0x224 + 4) <= self->f18) {
            self->h8 = 0xB;
        }
        return;
    }
    if (AttackChainGetPhase_382eb0(self) > 6 && AttackChainGetPhase_382eb0(self) <= 0xB) return;
    if (AttackChainGetPhase_382eb0(self) == 1 || AttackChainGetPhase_382eb0(self) == 2) {
        self->f1C = self->f18;
    }
    if (AttackChainGetPhase_382eb0(self) == 2) {
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
        vb = ActorFindById_3eb870(g, GameFlowGetChainTargetId_285f40());
        r = 0;
        if (vb != 0) {
            ExecInfoInit_3a7940(&o100);
            ExecInfoInitFromChara_3a7830(&o100, GameFlowGetChainCharaId_285f50(), 0, 0, D_00463E10);
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
    if (AttackChainGetPhase_382eb0(self) == 4) {
        func_4F6B30(D_00527020);
        GameSceneSoundSlot5PlaySe_1d05a0(h, 0x4F);
    }
}
