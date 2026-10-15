#include "types.h"
#pragma divbyzerocheck on
#pragma optimization_level 3

typedef unsigned __int128 u128;

struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

struct Mat {
    Vec a;
    Vec b;
    Vec c;
    Vec d;
};

struct S24 {
    s32 w[6];
};

struct S80 {
    s32 w[20];
};

struct ChBase {
    u8 pad0[0x1B0];
};

class Ch : public ChBase {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void f44(f32);
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void f54(s32);
    u8 pad1B4[0x2B0];
    s32 f464;
    u8 f468;
};

struct ObjBase {
    u8 pad0[0xB0];
};

class Obj : public ObjBase {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void f54(f32, f32, f32);
};

struct Info {
    s16 id;
    S24 a;
    S80 b;
};

struct ObjData {
    u8 pad0[0x10];
    Info info;          /* 0x10 */
    u8 pad7C[0x34];
    void *vt;           /* 0xB0 */
    u8 padB4[0x14];
    f32 fC8;            /* 0xC8 */
    u8 padCC[0xC4];
    f32 f190;           /* 0x190 */
    u8 pad194[0xC];
};

class Vp280;
class Vp2D8;
class Vp320;

struct Pc;
struct Mc;
struct Ev;

struct Mgr {
    u8 pad0[0x38];
    u32 f38;
};

struct Chr {
    u8 pad0[0xA44];
    u32 fA44;
};

struct Ctx {
    u8 pad0[0x14];
    s32 f14;
    struct {
        u8 pad0[0x30];
        s16 f30;
    } *f18;
    s32 f1C;
    s32 f20;
};

struct St {
    u8 pad0[8];
    s32 f8;
};

struct Pp {
    u8 pad0[4];
    s32 f4;
    u8 pad8[0x20];
    s8 f28;
};

struct Pcv {
    virtual void d0();
};

