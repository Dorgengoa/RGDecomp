#include "types.h"

typedef struct {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
} BF232670;

typedef struct {
    u8 d[0xB0];
    void *vptr;
    u8 rest[0x7DC];
} Obj232670;

class C232670 {
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
    virtual s32 f101(s32);
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
    virtual s32 f139();
    u8 pad[0x1C4];
    BF232670 bf;
};

extern "C" {
extern f32 GameSceneGetTimeStep_1ceba0(s32);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern void GameSceneSoundSlot0PlaySeVol_1d05f0(s32, s32, f32);
extern s32 GetGameMode_1f59c0(void);
extern s32 GetCurrentScene_1f5be0(void);
extern u8 *GetGameData_1fede0(void);
extern s32 ObjFindNthAttachPoint_1addc0(s32, s32, s32);
extern s32 *ModelGetFrame_1511f0(s32, s32);
extern void CharaPostUpdateMaybe_20f0b0(u8 *, f32);
extern s32 CharaGetActionMode_213850(u8 *);
extern s32 CharaInvincibleTimeOver_2138b0(u8 *);
extern void CharaRequestTint_213fd0(u8 *, s32, s32, f32, f32, f32, f32, f32);
extern void CharaGaugeFullFxStartMaybe_214250(u8 *);
extern void CharaGaugeDrainFxStartMaybe_214260(u8 *);
extern s32 CharaGetId_214a80(u8 *);
extern s32 CharaGetActionTable_214cd0(u8 *);
extern s32 CharaFlagsA44Test808Related_215010(u8 *);
extern void NodeRefObjCloneAndRegister_219500(Obj232670 *);
extern s32 ActCfgTableGetColPrmValue_223460(s32, s32);
extern void CharaSetVelocity_238770(u8 *, f32, f32, f32);
extern void CharaGetVelocity_238890(u8 *, f32 *);
extern s32 IsInBattleMode_288380(void);
extern s32 IsInBattle_288420(void);
extern void NodeRefObjAddClsnPnt_318ca0(Obj232670 *, s32, s32, f32, f32);
extern s32 NodeRefListAdd_318d50(Obj232670 *, s32, s32, s32, s32, f32 *);
extern void NodeRefObjCtor_318ff0(Obj232670 *, s32, s32, s32, f32);
extern C232670 *ActorFindById_3eb870(u8 *, s32);
extern u8 *DListGetHead_42ea60(u8 *);
extern u8 *DListGetNext_42eb30(u8 *);
extern f32 D_0045B080[];
extern u8 D_00471AA0[];
extern f32 D_0047DB14;
extern f32 D_0047E710;
extern f32 D_0047E714;
extern f32 D_0047E718;
extern f32 D_0047E71C;
}

static inline s32 IsA(u8 *o) {
    return (*(s32 *)(o + 0xA44) & 0x1000) != 0;
}

static inline s32 IsB(u8 *o) {
    return (*(s32 *)(o + 0xA44) & 0x2000) != 0;
}

static inline bool NotA(u8 *o) {
    return !((*(s32 *)(o + 0xA44) & 0x1000) != 0);
}

static inline bool NotB(u8 *o) {
    return !((*(s32 *)(o + 0xA44) & 0x2000) != 0);
}

