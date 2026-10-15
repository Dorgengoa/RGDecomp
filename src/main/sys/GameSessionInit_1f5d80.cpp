#include "types.h"

typedef struct Cfg5d80 {
    s16 mode;
    u8 m2;
    u8 m3;
    s16 m4;
    s16 m6;
    s16 m8;
    s16 mA;
    s16 mC;
    s16 mE;
    s16 m10;
    u8 pad12[0x34 - 0x12];
    s16 m34;
    s16 m36;
    s16 m38;
    u8 pad3A[2];
    u8 b0:1;
    u8 b1:1;
    u8 b2:1;
    u8 b3:5;
    u8 pad3D[0x70 - 0x3D];
} __attribute__((aligned(4))) Cfg5d80;

typedef struct Buf5d80 {
    u8 pad0[0x2C];
    s32 m2C;
    u8 pad30[4];
    s32 m34;
} Buf5d80;

typedef struct Sys5d80 {
    u8 pad0[0xC];
    s32 mC;
} Sys5d80;

extern "C" {
void DelayThread_117618(s32);
void Tanf_1290b8(f32);
void Srand_1336f8(s32);
void ViewSetProjectionBasic_143180(s32, f32, f32, f32, f32);
s32 MemStackAllocAligned64_14da10(Buf5d80 *, s32);
void DrawEnvSetClearColorVec_15ca70(void *);
void LightStateSetAmbient_15cb30(void *);
void LightStateSetMatrices_15cc00(void *, void *);
void CameraSetFogEnable_15cce0(s32);
s32 GetDrawCtx_15de80(void);
void PadClearStickDpadThreshold_183940(void *);
void PadClearRepeatAll_183960(void *);
void PadWaitReady_1849e0(void *);
void SoundNoteListAlloc_1b4f00(s32, s32, s32);
s32 CdDiscGetCurrent_1c3080(void);
void CdDiscSelect_1c3090(s32);
s32 GetKeyCapModeMaybe_1c3540(void);
void SetAspectMode_1c6a90(s32);
void FrameCounterReset_1c6b10(void);
s32 GetStaticScene_1c6c70(void);
s32 GetMainStack_1c6dc0(void);
s32 LoaderCountQueued_1cd620(s32 *);
void LoaderSetSyncMode_1cd880(s32 *, s32, s32);
void LoaderInit_1cde60(s32 *, s32, s32, s32, s32, s32);
void LoaderClear_1ce040(s32 *);
void GameSceneSetTimeScaleSuspendedMaybe_1ceb60(s32, s32);
void ScreenFadeOutColor_1cf730(s32, s32, f32, f32, f32);
void ScreenFadeReset_1cf760(s32);
void GameSceneSoundFadeOut_1d0340(s32, s32);
void GameSceneSoundSlot4SetVolume_1d0630(s32, f32);
void ClearGameReqHold_1f5880(void);
void GameModeStackReset_1f5940(void);
s32 *GetLoaderMgr_1f59d0(void);
void GameReqQueuePushFront_1f5ab0(s32, s32);
void GameReqQueuePushBack_1f5b50(s32, s32);
s32 GetGameReqQueue_1f5bc0(void);
void SetCurrentScene_1f5bd0(s32);
s32 GetCurrentScene_1f5be0(void);
void CameraSnapToLeader_1f6a00(void);
void Nop_1f6c00(void);
void SceneCamerasInit_1f6c10(s32, s32);
void TaskCharaFollow_1f9770(void);
void TaskCharaMove_1f9790(void);
void SceneObjsStep_1f97a0(void);
void TaskCharaInfo_1f9c70(void);
void TaskCharaAction_1fa5c0(void);
void TaskCharaEnd_1fae60(void);
void TaskCharaBegin_1fb140(void);
void StaticObjPacLoad_1fb670(void);
void CharaSystemsInit_1fbb50(s32, s32);
void GameDataApplyUnlockMask_1fe4b0(void);
void WorldDataLoadParamPac_1fe5a0(bool, s32);
void LoadingScreenLoadText_1fe7f0(void *, s32, s32, s32, s32);
void WorldDataRebuild_1feac0(bool);
void GameDataTick_1febd0(void);
void GameDataRunStartConfigMaybe_1fec40(Cfg5d80 *);
void WorldDataRelated_1fecd0(s32);
Sys5d80 *GetGameData_1fede0(void);
void EventTimerMonographsSpawnMaybe_1fee00(void);
void TaskStepMap_200d70(void);
void TaskUpdateFogParam_201240(void);
void TaskUpdateMapInfo_201340(void);
void EffectCommonTexLoadMaybe_2015e0(void);
void MapSystemsInit_2017f0(s32, s32);
void SceneParentStackSetup_202030(void);
void SystemHeapsInit_2020d0(void);
void GameSceneBufsInitMaybe_202390(s32);
s32 GetReadBuffHeap_2025e0(void);
s32 GetSystemMemStack_202600(void);
void MenuFixResLoadMaybe_205110(void);
void MenuStaticMsgLoad_2052e0(void);
void MenuFixInitMaybe_205390(s32);
void FontResLoadAll_205540(void);
void Nop_2055e0(s32);
void MenuResGroupInit_206940(s32);
void SynopsisStackRelease_206b10(void);
void SynopsisStackInit_206b20(void);
Buf5d80 *GetSynopsisStack_206b40(void);
void StreamChan0SetFillThreshold_2073e0(f32);
void Nop_207950(void);
void SoundStreamChannelsInit_207960(s32, s32);
void SceneSoundUpdate_207a50(void);
void TaskLoadSound_207a80(void);
void SoundMapTablesLoad_207ac0(s32);
void SoundEnvPresetTableInitMaybe_207be0(s32, s32);
void SceneSoundEnvApplyPreset_207e20(s32, s32);
s32 GetStreamMgr_207ea0(void);
void SoundInitStubRelated_207ed0(void);
s32 IsTgsDemoBuild_207f20(void);
void Nop_207fa0(void);
void DbgLogClassSize_208a00(void *, s32);
void DbgLogMarkerMaybe_208a10(void *, s32);
void GameReqListAlloc_20a510(s32, s32, s32);
void GameReqListInit_20a560(s32);
void EventSysStub_27adb0(void);
void EventSysGameInitMaybe_27adc0(s32, s32);
void TaskTableInit_27c310(void);
void GameFlowReset_285c70(void);
void ClearPad2Enabled_2882a0(void);
void MapInitObjLoad_2d11a0(void);
void EventObjDataInit_2d12d0(s32, s32);
void EffectSysStub_2d8a70(void);
void EffectMgrInit_2d8a80(s32, s32);
void SoundEnvPresetApplyWaitLoad_2f48c0(void);
void MapLoadFromGameDataAndWait_2f4920(void);
void PartyLoadAndPlaceMembersMaybe_2f4b00(void);
void StaticEffectLoadWait_2f5180(void);
s32 StreamPlayAllowedMaybe_2f5210(void);
void PadIdleTimerReset_2f5ac0(void);
void PauseSysInit_2f65a0(void);
void BlurWorkTexRegister_2f67b0(void);
void FocusWorkTexRegister_2f6910(void);
void DofWorkTexRegister_2f6a30(void);
void GlareWorkTexRegister_2f6be0(void);
void ShadowWorkTexRegister_2f6c90(void);
void SceneScreenFadeStep_2f6e90(void);
void LoaderTickGlobal_2f74c0(void);
void SoundSetListenerFromCamera_2f74f0(void);
void LensWorkTexRegister_2f7620(void);
void SceneResetDefaults_2f7720(void);
void NpcObjTableStub_3127f0(void);
void NpcObjTableSetup_312800(s32);
void SphereModelLoad_313c60(void);
void FieldObjSysInit_313d40(s32, s32);
void InsectBattleGlobalsClear_31a750(void);
void LiveTalkStub_321220(void);
void LiveTalkInit_321230(s32, s32);
void TreasureBoxPoolStub_338970(void);
void TreasureBoxPoolSetup_338980(s32);
s32 LoadingScreenIsFinished_343090(void);
f32 LoadingScreenGetTimer_3430a0(void);
s32 LoadingScreenIsClosed_3430b0(void);
void LoadingScreenTryFinish_3430c0(void);
s32 LoadingScreenRequestEnd_343100(void);
void LoadingScreenResetEntriesMaybe_343140(void);
void LoadingScreenSetProgress_343190(f32, f32);
void LoadingScreenStop_3431e0(void);
void LoadingScreenStart_343240(void *);
void HatenaMarkInitAll_345d70(void);
void HatenaMarkListResetGlobal_345de0(s32);
void FactoryReset_367e80(void);
s32 StateGetRequiredDisc_3d5ed0(s32);
void OptionsSetDataSetIndexMaybe_3d5f00(s32, s32);
void OptionsSetFlagMaybe_3d6180(s32, s32);
void GameDataUnlockByMinGaugeLevelMaybe_3e4110(Sys5d80 *);
void SoundStreamSetMasterVolumeThunkMaybe_1bc6f0(s32, f32);
void SoundRpcFrameTickThunkMaybe_1bd690(s32);

extern char D_0044B5A0[];
extern char D_0044B5E0[];
extern char D_0045B8E8[];
extern char D_0045B8F8[];
extern char D_0045B908[];
extern char D_0045B918[];
extern char D_0045B928[];
extern char D_0045B938[];
extern char D_0045B948[];
extern char D_0045B958[];
extern char D_0045B968[];
extern char D_0045B978[];
extern char D_0045B988[];
extern char D_0045B998[];
extern char D_0045B9A8[];
extern char D_0045B9B8[];
extern char D_0045B9C8[];
extern char D_0045B9D8[];
extern char D_0045B9F0[];
extern char D_0045BA10[];
extern char D_0045BA30[];
extern char D_0045BA50[];
extern char D_0045BA70[];
extern char D_0045BA88[];
extern char D_0045BA98[];
extern char D_0045BAA8[];
extern char D_0045BAB8[];
extern char D_0045BAC8[];
extern char D_0045BAE0[];
extern char D_0045BB00[];
extern char D_0045BB20[];
extern char D_0045BB40[];
extern char D_0045BB60[];
extern char D_0045BB80[];
extern char D_0045BBA0[];
extern char D_0045BBC0[];
extern char D_0045BBE0[];
extern char D_0045BC00[];
extern char D_0045BC20[];
extern char D_0045BC40[];
extern char D_0045BC58[];
extern s32 D_0045B090[];
extern s32 D_0045B098[];
extern char D_004B2570[];
extern char D_004B27E0[];
extern s32 D_004B5220[];
extern s32 D_004B5224[];
extern s32 D_004B5228[];
extern s32 D_004B522C[];
extern s32 D_004B5230[];
extern s32 D_004B5234[];
extern s32 D_004B5644[];
extern s32 D_004B5648[];
extern s32 D_004B5650[];
extern f32 D_0047D4A0;
extern f32 D_0047DB50;
extern f32 D_0047DC8C;
extern f32 D_0047DCEC;
extern s32 D_0047DF30;
extern s32 D_0047E460;
extern u8 D_004819D8;
extern s32 D_004819E0;
extern s8 D_004819F0;
}