extern "C" {
void *memcpy(void *, const void *, u32);
char *strcpy(char *, const char *);
void Sprintf_1343b8(char *, const char *, void *);
void *MemStackAllocAligned64_14da10(s32, s32);
void ModelSetRot_151080(Ch *, Vec *);
void ModelSetPos_151110(Ch *, Vec *);
Pp *ModelGetRootFrame_1511a0(Ch *);
s32 ScriptVmHasLabel_1768f0(s32, s32);
s32 PadIsTriggered_1839f0(void *, s32);
void PadUpdateVibration_184250(void *, s32);
void PadUpdate_1843a0(void *);
void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
void ObjRecSetFlag2_1c3e80(s32, s32, s32);
void RecStackPop_1c4140(s32, s32);
s32 RecStackPush_1c4240(s32, const char *);
s32 RecStackGetSlot_1c4330(s32, s32);
Ch *ObjRecGetLiveObject_1c4a90(s32, s32);
void MatFromRotPos_1caf90(Mat *, Vec *, Vec *);
void MatMulPoint_1cb8e0(Vec *, Mat *, Vec *);
void LoaderPurgeAll_1cd240(s32);
void LoaderReleaseById_1cd340(s32, s32);
void *LoaderGetData_1cd490(s32, s32, s32 *);
s32 LoaderGetStatus_1cd4f0(s32, s32);
s32 LoaderCountQueued_1cd620(s32);
s32 LoaderRequestFile_1cd870(s32, char *, s32);
void StreamPauseChan_1cd9f0(s32, s32);
void StreamStopChan_1cda60(s32, s32);
void GameSceneSoundSlot1PlaySeVol_1d05e0(s32, s32, f32);
void GameSceneSoundSlot0PlaySeVol_1d05f0(s32, s32, f32);
s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
s32 MapDataIsNoDarken_1e7aa0(s32);
void ClearGameReqHold_1f5880(void);
void SetGameReqHold_1f5890(void);
void SetGameModePhase_1f59a0(s32);
s32 GetGameModePhase_1f59b0(void);
s32 GetLoaderMgr_1f59d0(void);
void GameReqQueueRemoveById_1f5a10(s32);
s32 GameReqQueuePeekHead_1f5a70(s32);
void GameReqQueuePushBack_1f5b50(s32, s32);
Mgr *GetActionMgr_1fdb50(void);
s32 GetCharaResMgr_1fdb60(void);
Ctx *GetGameData_1fede0(void);
s32 GetMapMgr_201a90(void);
void FieldHudAllySuggestShow_203c90(void);
void FieldHudAllySuggestHide_203ca0(void);
void FieldHudFadeIn_203ee0(void);
void FieldHudLogOpen_203fb0(void);
void FieldHudFadeOut_204080(void);
void CharaPlayMotion_212590(Chr *, Ch *, char *, s32, f32);
void CharaResetBattleStateMaybe_212f20(Chr *, s32);
s32 CharaGetBaseActionMode_213830(Chr *);
s32 CharaGetActionMode_213850(Chr *);
void CharaSetInvincibleTime_2138a0(Chr *, f32);
void CharaSetYaw_2138f0(Chr *, f32);
void CharaSetPos_213a40(Chr *, Vec *);
void CharaSetSavedRot_214290(Chr *, Vec *);
void CharaGetSavedRot_2142b0(Chr *, Vec *);
void CharaSetSavedPos_2142e0(Chr *, Vec *);
void CharaGetSavedPos_214300(Chr *, Vec *);
s32 CharaGetId_214a80(Chr *);
void ActionMgrRestoreSavedMotionAll_231590(Mgr *);
void ActionMgrSaveMotionAll_2315e0(Mgr *);
s32 ActionMgrGetCharaList_233b40(Mgr *);
Chr *ActionMgrFindById_233b50(Mgr *, s32);
void CharaGetPos_2388a0(Chr *, Vec *);
void CharaGetRot_2388b0(Chr *, Vec *);
s32 SystemVmUpdate_2509f0(void);
void SystemVmCall_250a50(s32, s32);
s32 GetSystemVm_250b60(void);
s32 MenuWinGet_2653e0(s32);
void EvSceneObjRemove_2690a0(s32);
void MenuWinFadeColorToInt_26c1c0(s32, s32, s32, s32, s32, s32);
void MenuWinSetBlendMode_26c270(s32, s32);
void MenuWinSetSize_26c320(s32, s32, s32);
void MenuWinSetColorInt_26c330(s32, s32, s32, s32, s32);
void MenuWinSetPosXyz_26c390(s32, f32, f32, f32);
void MenuWinSetDrawMode_26c3e0(s32, s32);
void MenuWinSetActive_26c3f0(s32, s32);
void MenuWinInit_26c450(s32);
void LetterboxSetFade_277ea0(void *, f32, f32, f32);
void LetterboxReset_278390(void *);
void CharaEffectGroupsSetPausedHiddenAll_27a260(s32, s32, s32);
void SystemScriptStart_27a540(s32, void *, s32);
void AbilityReqReset_27a610(void);
void TaskApplyPresetMaybe_27af70(s32);
s32 SysModeMsgIsKeyCapWarpStartMaybe_27bc40(void);
void SetFieldControlActive_27bd30(s32);
s32 AttackObjBaseCloneAndRegister_27bd90(ObjData *);
void TaskTableRestoreOrder_27bed0(void);
void TaskStatePushAll_27c220(void);
void TaskStatePopAll_27c250(void);
void TaskSetEnabled_27c2a0(s32, const char *);
void TaskSetUpdateTasksPaused_287dd0(s32);
St *GetStatusEffect_2d9010(void);
s32 GetEffectMgr_2d9040(void);
void EffectReleaseByKey_2e1260(s32, s32);
void EffectGroupSetHidden_2e2bd0(s32, s32, s32);
void EffectGroupSetPaused_2e2c80(s32, s32, s32);
void PartyAllySuggestCancel_2eea00(s32);
void GameSceneCBlurResetMode2Maybe_2f1da0(void);
void SceneScreenOverlayResetMaybe_2f1ea0(void);
void SceneScreenOverlayResetAllMaybe_2f1f00(void);
void CharaAbilityResReloadMaybe_2f3f10(s32, s32);
void CameraScenePopApplyFov_309f10(void);
void CameraSwitchTo2KeepView_309fa0(void);
void AttackObjBaseCtor_3181b0(ObjData *, s32, s32, s32, f32);
s32 EquipSlotGetAbilityCompositeId_3a0730(s32);
s32 EquipSlotGetRecId_3a0760(s32);
void CharaSysEventLogKeyAdd_3a33b0(s32, s32, s32);
void ExecInfoInitFromEquipSlot_3a7690(void *, s32, s32, s32);
Vp2D8 *CharaMgrPoolFindById_3a8c60(s32, s32);
Vp320 *ObjFindById_3bb3a0(s32, s32);
s32 PartyGetMemberId_3c2490(void *, s32);
Vp280 *ActorFindById_3eb870(Ctx *, s32);
f32 DataTableEntryGetParamFloat_3fc970(void *, s32);
void *DListGetHead_42ea60(s32);
void *DListGetNext_42eb30(void *);

extern u8 D_00471AA0[];
extern f32 D_0045B080[];
extern char D_0045F950[];
extern char D_0045F960[];
extern char D_0045F978[];
extern char D_0045F988[];
extern char D_0045F990[];
extern u8 D_004B2570[];
extern u8 D_004D7810[];
extern s32 D_004D7828[];
extern s32 D_004D7C70[];
extern s32 D_004D7C74[];
extern s32 D_004D7C78[];
extern char D_004D7C7C[];
extern Info D_004D7C8C;
extern s16 D_004D7C94[];
extern void *D_004D7CDC[];
extern s32 D_004D7D00[];
extern s32 D_0047E9B0;
extern s32 D_0047E9B4;
extern f32 D_0047E9C0;
extern f32 D_0047E9C4;
extern f32 D_0047E9C8;
extern f32 D_0047E9CC;
extern s32 D_00481A90;
extern u8 D_00482070;
extern u8 D_0048217C;
extern u8 D_0048218C;
extern s32 D_00482190;
}

