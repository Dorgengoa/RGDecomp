#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { u8 pad0[0x1C]; s32 f1C; } Game;
typedef struct { u8 pad0[0x20]; f32 f20; } Mv;
typedef struct { u8 pad0[8]; s32 f8; } Snd;
class Pc {
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
    virtual void Reset(s32, s32, s32);
};
class Hd {
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
    virtual s32 IsOn();
};

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" {
Game *GetGameData_1fede0(void);
s32 GetCurrentScene_1f5be0(void);
void GetMapMgr_201a90(void);
s32 GetActionMgr_1fdb50(void);
s32 GetAttackChain_1fdb40(void);
s32 GetLoaderMgr_1f59d0(void);
void GameReqQueueRemoveById_1f5a10(s32);
s32 GetGameModePhase_1f59b0(void);
void SetGameReqHold_1f5890(void);
void TaskStatePushAll_27c220(void);
void TaskSetUpdateTasksPaused_287dd0(s32);
void TaskSetEnabled_27c2a0(s32, void *);
void TaskMoveBefore_27bf50(void *, void *);
void AttackChainStateInit_382ed0(s32);
s32 HeapHandleAllocBack_1cdb10(s32, s32);
void AttackChainEntriesInit_382f10(s32, s32, s32);
void SceneScreenOverlayResetAllMaybe_2f1f00(void);
void TargetMngClearTarget_313c00(void);
void EventObjMgrSuspend_27aef0(void);
s32 GameFlowGetChainCharaId_285f50(void);
s32 GameFlowGetChainTargetId_285f40(void);
s32 GameFlowGetChainNo_285f20(void);
Pc *ActorFindById_3eb870(Game *, s32);
void GameSceneSoundSlot5PlaySe_1d05a0(s32, s32);
void SetGameModePhase_1f59a0(s32);
void ActionMgrSaveMotionAll_2315e0(s32);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaGetPos_2388a0(s32, V4 *);
void CharaGetRot_2388b0(s32, V4 *);
f32 Sinf_128fd0(f32);
f32 Cosf_128d30(f32);
void FieldHudAllySuggestHide_203ca0(void);
void GameDataAttackChainBegin_3e6640(Game *, s32);
s32 LoaderRequestFile_1cd870(s32, void *, s32);
s32 GetStreamMgr_207ea0(void);
void StreamMgrSetChanVolumeFade_1d63a0(s32, s32, f32, s32);
s32 LoaderGetStatus_1cd4f0(s32, s32);
void SceneScreenOverlayResetMaybe_2f1ea0(void);
s32 RecStackPush_1c4240(s32, void *);
s32 RecStackGetSlot_1c4330(s32, s32);
void Sprintf_1343b8(char *, void *, s32, s32);
s32 LoaderGetData_1cd490(s32, s32, s32 *);
s32 ArchiveGetFileByPath_1c2800(s32, void *, s32 *);
u8 AttackChainCfgParse_1f93c0(s32, s32, s32, s32);
s32 MemStackAllocAligned64_14da10(s32, s32);
void *memcpy(void *, const void *, u32);
s32 GetDrawCtxNameTable_15de40(void);
void NameTableRegisterImArchive_1594d0(s32, s32, s32, s32, s32);
void LoaderReleaseById_1cd340(s32, s32);
void SystemVmLoadScript_250ac0(s32, s32, s32);
void SystemVmCall_250a50(s32, s32);
void CameraSwitchTo2KeepView_309fa0(void);
s32 AttackChainGetPhase_382eb0(s32);
s32 AttackChainGetHitCount_382ea0(s32);
s32 AttackChainGetAppliedHitCount_382e80(s32);
void AttackChainSetPhase_382ce0(s32, s32);
s32 SystemVmUpdate_2509f0(void);
void TaskTableRestoreOrder_27bed0(void);
void GameDataAttackChainEnd_3e65b0(Game *, s32, s32);
void FieldHudAllySuggestShow_203c90(void);
void CameraScenePopApplyFov_309f10(void);
void RecStackPop_1c4140(s32, s32);
void SceneTimeScaleRestore_2882d0(void);
void EventObjMgrResume_27aec0(void);
void ActionMgrRestoreSavedMotionAll_231590(s32);
f32 Atan2f_1291a8(f32, f32);
f32 AngleWrap_1cbf30(f32);
void CharaResetBattleStateMaybe_212f20(s32, s32);
void CharaSetYaw_2138f0(s32, f32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
void CharaSetPos_213a40(s32, V4 *);
void ModelSetRot_151080(s32, V4 *);
void ModelSetPos_151110(s32, V4 *);
Mv *CharaGetHitInfo_214a00(s32);
s32 CharaGetActionTable_214cd0(s32);
char *ActCfgTableGetName_223cf0(s32);
s32 strcmp(const char *, const char *);
s32 CharaGetBaseActionMode_213830(s32);
void CharaAddFlags_212460(s32, u64);
void CharaRequestTint_213fd0(s32, s32, s32, f32, f32, f32, f32, f32);
void EffectSpawnFinishingBlow_2d81b0(s32);
s32 GameSceneSoundSlot5GetHandle_1d0790(s32);
s32 SoundNextPlayHandle_1b81c0(void);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
Hd *ObjFindById_3bb3a0(s32, s32);
void NameTableFreeGroup_158ac0(s32, s32);
s32 AttackChainGetBufHandle_382ec0(s32);
void HeapHandleFree_1cdae0(s32, s32);
void StreamStopChan_1cda60(s32, s32);
void AttackChainReset_3828b0(s32);
s32 GetEffectMgr_2d9040(void);
void EffectGroupSetPaused_2e2c80(s32, s32, s32);
void EffectGroupSetHidden_2e2bd0(s32, s32, s32);
Snd *GetStatusEffect_2d9010(void);
void GameSceneCBlurResetMode2Maybe_2f1da0(void);
void GameReqQueuePushFront_1f5ab0(s32, s32);
void TaskStatePopAll_27c250(void);
void ClearGameReqHold_1f5880(void);
extern u8 D_004600B8[];
extern u8 D_00460588[];
extern u8 D_00460C70[];
extern u8 D_00460390[];
extern u8 D_00460A60[];
extern u8 D_00460C88[];
extern u8 D_00460DA8[];
extern u8 D_00460DB8[];
extern u8 D_00460DD0[];
extern u8 D_00460DE8[];
extern u8 D_00460DF8[];
extern char D_00460E08[];
extern f32 D_0045B080[];
extern f32 D_0047D1FC;
extern s32 D_0047EA20;
extern s32 D_0047EA24;
extern s8 D_0047EA28[] __attribute__((section(".sdata")));
extern V4 D_00482240 __attribute__((section(".sdata")));
extern V4 D_00482250 __attribute__((section(".sdata")));
extern s32 D_00482260;
extern s16 D_004821C0;
extern s16 D_004821C2;
extern s32 D_004821C4;
extern s32 D_004821C8;

s32 AttackChainModeUpdate_27f840(void) {
    s32 n12C;
    s32 n128;
    s32 n124;
    s32 n120;
    char buf[0x80];
    V4 pos;
    V4 rot;
    Game *g;
    s32 w;
    s32 lst;
    s32 st;
    s32 sys;
    s32 r;
    s32 o;
    Pc *pc;
    f32 k;
    s32 heap;
    s32 c;
    s32 dat;
    s32 p;
    s32 ok;
    s32 p1;
    s32 p2;
    s32 m1;
    s32 m2;
    s32 n;
    f32 ang;
    f32 dir;
    s32 o2;
    s32 cc;
    s32 t;
    Hd *h;
    s32 d;

    g = GetGameData_1fede0();
    w = GetCurrentScene_1f5be0();
    GetMapMgr_201a90();
    lst = GetActionMgr_1fdb50();
    st = GetAttackChain_1fdb40();
    sys = GetLoaderMgr_1f59d0();
    GameReqQueueRemoveById_1f5a10(9);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
    case 0:
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        TaskSetUpdateTasksPaused_287dd0(1);
        TaskSetEnabled_27c2a0(0, D_004600B8);
        TaskSetEnabled_27c2a0(1, D_00460588);
        TaskSetEnabled_27c2a0(1, D_00460C70);
        TaskSetEnabled_27c2a0(0, D_00460390);
        TaskSetEnabled_27c2a0(0, D_00460A60);
        TaskMoveBefore_27bf50(D_00460A60, D_00460C88);
        AttackChainStateInit_382ed0(st);
        sys = GetLoaderMgr_1f59d0();
        AttackChainEntriesInit_382f10(st, HeapHandleAllocBack_1cdb10(sys, 0x1568), 0xA);
        D_00482260 = 0;
        SceneScreenOverlayResetAllMaybe_2f1f00();
        TargetMngClearTarget_313c00();
        EventObjMgrSuspend_27aef0();
        pc = ActorFindById_3eb870(g, GameFlowGetChainCharaId_285f50());
        if (pc != 0) {
            pc->Reset(0, 0, 0);
        }
        GameSceneSoundSlot5PlaySe_1d05a0(w, 0x43);
        SetGameModePhase_1f59a0(1);
        ActionMgrSaveMotionAll_2315e0(lst);
        o = ActionMgrFindById_233b50(lst, GameFlowGetChainTargetId_285f40());
        if (o != 0) {
            CharaGetPos_2388a0(o, &D_00482240);
            CharaGetRot_2388b0(o, &D_00482250);
        } else {
            o = ActionMgrFindById_233b50(lst, GameFlowGetChainCharaId_285f50());
            if (o != 0) {
                CharaGetPos_2388a0(o, &D_00482240);
                CharaGetRot_2388b0(o, &D_00482250);
                k = D_0045B080[0];
                { f32 t_ = Sinf_128fd0(D_00482250.y); D_00482240.x = D_00482240.x + t_ * k; }
                { f32 t_ = Cosf_128d30(D_00482250.y); D_00482240.z = D_00482240.z + t_ * k; }
            }
        }
        FieldHudAllySuggestHide_203ca0();
        GameDataAttackChainBegin_3e6640(g, GameFlowGetChainCharaId_285f50());
        D_0047EA20 = LoaderRequestFile_1cd870(sys, D_00460DA8, 0);
        StreamMgrSetChanVolumeFade_1d63a0(GetStreamMgr_207ea0(), 0, 0.75f, 0xF);
        return 0;
    case 1:
        switch (LoaderGetStatus_1cd4f0(sys, D_0047EA20)) {
        case 0:
            return 0;
        case -1:
            SceneScreenOverlayResetMaybe_2f1ea0();
            SetGameModePhase_1f59a0(0xC9);
            return 1;
        }
        D_0047EA24 = RecStackPush_1c4240(w, D_00460DB8);
        heap = RecStackGetSlot_1c4330(w, D_0047EA24);
        c = D_0047EA28[GameFlowGetChainCharaId_285f50()];
        Sprintf_1343b8(buf, D_00460DD0, c, GameFlowGetChainNo_285f20());
        dat = LoaderGetData_1cd490(sys, D_0047EA20, &n12C);
        p = ArchiveGetFileByPath_1c2800(dat, D_00460DE8, &n128);
        ok = AttackChainCfgParse_1f93c0(p, n128, GameFlowGetChainCharaId_285f50(), GameFlowGetChainNo_285f20());
        n124 = 0;
        n120 = 0;
        p1 = ArchiveGetFileByPath_1c2800(dat, buf, &n124);
        p2 = ArchiveGetFileByPath_1c2800(dat, D_00460DF8, &n120);
        if (ok == 0 || p1 == 0 || n124 <= 0 || p2 == 0 || n120 <= 0) {
            SceneScreenOverlayResetMaybe_2f1ea0();
            SetGameModePhase_1f59a0(0xC9);
            return 1;
        }
        m1 = MemStackAllocAligned64_14da10(heap, n124 / 16 + 1);
        memcpy((void *)m1, (void *)p1, n124);
        m2 = MemStackAllocAligned64_14da10(heap, n120 / 16 + 1);
        memcpy((void *)m2, (void *)p2, n120);
        NameTableRegisterImArchive_1594d0(GetDrawCtxNameTable_15de40(), m2, 0x32D, heap, 0);
        LoaderReleaseById_1cd340(sys, D_0047EA20);
        D_0047EA20 = -1;
        SystemVmLoadScript_250ac0(m1, 0, heap);
        SystemVmCall_250a50(1000, w);
        CameraSwitchTo2KeepView_309fa0();
        SetGameModePhase_1f59a0(0x64);
        return 0;
    case 0x64:
        if (AttackChainGetPhase_382eb0(st) == 5) {
            n = AttackChainGetHitCount_382ea0(st);
            if (n <= AttackChainGetAppliedHitCount_382e80(st)) {
                AttackChainSetPhase_382ce0(st, 6);
            }
        }
        if (AttackChainGetPhase_382eb0(st) == 0xB) {
            AttackChainSetPhase_382ce0(st, 0xC);
            SystemVmCall_250a50(5000, w);
            return 0;
        }
        if (SystemVmUpdate_2509f0() != 1) {
            return 0;
        }
        SetGameModePhase_1f59a0(0xC8);
        return 0;
    case 0xC8:
        SystemVmCall_250a50(2000, w);
        do {
        } while (SystemVmUpdate_2509f0() != 1);
        SetGameModePhase_1f59a0(0xC9);
    case 0xC9:
        TaskTableRestoreOrder_27bed0();
        n = GameFlowGetChainCharaId_285f50();
        GameDataAttackChainEnd_3e65b0(g, n, AttackChainGetHitCount_382ea0(st));
        FieldHudAllySuggestShow_203c90();
        CameraScenePopApplyFov_309f10();
        RecStackPop_1c4140(w, D_0047EA24);
        D_0047EA24 = -1;
        SceneTimeScaleRestore_2882d0();
        EventObjMgrResume_27aec0();
        ActionMgrRestoreSavedMotionAll_231590(lst);
        o = ActionMgrFindById_233b50(lst, GameFlowGetChainCharaId_285f50());
        if (o != 0) {
            CharaGetPos_2388a0(o, &pos);
            ang = Atan2f_1291a8(pos.x - D_00482240.x, pos.z - D_00482240.z);
            dir = AngleWrap_1cbf30(D_0047D1FC + ang);
            CharaResetBattleStateMaybe_212f20(o, 1);
            CharaSetYaw_2138f0(o, dir);
            o2 = ActionMgrFindById_233b50(lst, GameFlowGetChainTargetId_285f40());
            if (o2 != 0) {
                cc = ObjRecGetLiveObject_1c4a90(w, GameFlowGetChainTargetId_285f40());
                if (cc != 0) {
                    CharaSetPos_213a40(o2, &D_00482240);
                    CharaSetYaw_2138f0(o2, ang);
                    ZERO(&rot, 0x10);
                    rot.y = ang;
                    rot.x = 0.0f;
                    rot.z = 0.0f;
                    ModelSetRot_151080(cc, &rot);
                    ModelSetPos_151110(cc, &D_00482240);
                }
                CharaGetHitInfo_214a00(o2)->f20 = dir;
                if (AttackChainGetHitCount_382ea0(st) > 0) {
                    t = CharaGetActionTable_214cd0(o2);
                    if (t == 0 || strcmp(ActCfgTableGetName_223cf0(t), D_00460E08) != 0 || CharaGetBaseActionMode_213830(o2) != 1) {
                        CharaAddFlags_212460(o2, (u64)4 << 32);
                    }
                    CharaRequestTint_213fd0(o2, 3, 2, 250.0f, 118.0f, 80.0f, 10.0f, 1.0f);
                    EffectSpawnFinishingBlow_2d81b0(GameFlowGetChainTargetId_285f40());
                    d = GameSceneSoundSlot5GetHandle_1d0790(w);
                    SoundPlayScaledVolume_1b9520(d, 0x19, SoundNextPlayHandle_1b81c0(), 1.0f);
                    h = ObjFindById_3bb3a0(g->f1C, GameFlowGetChainTargetId_285f40());
                    if (h != 0 && h->IsOn() != 0) {
                        d = GameSceneSoundSlot5GetHandle_1d0790(w);
                        SoundPlayScaledVolume_1b9520(d, 0x56, SoundNextPlayHandle_1b81c0(), 1.0f);
                    }
                }
            }
        }
        StreamMgrSetChanVolumeFade_1d63a0(GetStreamMgr_207ea0(), 0, 1.0f, 0xF);
        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32D);
        sys = GetLoaderMgr_1f59d0();
        HeapHandleFree_1cdae0(sys, AttackChainGetBufHandle_382ec0(st));
        StreamStopChan_1cda60(sys, 1);
        StreamStopChan_1cda60(sys, 2);
        AttackChainReset_3828b0(st);
        d = GetEffectMgr_2d9040();
        EffectGroupSetPaused_2e2c80(d, 1000, 0);
        EffectGroupSetHidden_2e2bd0(d, 1000, 0);
        EffectGroupSetPaused_2e2c80(d, 2000, 0);
        EffectGroupSetHidden_2e2bd0(d, 2000, 0);
        EffectGroupSetPaused_2e2c80(d, 3000, 0);
        EffectGroupSetHidden_2e2bd0(d, 3000, 0);
        {
            Snd *sn = GetStatusEffect_2d9010();
            sn->f8 = 1;
        }
        D_004821C0 = -1;
        D_004821C2 = -1;
        D_004821C4 = 0;
        D_004821C8 = 0;
        GameSceneCBlurResetMode2Maybe_2f1da0();
        GameReqQueuePushFront_1f5ab0(0, -1);
        TaskStatePopAll_27c250();
        ClearGameReqHold_1f5880();
        return 1;
    }
    return 0;
    return 0;
}
}