extern "C" void ActionMgrPostUpdateAll_232670(u8 *arg0) {
    Obj232670 obj;
    f32 col[4];
    f32 v[4];
    s32 g;
    f32 k21;
    u8 *it;
    f32 k20;
    f32 kb;
    u8 *nx;
    u8 *o;
    u8 *d;
    C232670 *c;
    s32 e;
    s32 tbl;
    s32 fl;
    s32 grp;
    s32 idx;
    s32 *n;
    s32 *s7;
    s32 s6;
    s32 r;
    s32 kk;

    g = GetCurrentScene_1f5be0();
    k21 = GameSceneGetTimeStep_1ceba0(g);
    it = DListGetHead_42ea60(arg0 + 0x20);
    k20 = D_0047DB14 * *(volatile f32 *)&D_0045B080[0];
    while (it != 0) {
        nx = DListGetNext_42eb30(it);
        o = it + 0x10;
        it = nx;
        if (IsInBattleMode_288380() != 0) {
            d = GetGameData_1fede0();
            c = ActorFindById_3eb870(d, CharaGetId_214a80(o));
            e = ObjRecGetLiveObject_1c4a90(g, CharaGetId_214a80(o));
            tbl = CharaGetActionTable_214cd0(o);
            if (c != 0 && e != 0) {
                c->bf.b1 = (*(s32 *)(o + 0xA44) & 0x10) != 0;
                c->bf.b2 = CharaFlagsA44Test808Related_215010(o);
                if (c->f139() != 0 && CharaInvincibleTimeOver_2138b0(o) != 0 && CharaGetActionMode_213850(o) != 10) {
                    fl = 2;
                    if (c->f101(fl) != 0) {
                        fl |= 0x4000;
                    }
                    NodeRefObjCtor_318ff0(&obj, 1, CharaGetId_214a80(o), fl, 1.0f);
                    for (grp = 0x64; grp <= 0x66; grp++) {
                        idx = 0;
                        while ((n = (s32 *)ObjFindNthAttachPoint_1addc0(e, grp, idx)) != 0) {
                            idx++;
                            if (n[3] == 0) {
                                continue;
                            }
                            s7 = ModelGetFrame_1511f0(e, n[0]);
                            if (s7 == 0) {
                                continue;
                            }
                            col[0] = D_0047E710;
                            col[1] = D_0047E714;
                            col[2] = D_0047E718;
                            col[3] = D_0047E71C;
                            s6 = 0;
                            if (grp == 0x65) {
                                col[0] = *(f32 *)&n[5] * k20;
                                col[1] = *(f32 *)&n[6] * k20;
                                col[2] = *(f32 *)&n[7] * k20;
                            }
                            if (grp == 0x66) {
                                s6 |= 2;
                            }
                            if (tbl != 0) {
                                r = ActCfgTableGetColPrmValue_223460(tbl, s7[0]);
                            } else {
                                r = -1;
                            }
                            kk = NodeRefListAdd_318d50(&obj, CharaGetId_214a80(o), -1, s7[0], r, col);
                            NodeRefObjAddClsnPnt_318ca0(&obj, kk, s6, 0.0f, *(f32 *)&n[4] * k20);
                        }
                    }
                    NodeRefObjCloneAndRegister_219500(&obj);
                    obj.vptr = D_00471AA0;
                }
            }
        }
        if (!NotA(o) && NotB(o)) {
            if (CharaGetId_214a80(o) >= 0 && CharaGetId_214a80(o) < 12 && IsInBattle_288420() != 0) {
                CharaRequestTint_213fd0(o, 4, 2, 160.0f, 240.0f, 250.0f, 10.0f, 1.0f);
                CharaGaugeFullFxStartMaybe_214250(o);
                if (GetGameMode_1f59c0() == 7) {
                    GameSceneSoundSlot0PlaySeVol_1d05f0(g, 0x2C, 1.0f);
                }
            }
        }
        if (NotA(o) && !NotB(o)) {
            if (GetGameMode_1f59c0() == 7) {
                GameSceneSoundSlot0PlaySeVol_1d05f0(g, 0x2A, 1.0f);
            }
            CharaGaugeDrainFxStartMaybe_214260(o);
        }
        if (*(s32 *)(o + 0xA44) & 0x40000) {
            ObjRecSetFlags_1c3e00(g, 1, CharaGetId_214a80(o), 0x4000000);
        } else {
            ObjRecClearFlags_1c3dc0(g, 1, CharaGetId_214a80(o), 0x4000000);
        }
        CharaPostUpdateMaybe_20f0b0(o, k21);
        if (*(s32 *)(arg0 + 0x38) & 0x40000000) {
            *(u64 *)(o + 0x3D0) |= 0x0000400000000000ULL;
            *(u64 *)(o + 0x3D0) |= 0x0000080000000000ULL;
            *(u64 *)(o + 0x3D0) |= 0x0000040000000000ULL;
            *(u64 *)(o + 0x3D0) |= 0x0000020000000000ULL;
            *(u64 *)(o + 0x3D0) |= 0x0000010000000000ULL;
            *(u64 *)(o + 0x3D0) |= 0x0000100000000000ULL;
            CharaGetVelocity_238890(o, v);
            CharaSetVelocity_238770(o, v[0], 0.0f, v[2]);
        }
        if (*(u64 *)(o + 0x3D0) & 0x1000000000000000ULL) {
            ObjRecSetFlags_1c3e00(g, 1, CharaGetId_214a80(o), 0x40);
        }
    }
}