class Vp280 {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual void vB4();
    virtual void vB8();
    virtual void vBC();
    virtual void vC0();
    virtual void vC4();
    virtual void vC8();
    virtual void vCC();
    virtual void vD0();
    virtual void vD4();
    virtual void vD8();
    virtual void vDC();
    virtual void vE0();
    virtual void vE4();
    virtual void vE8();
    virtual void vEC();
    virtual void vF0();
    virtual void vF4();
    virtual void vF8();
    virtual void vFC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual void v19C();
    virtual void v1A0();
    virtual void v1A4();
    virtual void v1A8();
    virtual void v1AC();
    virtual void v1B0();
    virtual void v1B4();
    virtual void v1B8();
    virtual void v1BC();
    virtual void v1C0();
    virtual void v1C4();
    virtual void v1C8();
    virtual void v1CC();
    virtual void v1D0();
    virtual void v1D4();
    virtual void v1D8();
    virtual void v1DC();
    virtual void v1E0();
    virtual void v1E4();
    virtual void v1E8();
    virtual void v1EC();
    virtual void v1F0();
    virtual void v1F4();
    virtual void v1F8();
    virtual void v1FC();
    virtual void v200();
    virtual void v204();
    virtual void v208();
    virtual void v20C();
    virtual void v210();
    virtual void v214();
    virtual void v218();
    virtual void v21C();
    virtual void v220();
    virtual void v224();
    virtual void v228();
    virtual void v22C();
    virtual void v230();
    virtual void v234();
    virtual void v238();
    virtual void v23C();
    virtual void v240();
    virtual void v244();
    virtual void v248();
    virtual void v24C();
    virtual void v250();
    virtual void v254();
    virtual void v258();
    virtual void v25C();
    virtual void v260();
    virtual void v264();
    virtual void v268();
    virtual void v26C();
    virtual void v270();
    virtual void v274();
    virtual void v278();
    virtual void v27C();
    virtual void f280(void *);
};