static inline bool ready5d80(void)
{
    return LoadingScreenRequestEnd_343100();
}

extern "C" void GameSessionInit_1f5d80(Cfg5d80 cfg)
{
    s32 x;
    s32 wait;
    s32 *p;
    s32 cur;
    s32 id2;
    u8 *sys;
    bool first;
    s32 i;
    s32 c2;
    Buf5d80 *buf;
    bool on;
    Sys5d80 *s;
    s32 ctx;
    bool hit;
    s32 a;
    s32 obj;
    s32 d;

    DbgLogMarkerMaybe_208a10(D_0045B8E8, 0x3C);
    PadWaitReady_1849e0(D_004B2570);
    ClearPad2Enabled_2882a0();
    if (cfg.m2 == 0) {
        SoundInitStubRelated_207ed0();
    }
    DbgLogClassSize_208a00(D_0045B8F8, 0x43A0);
    DbgLogClassSize_208a00(D_0045B908, 0xB570);
    DbgLogClassSize_208a00(D_0045B918, 0x790);
    DbgLogClassSize_208a00(D_0045B928, 0x60);
    DbgLogClassSize_208a00(D_0045B938, 0x264);
    DbgLogClassSize_208a00(D_0045B948, 0x58);
    DbgLogClassSize_208a00(D_0045B958, 0x1710);
    DbgLogClassSize_208a00(D_0045B968, 0x17D0);
    DbgLogClassSize_208a00(D_0045B978, 0x54);
    DbgLogClassSize_208a00(D_0045B988, 0x1CC);
    DbgLogClassSize_208a00(D_0045B998, 0x58);
    DbgLogClassSize_208a00(D_0045B9A8, 0xCC);
    DbgLogClassSize_208a00(D_0045B9B8, 0x50);
    DbgLogClassSize_208a00(D_0045B9C8, 0x40);
    DbgLogClassSize_208a00(D_0045B9D8, 0x180);
    DbgLogClassSize_208a00(D_0045B9F0, 0xE0);
    DbgLogClassSize_208a00(D_0045BA10, 0x110);
    DbgLogClassSize_208a00(D_0045BA30, 0x1B0);
    DbgLogClassSize_208a00(D_0045BA50, 0x110);
    DbgLogClassSize_208a00(D_0045BA70, 0x140);
    DbgLogClassSize_208a00(D_0045BA88, 0xB70);
    DbgLogClassSize_208a00(D_0045BA98, 0x180);
    DbgLogClassSize_208a00(D_0045BAA8, 0x6C);
    DbgLogClassSize_208a00(D_0045BAB8, 0x18);
    DbgLogClassSize_208a00(D_0045BAC8, 0x50);
    DbgLogClassSize_208a00(D_0045BAE0, 0x40);
    DbgLogClassSize_208a00(D_0045BB00, 0xD18);
    DbgLogClassSize_208a00(D_0045BB20, 0xF98);
    DbgLogClassSize_208a00(D_0045BB40, 0x22B0);
    DbgLogClassSize_208a00(D_0045BB60, 0x28);
    DbgLogClassSize_208a00(D_0045BB80, 0x530);
    DbgLogClassSize_208a00(D_0045BBA0, 0x154);
    DbgLogClassSize_208a00(D_0045BBC0, 0x4080);
    DbgLogClassSize_208a00(D_0045BBE0, 0x340);
    DbgLogClassSize_208a00(D_0045BC00, 0x50);
    DbgLogClassSize_208a00(D_0045BC20, 0x70);
    DbgLogClassSize_208a00(D_0045BC40, 0x150);
    DbgLogClassSize_208a00(D_0045BC58, 0x30);
    FrameCounterReset_1c6b10();
    GameModeStackReset_1f5940();
    GameFlowReset_285c70();
    TaskTableInit_27c310();
    SetCurrentScene_1f5bd0(GetStaticScene_1c6c70());
    SystemHeapsInit_2020d0();
    SceneResetDefaults_2f7720();
    GameSceneBufsInitMaybe_202390(GetSystemMemStack_202600());
    CameraSetFogEnable_15cce0(1);
    x = GetGameReqQueue_1f5bc0();
    GameReqListInit_20a560(x);
    GameReqListAlloc_20a510(x, 0x20, GetSystemMemStack_202600());
    p = GetLoaderMgr_1f59d0();
    LoaderClear_1ce040(p);
    LensWorkTexRegister_2f7620();
    InsectBattleGlobalsClear_31a750();
    FactoryReset_367e80();
    *p = GetReadBuffHeap_2025e0();
    LoaderSetSyncMode_1cd880(p, 1, 0);
    ShadowWorkTexRegister_2f6c90();
    GlareWorkTexRegister_2f6be0();
    DofWorkTexRegister_2f6a30();
    FocusWorkTexRegister_2f6910();
    BlurWorkTexRegister_2f67b0();
    PauseSysInit_2f65a0();
    PadIdleTimerReset_2f5ac0();
    Nop_207fa0();
    PadClearRepeatAll_183960(D_004B2570);
    PadClearRepeatAll_183960(D_004B27E0);
    PadClearStickDpadThreshold_183940(D_004B2570);
    PadClearRepeatAll_183960(D_004B2570);
    PadWaitReady_1849e0(D_004B2570);
    LightStateSetMatrices_15cc00(D_0044B5A0, D_0044B5E0);
    LightStateSetAmbient_15cb30(&D_0047E460);
    DrawEnvSetClearColorVec_15ca70(&D_004819E0);
    Tanf_1290b8(D_0047D4A0);
    ViewSetProjectionBasic_143180(GetDrawCtx_15de80(), D_0047D4A0, 5.0f, 10000, 0.75f);
    sys = (u8 *)GetCurrentScene_1f5be0();
    ctx = GetMainStack_1c6dc0();
    obj = GetSystemMemStack_202600();
    WorldDataRelated_1fecd0(obj);
    MenuResGroupInit_206940(obj);
    SoundNoteListAlloc_1b4f00((s32)(sys + 0xB0A4), 0x40, obj);
    ScreenFadeReset_1cf760((s32)sys);
    ScreenFadeOutColor_1cf730((s32)sys, 0, 0.0f, 0.0f, 0.0f);
    MenuFixInitMaybe_205390(obj);
    Nop_2055e0(obj);
    SceneCamerasInit_1f6c10(ctx, obj);
    SoundEnvPresetTableInitMaybe_207be0(ctx, obj);
    SoundStreamChannelsInit_207960(ctx, obj);
    MapSystemsInit_2017f0(ctx, obj);
    CharaSystemsInit_1fbb50(ctx, obj);
    EffectMgrInit_2d8a80(ctx, obj);
    EventObjDataInit_2d12d0(ctx, obj);
    FieldObjSysInit_313d40(ctx, obj);
    LiveTalkInit_321230(ctx, obj);
    EventSysGameInitMaybe_27adc0(ctx, obj);
    NpcObjTableSetup_312800(ctx);
    TreasureBoxPoolSetup_338980(obj);
    HatenaMarkListResetGlobal_345de0(obj);
    SceneParentStackSetup_202030();
    *p = GetReadBuffHeap_2025e0();
    LoaderInit_1cde60(p, 0x40, 0x50, 8, 0x50, GetSystemMemStack_202600());
    if (GetKeyCapModeMaybe_1c3540() != 0) {
        SetAspectMode_1c6a90(1);
        OptionsSetFlagMaybe_3d6180(GetGameData_1fede0()->mC, 1);
        GameSceneSetTimeScaleSuspendedMaybe_1ceb60(GetCurrentScene_1f5be0(), 1);
    }
    LoaderSetSyncMode_1cd880(p, 1, 0);
    SynopsisStackInit_206b20();
    buf = GetSynopsisStack_206b40();
    if (D_004819F0 == 0) {
        D_004B5220[0] = -1;
        D_004B5224[0] = 0;
        D_004B5228[0] = 0;
        D_004B5650[0] = 0;
        D_004819F0 = 1;
    }
    D_004B5220[0] = D_0047DF30;
    D_004B5224[0] = MemStackAllocAligned64_14da10(buf, 0x4000);
    D_004B5228[0] = 0x40000;
    D_004B5234[0] = buf->m34 - buf->m2C;
    D_004B5230[0] = MemStackAllocAligned64_14da10(buf, D_004B5234[0]);
    D_004B522C[0] = 0x31A;
    a = -1;
    on = true;
    wait = 0x1F7;
    d = 0;
    ctx = -1;
    obj = -1;
    switch (cfg.mode) {
    case 0:
        a = 1;
        ctx = 0;
        obj = 10;
        break;
    case 1:
        a = cfg.m6;
        ctx = cfg.m8;
        obj = cfg.mA;
        d = cfg.mC;
        break;
    case 2:
        a = 1;
        ctx = 0;
        obj = 10;
        on = false;
        wait = 0x1F4;
        break;
    case 4:
        a = -1;
        break;
    case 5:
        a = cfg.m34;
        ctx = cfg.m36;
        obj = cfg.m38;
        d = d | (cfg.b0 ? 1 : 0);
        d = d | (cfg.b1 ? 2 : 0);
        d = d | (cfg.b2 ? 4 : 0);
        break;
    case 6:
        a = cfg.mC;
        ctx = cfg.mE;
        obj = cfg.m10;
        if (cfg.m4 == 4) {
            if (cfg.mA == D_0045B090[0] || cfg.mA == D_0045B098[0]) {
                on = false;
                wait = 0x1F4;
            }
        }
        break;
    }
    if (IsTgsDemoBuild_207f20() != 0) {
        on = false;
    }
    first = false;
    if (cfg.mode == 0) {
        first = true;
    }
    if (cfg.mode != 1) {
        WorldDataRebuild_1feac0(first);
    }
    if (on) {
        LoadingScreenLoadText_1fe7f0(D_004B5220, a, ctx, obj, d);
    } else {
        D_004B5650[0] = 1;
        D_004B5644[0] = 0;
        D_004B5648[0] = 1;
    }
    D_004819D8 = 0;
    PadWaitReady_1849e0(D_004B2570);
    LoadingScreenStart_343240(D_004B5220);
    SoundMapTablesLoad_207ac0(0);
    SceneSoundEnvApplyPreset_207e20(wait, 0);
    for (;;) {
        LoaderTickGlobal_2f74c0();
        TaskLoadSound_207a80();
        SceneSoundUpdate_207a50();
        if (LoaderCountQueued_1cd620(p) <= 0) {
            break;
        }
        DelayThread_117618(10);
    }
    FontResLoadAll_205540();
    MenuStaticMsgLoad_2052e0();
    D_004819D8 = 1;
    LoadingScreenResetEntriesMaybe_343140();
    LoadingScreenSetProgress_343190(D_0047DB50, D_0047DC8C);
    if (cfg.mode != 1) {
        WorldDataLoadParamPac_1fe5a0(first, 0);
        GameDataRunStartConfigMaybe_1fec40(&cfg);
        GameDataApplyUnlockMask_1fe4b0();
    }
    MenuFixResLoadMaybe_205110();
    Nop_1f6c00();
    Nop_207950();
    EffectCommonTexLoadMaybe_2015e0();
    StaticObjPacLoad_1fb670();
    EffectSysStub_2d8a70();
    MapInitObjLoad_2d11a0();
    SphereModelLoad_313c60();
    LiveTalkStub_321220();
    EventSysStub_27adb0();
    NpcObjTableStub_3127f0();
    TreasureBoxPoolStub_338970();
    HatenaMarkInitAll_345d70();
    c2 = GetCurrentScene_1f5be0();
    GameSceneSoundSlot4SetVolume_1d0630(c2, 0.0f);
    StaticEffectLoadWait_2f5180();
    LoadingScreenSetProgress_343190(0.75f, D_0047DC8C);
    PartyLoadAndPlaceMembersMaybe_2f4b00();
    LoadingScreenSetProgress_343190(1.0f, D_0047DC8C);
    MapLoadFromGameDataAndWait_2f4920();
    if (GetKeyCapModeMaybe_1c3540() != 0) {
        Srand_1336f8(0x270F);
    }
    TaskUpdateMapInfo_201340();
    EventTimerMonographsSpawnMaybe_1fee00();
    for (i = 0; i < 15; i++) {
        SoundSetListenerFromCamera_2f74f0();
        TaskUpdateFogParam_201240();
        TaskStepMap_200d70();
        CameraSnapToLeader_1f6a00();
        TaskCharaBegin_1fb140();
        TaskCharaAction_1fa5c0();
        TaskCharaInfo_1f9c70();
        SceneObjsStep_1f97a0();
        TaskCharaMove_1f9790();
        TaskCharaFollow_1f9770();
        TaskCharaEnd_1fae60();
        GameDataTick_1febd0();
        SceneScreenFadeStep_2f6e90();
    }
    s = GetGameData_1fede0();
    GameDataUnlockByMinGaugeLevelMaybe_3e4110(s);
    id2 = StateGetRequiredDisc_3d5ed0(s->mC);
    cur = CdDiscGetCurrent_1c3080();
    if (cur != id2) {
        CdDiscSelect_1c3090(StateGetRequiredDisc_3d5ed0(s->mC));
    }
    OptionsSetDataSetIndexMaybe_3d5f00(s->mC, -1);
    while (!ready5d80()) {
        DelayThread_117618(10);
    }
    hit = false;
    for (;;) {
        if (LoadingScreenIsFinished_343090() != 0) {
            break;
        }
        if (IsTgsDemoBuild_207f20() != 0) {
            if (!(LoadingScreenGetTimer_3430a0() <= 120.0f)) {
                LoadingScreenTryFinish_3430c0();
                hit = true;
                break;
            }
        }
        DelayThread_117618(10);
    }
    SoundEnvPresetApplyWaitLoad_2f48c0();
    for (;;) {
        if (LoadingScreenIsClosed_3430b0() != 0) {
            break;
        }
        DelayThread_117618(10);
    }
    LoadingScreenStop_3431e0();
    SynopsisStackRelease_206b10();
    LoaderSetSyncMode_1cd880(p, 0, 0);
    if (StreamPlayAllowedMaybe_2f5210() != 0) {
        s32 e = GetStreamMgr_207ea0();
        SoundRpcFrameTickThunkMaybe_1bd690(e);
        SoundStreamSetMasterVolumeThunkMaybe_1bc6f0(e, 1.0f);
        StreamChan0SetFillThreshold_2073e0(D_0047DCEC);
    }
    GameReqQueuePushBack_1f5b50(1, -1);
    ClearGameReqHold_1f5880();
    if (hit) {
        GameReqQueuePushFront_1f5ab0(3, -1);
    }
    GameSceneSoundFadeOut_1d0340(c2, 0x2D);
}