class Vp2D8 {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual void vB4();
    virtual void vB8();
    virtual void vBC();
    virtual void vC0();
    virtual void vC4();
    virtual void vC8();
    virtual void vCC();
    virtual void vD0();
    virtual void vD4();
    virtual void vD8();
    virtual void vDC();
    virtual void vE0();
    virtual void vE4();
    virtual void vE8();
    virtual void vEC();
    virtual void vF0();
    virtual void vF4();
    virtual void vF8();
    virtual void vFC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual void v19C();
    virtual void v1A0();
    virtual void v1A4();
    virtual void v1A8();
    virtual void v1AC();
    virtual void v1B0();
    virtual void v1B4();
    virtual void v1B8();
    virtual void v1BC();
    virtual void v1C0();
    virtual void v1C4();
    virtual void v1C8();
    virtual void v1CC();
    virtual void v1D0();
    virtual void v1D4();
    virtual void v1D8();
    virtual void v1DC();
    virtual void v1E0();
    virtual void v1E4();
    virtual void v1E8();
    virtual void v1EC();
    virtual void v1F0();
    virtual void v1F4();
    virtual void v1F8();
    virtual void v1FC();
    virtual void v200();
    virtual void v204();
    virtual void v208();
    virtual void v20C();
    virtual void v210();
    virtual void v214();
    virtual void v218();
    virtual void v21C();
    virtual void v220();
    virtual void v224();
    virtual void v228();
    virtual void v22C();
    virtual void v230();
    virtual void v234();
    virtual void v238();
    virtual void v23C();
    virtual void v240();
    virtual void v244();
    virtual void v248();
    virtual void v24C();
    virtual void v250();
    virtual void v254();
    virtual void v258();
    virtual void v25C();
    virtual void v260();
    virtual void v264();
    virtual void v268();
    virtual void v26C();
    virtual void v270();
    virtual void v274();
    virtual void v278();
    virtual void v27C();
    virtual void v280();
    virtual void v284();
    virtual void v288();
    virtual void v28C();
    virtual void v290();
    virtual void v294();
    virtual void v298();
    virtual void v29C();
    virtual void v2A0();
    virtual void v2A4();
    virtual void v2A8();
    virtual void v2AC();
    virtual void v2B0();
    virtual void v2B4();
    virtual void v2B8();
    virtual void v2BC();
    virtual void v2C0();
    virtual void v2C4();
    virtual void v2C8();
    virtual void v2CC();
    virtual void v2D0();
    virtual void v2D4();
    virtual void f2D8(s32);
};

class Vp320 {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual void vB4();
    virtual void vB8();
    virtual void vBC();
    virtual void vC0();
    virtual void vC4();
    virtual void vC8();
    virtual void vCC();
    virtual void vD0();
    virtual void vD4();
    virtual void vD8();
    virtual void vDC();
    virtual void vE0();
    virtual void vE4();
    virtual void vE8();
    virtual void vEC();
    virtual void vF0();
    virtual void vF4();
    virtual void vF8();
    virtual void vFC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual void v19C();
    virtual void v1A0();
    virtual void v1A4();
    virtual void v1A8();
    virtual void v1AC();
    virtual void v1B0();
    virtual void v1B4();
    virtual void v1B8();
    virtual void v1BC();
    virtual void v1C0();
    virtual void v1C4();
    virtual void v1C8();
    virtual void v1CC();
    virtual void v1D0();
    virtual void v1D4();
    virtual void v1D8();
    virtual void v1DC();
    virtual void v1E0();
    virtual void v1E4();
    virtual void v1E8();
    virtual void v1EC();
    virtual void v1F0();
    virtual void v1F4();
    virtual void v1F8();
    virtual void v1FC();
    virtual void v200();
    virtual void v204();
    virtual void v208();
    virtual void v20C();
    virtual void v210();
    virtual void v214();
    virtual void v218();
    virtual void v21C();
    virtual void v220();
    virtual void v224();
    virtual void v228();
    virtual void v22C();
    virtual void v230();
    virtual void v234();
    virtual void v238();
    virtual void v23C();
    virtual void v240();
    virtual void v244();
    virtual void v248();
    virtual void v24C();
    virtual void v250();
    virtual void v254();
    virtual void v258();
    virtual void v25C();
    virtual void v260();
    virtual void v264();
    virtual void v268();
    virtual void v26C();
    virtual void v270();
    virtual void v274();
    virtual void v278();
    virtual void v27C();
    virtual void v280();
    virtual void v284();
    virtual void v288();
    virtual void v28C();
    virtual void v290();
    virtual void v294();
    virtual void v298();
    virtual void v29C();
    virtual void v2A0();
    virtual void v2A4();
    virtual void v2A8();
    virtual void v2AC();
    virtual void v2B0();
    virtual void v2B4();
    virtual void v2B8();
    virtual void v2BC();
    virtual void v2C0();
    virtual void v2C4();
    virtual void v2C8();
    virtual void v2CC();
    virtual void v2D0();
    virtual void v2D4();
    virtual void v2D8();
    virtual void v2DC();
    virtual void v2E0();
    virtual void v2E4();
    virtual void v2E8();
    virtual void v2EC();
    virtual void v2F0();
    virtual void v2F4();
    virtual void v2F8();
    virtual void v2FC();
    virtual void v300();
    virtual void v304();
    virtual void v308();
    virtual void v30C();
    virtual void v310();
    virtual void v314();
    virtual void v318();
    virtual void v31C();
    virtual void f320();
};

static inline void CopyInfo(Info *d, Info *s) {
    *d = *s;
}

static inline s32 Part(s32 v, s32 k) {
    return (v >= 0 && v < 12) ? v * 4 + k : -1;
}

static inline void Wait(s32 w, s32 id) {
    if (ScriptVmHasLabel_1768f0(GetSystemVm_250b60(), id) != 0) {
        SystemVmCall_250a50(id, w);
        while (SystemVmUpdate_2509f0() != 1) {
        }
    }
}

extern "C" s32 AbilityModeRun_2790e0(s32 w) {
    s32 tmp;
    char buf[0x8C];
    Vec v310;
    Vec v300;
    Vec v2F0;
    Vec v2E0;
    char name[0x20];
    s32 sys;
    Ctx *ctx;
    Mgr *mgr;
    s32 snd;
    St *st;
    s32 dat;
    s32 i;
    s32 k;
    s32 v;
    bool ok;
    s32 id;
    s32 flags;
    s32 h;
    s32 x;
    s32 r;
    void *it;
    void *p;
    void *src;
    Chr *o;
    Ch *c;
    Pp *pp;
    Vp280 *pc;
    Vp2D8 *m;
    Vp320 *e;
    void *ev;
    Info *pi;

    sys = GetLoaderMgr_1f59d0();
    GetCharaResMgr_1fdb60();
    ctx = GetGameData_1fede0();
    GetMapMgr_201a90();
    mgr = GetActionMgr_1fdb50();
    snd = GetEffectMgr_2d9040();
    st = GetStatusEffect_2d9010();
    dat = D_004D7C74[0];
    GameReqQueueRemoveById_1f5a10(10);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
    case 0:
        GameReqQueueRemoveById_1f5a10(0x11);
        GameReqQueueRemoveById_1f5a10(0x14);
        GameReqQueueRemoveById_1f5a10(0x13);
        GameReqQueueRemoveById_1f5a10(8);
        GameReqQueueRemoveById_1f5a10(9);
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        TaskSetUpdateTasksPaused_287dd0(1);
        TaskSetEnabled_27c2a0(0, D_0045F950);
        PartyAllySuggestCancel_2eea00(D_004D7C70[0]);
        pc = ActorFindById_3eb870(ctx, D_004D7C70[0]);
        if (pc != 0) {
            if (D_004D7C78[0] != 0) {
                ExecInfoInitFromEquipSlot_3a7690(&D_004D7C8C, D_004D7C70[0], EquipSlotGetRecId_3a0760(D_004D7C78[0]), 0);
                pc->f280(&D_004D7C8C);
            }
        }
        TaskApplyPresetMaybe_27af70(3);
        SetFieldControlActive_27bd30(0);
        StreamPauseChan_1cd9f0(sys, 1);
        StreamStopChan_1cda60(sys, 1);
        Sprintf_1343b8(buf, D_0045F960, D_004D7C7C);
        D_0047E9B4 = LoaderRequestFile_1cd870(sys, buf, 0);
        FieldHudAllySuggestHide_203ca0();
        FieldHudFadeOut_204080();
        SetGameModePhase_1f59a0(1);
        GameSceneSoundSlot1PlaySeVol_1d05e0(w, 0x51, 1.0f);
        D_0048217C = 0xFF;
        LetterboxReset_278390(D_004D7810);
        D_004D7828[0] = 0;
        if (SysModeMsgIsKeyCapWarpStartMaybe_27bc40() == 0) {
            LetterboxSetFade_277ea0(D_004D7810, 1.0f, 10.0f, 0.0f);
        }
        SceneScreenOverlayResetAllMaybe_2f1f00();
        D_00482190 = 0;
        it = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(mgr));
        while (it != 0) {
            o = (Chr *)((u8 *)it + 0x10);
            it = DListGetNext_42eb30(it);
            if (o->fA44 & 0x80000) continue;
            D_004D7D00[D_00482190++] = CharaGetId_214a80(o);
            CharaGetPos_2388a0(o, &v310);
            CharaGetRot_2388b0(o, &v300);
            CharaSetSavedPos_2142e0(o, &v310);
            CharaSetSavedRot_214290(o, &v300);
        }
        EffectGroupSetPaused_2e2c80(snd, 1000, 1);
        EffectGroupSetHidden_2e2bd0(snd, 1000, 1);
        EffectGroupSetPaused_2e2c80(snd, 2000, 1);
        EffectGroupSetHidden_2e2bd0(snd, 2000, 1);
        ActionMgrSaveMotionAll_2315e0(mgr);
        v = D_004D7C94[0];
        if (!(v < 0x80) && v < 0x9C) {
            o = ActionMgrFindById_233b50(mgr, v);
            if (o != 0) o->fA44 |= 0x4000000;
        }
        st->f8 = 0;
        D_0048218C = 0;
        D_00482070 = 0;
        break;
    case 1:
        if (LoaderGetStatus_1cd4f0(sys, D_0047E9B4) == -1) {
            LoaderReleaseById_1cd340(sys, D_0047E9B4);
            CharaAbilityResReloadMaybe_2f3f10(dat, D_004D7C78[0]);
            SetGameModePhase_1f59a0(100);
        } else if (LoaderGetStatus_1cd4f0(sys, D_0047E9B4) == 1) {
        ObjRecClearFlags_1c3dc0(w, 1, dat, 0x2000);
        D_0047E9B0 = RecStackPush_1c4240(w, D_0045F978);
        x = RecStackGetSlot_1c4330(w, D_0047E9B0);
        src = LoaderGetData_1cd490(sys, D_0047E9B4, &tmp);
        p = MemStackAllocAligned64_14da10(x, 0x1900);
        memcpy(p, src, 0x19000);
        LoaderReleaseById_1cd340(sys, D_0047E9B4);
        SystemScriptStart_27a540(w, p, 100);
        TaskApplyPresetMaybe_27af70(3);
        CameraSwitchTo2KeepView_309fa0();
        SetGameModePhase_1f59a0(2);
        r = MapSlotsFindBlockById_1e49b0(GetMapMgr_201a90(), ctx->f18->f30, 0);
        if (r == 0) break;
        if (MapDataIsNoDarken_1e7aa0(r) != 0) break;
        x = MenuWinGet_2653e0(7);
        MenuWinInit_26c450(x);
        MenuWinSetDrawMode_26c3e0(x, 0);
        MenuWinSetBlendMode_26c270(x, 1);
        MenuWinSetPosXyz_26c390(x, 256.0f, 224.0f, 0.0f);
        MenuWinSetSize_26c320(x, 0x200, 0x1C0);
        MenuWinSetActive_26c3f0(x, 1);
        MenuWinSetColorInt_26c330(x, 0, 0, 0, 0);
        MenuWinFadeColorToInt_26c1c0(x, 0, 0, 0, 0x40, 10);
        }
        break;
    case 2:
        ok = false;
        v = D_004D7C70[0];
        if (v >= 0 && v < 12 && D_0048218C != 0 && EquipSlotGetAbilityCompositeId_3a0730(D_004D7C78[0]) != 0x1776 && LoaderCountQueued_1cd620(sys) <= 0) {
            D_00482070 = 1;
            if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
                ok = true;
                PadUpdate_1843a0(D_004B2570);
                PadUpdateVibration_184250(D_004B2570, 0);
            }
        }
        if (!ok) {
            if (SystemVmUpdate_2509f0() != 1) return 0;
        }
        if (LoaderCountQueued_1cd620(sys) > 0) return 0;
        D_0048218C = 0;
        D_00482070 = 0;
        if (ok) {
            StreamPauseChan_1cd9f0(sys, 1);
            StreamStopChan_1cda60(sys, 1);
            StreamPauseChan_1cd9f0(sys, 2);
            StreamStopChan_1cda60(sys, 2);
        }
        for (i = 0; i < 12; i++) {
            c = ObjRecGetLiveObject_1c4a90(w, i);
            if (c == 0) continue;
            c->f54(0x46);
            pp = ModelGetRootFrame_1511a0(c);
            if (pp != 0 && pp->f28 != 0) pp->f4 = 0;
        }
        for (i = 0; i < 0x30; i++) {
            c = ObjRecGetLiveObject_1c4a90(w, i + 12);
            if (c != 0) c->f54(0x46);
        }
        for (i = 0; i < 0x40; i++) {
            EvSceneObjRemove_2690a0(i + 0x40);
        }
        Wait(w, 3000);
        Wait(w, 2000);
        for (k = 0; k < D_00482190; k++) {
            id = D_004D7D00[k];
            o = ActionMgrFindById_233b50(mgr, id);
            if (o != 0) {
                CharaGetSavedPos_214300(o, &v2F0);
                CharaGetSavedRot_2142b0(o, &v2E0);
                CharaSetPos_213a40(o, &v2F0);
                CharaSetYaw_2138f0(o, v2E0.y);
                c = ObjRecGetLiveObject_1c4a90(w, id);
                if (c != 0) {
                    ModelSetPos_151110(c, &v2F0);
                    ModelSetRot_151080(c, &v2E0);
                }
            }
            ObjRecSetFlag2_1c3e80(w, 1, PartyGetMemberId_3c2490(ctx->f18, k));
        }
        Wait(w, 4000);
        LoaderPurgeAll_1cd240(sys);
        CameraScenePopApplyFov_309f10();
        RecStackPop_1c4140(w, D_0047E9B0);
        SetGameModePhase_1f59a0(100);
    case 100:
        if (LoaderCountQueued_1cd620(sys) > 0) return 1;
        m = CharaMgrPoolFindById_3a8c60(ctx->f14, D_004D7C70[0]);
        if (m != 0) {
            m->f2D8(EquipSlotGetRecId_3a0760(D_004D7C78[0]));
        }
        for (i = 0; i < 0xE0; i++) {
            c = ObjRecGetLiveObject_1c4a90(w, i);
            if (c != 0) {
                c->f464 = 0x1F;
                c->f468 = 0;
            }
        }
        for (flags = 0x80; flags <= 0x9B; flags++) {
            o = ActionMgrFindById_233b50(mgr, flags);
            if (o == 0) continue;
            if (o->fA44 & 0x80000) continue;
            if (CharaGetActionMode_213850(o) == -1 || CharaGetActionMode_213850(o) == 0x12) {
                o->fA44 |= 0x40000000;
                CharaResetBattleStateMaybe_212f20(o, 0);
                CharaSetInvincibleTime_2138a0(o, 0.0f);
                e = ObjFindById_3bb3a0(ctx->f1C, flags);
                if (e != 0) e->f320();
            }
        }
        LetterboxSetFade_277ea0(D_004D7810, 0.0f, 10.0f, 0.0f);
        ObjRecSetFlags_1c3e00(w, 1, dat, 0x2000);
        StreamPauseChan_1cd9f0(sys, 1);
        StreamStopChan_1cda60(sys, 1);
        SetGameModePhase_1f59a0(0x65);
        SceneScreenOverlayResetMaybe_2f1ea0();
        ClearGameReqHold_1f5880();
        GameSceneCBlurResetMode2Maybe_2f1da0();
        return 1;
    case 101:
        if (GameReqQueuePeekHead_1f5a70(0) != -1) return 0;
        v = D_004D7C94[0];
        o = ActionMgrFindById_233b50(mgr, v);
        if (o != 0) {
            o->fA44 &= ~0x4000000;
            if (v >= 0 && v < 12) {
                if (CharaGetBaseActionMode_213830(o) == 2) {
                    strcpy(name, D_0045F988);
                } else {
                    strcpy(name, D_0045F990);
                }
                CharaResetBattleStateMaybe_212f20(o, 0);
                CharaPlayMotion_212590(o, ObjRecGetLiveObject_1c4a90(w, v), name, 0, 1.0f);
                {
                    s32 ids[5] = {v, Part(v, 12), Part(v, 13), Part(v, 14), Part(v, 15)};

                    for (i = 0; i < 5; i++) {
                        c = ObjRecGetLiveObject_1c4a90(w, ids[i]);
                        if (c != 0) {
                            c->f464 = 0x1F;
                            c->f468 = 1;
                            c->f44(1.0f);
                        }
                    }
                }
            }
        }
        ev = D_004D7CDC[0];
        if (ev != 0) {
            h = -1;
            switch (*(s32 *)((u8 *)ev + 8)) {
            case 1:
                o = ActionMgrFindById_233b50(mgr, D_004D7C94[0]);
                if (o != 0) {
                    ObjData obj;
                    Vec col;
                    Mat mat;
                    Vec vA0;
                    Vec v90;

                    flags = 0x8001;
                    if (EquipSlotGetAbilityCompositeId_3a0730(D_004D7C78[0]) != 0x1391) flags |= 0x1000;
                    AttackObjBaseCtor_3181b0(&obj, 1, D_004D7C94[0], flags, DataTableEntryGetParamFloat_3fc970(ev, 2));
                    col.x = D_0047E9C0;
                    col.y = D_0047E9C4;
                    col.z = D_0047E9C8;
                    col.w = D_0047E9CC;
                    col.x = DataTableEntryGetParamFloat_3fc970(ev, 3);
                    col.y = DataTableEntryGetParamFloat_3fc970(ev, 4);
                    col.z = DataTableEntryGetParamFloat_3fc970(ev, 5);
                    CharaGetPos_2388a0(o, &vA0);
                    CharaGetRot_2388b0(o, &v90);
                    MatFromRotPos_1caf90(&mat, &v90, &vA0);
                    MatMulPoint_1cb8e0(&vA0, &mat, &col);
                    ((Obj *)&obj)->f54(vA0.x, vA0.y, vA0.z);
                    obj.fC8 = 5.0f;
                    D_00481A90 = 50;
                    obj.f190 = 1000.0f * D_0045B080[0];
                    pi = (Info *)(u32)(&obj.info);
                    *pi = D_004D7C8C;
                    h = AttackObjBaseCloneAndRegister_27bd90(&obj);
                    obj.vt = D_00471AA0;
                }
                break;
            }
            if (h >= 0) {
                CharaSysEventLogKeyAdd_3a33b0(ctx->f20, h, 0);
                FieldHudLogOpen_203fb0();
            }
        }
        if (D_004D7C78[0] != 0) {
            switch (EquipSlotGetAbilityCompositeId_3a0730(D_004D7C78[0])) {
            case 0x1F43:
            case 0xBBC:
            case 0xFA4:
            case 0x1F41:
            case 0x1771:
            case 0x1B59:
            case 0x7D1:
            case 0x7D4:
            case 0x1773:
            case 0x138D:
            case 0x1389:
                GameSceneSoundSlot0PlaySeVol_1d05f0(w, 0x2F, 1.0f);
                break;
            case 0xBB9:
            case 0xBBF:
                EffectReleaseByKey_2e1260(GetEffectMgr_2d9040(), 2);
                break;
            }
        }
        if (D_004D7C94[0] == 7) {
            if (EquipSlotGetAbilityCompositeId_3a0730(D_004D7C78[0]) != 0x1F45) {
                ObjRecSetFlags_1c3e00(w, 1, 0x29, 0x10);
            } else {
                ObjRecClearFlags_1c3dc0(w, 1, 0x29, 0x10);
            }
        }
        AbilityReqReset_27a610();
        TaskTableRestoreOrder_27bed0();
        CharaEffectGroupsSetPausedHiddenAll_27a260(0, 0, -1);
        EffectGroupSetPaused_2e2c80(snd, 1000, 0);
        EffectGroupSetHidden_2e2bd0(snd, 1000, 0);
        EffectGroupSetPaused_2e2c80(snd, 2000, 0);
        EffectGroupSetHidden_2e2bd0(snd, 2000, 0);
        st->f8 = 1;
        FieldHudFadeIn_203ee0();
        mgr->f38 &= ~0x10000000;
        ActionMgrRestoreSavedMotionAll_231590(mgr);
        FieldHudAllySuggestShow_203c90();
        GameReqQueuePushBack_1f5b50(0, -1);
        TaskStatePopAll_27c250();
        ClearGameReqHold_1f5880();
        return 1;
    }
    return 0;
}
