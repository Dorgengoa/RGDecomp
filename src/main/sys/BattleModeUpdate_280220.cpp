#pragma opt_loop_invariants off
#pragma opt_dead_assignments off
#include "types.h"

typedef unsigned __int128 u128;

typedef struct Vec {
    f32 x, y, z, w;
} __attribute__((aligned(16))) Vec;

typedef struct Mat {
    Vec a, b, c, d;
} Mat;

struct Flag7E {
    s8 on : 1;
};

struct Info {
    u8 pad0[0x18];
    s16 f18;
    s16 f1A;
    u8 pad1C[4];
    f32 f20;
    u8 pad24[8];
    s8 f2C;
    u8 pad2D[0x51];
    Flag7E f7E;
};

struct Mission {
    u64 f0;
    u8 pad8[0x10];
    Info *f18;
    u8 pad1C[0x146];
    s16 f162;
    u8 pad164[4];
    s16 f168;
};

struct Game {
    u8 pad0[0x238];
    Mission *f238;
    u8 pad23C[0x10];
    u8 f24C;
};

struct Party {
    u8 pad0[0xC];
    s16 fC;
    u8 padE[2];
    s32 f10;
    u8 pad14[0x17A];
    s16 f18E;
};

struct Cfg {
    u8 pad0[0x1A];
    s16 f1A;
    u8 pad1C[6];
    s16 f22;
};

struct SiteInfo {
    u8 pad0[4];
    s8 lo : 4;
    s8 hi : 4;
};

struct Page {
    u8 pad0[4];
    s16 f4;
};

struct Ctx {
    u8 pad0[8];
    struct {
        u8 pad0[0x38];
        struct {
            u8 pad0[8];
            struct Book *f8;
        } *f38;
    } *f8;
    Cfg *fC;
    s32 f10;
    s32 f14;
    Party *f18;
    s32 f1C;
    Game *f20;
};

struct World {
    u8 pad0[0x4344];
    s32 f4344;
};

struct Chr {
    u8 pad0[0x3D0];
    u64 f3D0;
    s32 f3D8;
    u8 pad3DC[0x668];
    s32 fA44;
};

struct Node {
    u8 pad0[0x10];
};

struct Dlg {
    u8 pad0[0x30];
};

struct Con {
    u8 pad0[0xC];
    s32 fC;
};

struct CamBase {
    u8 pad[0xC0];
};

class Cam : public CamBase {
public:
    virtual void d8();
    virtual void dC();
    virtual void d10();
    virtual void d14();
    virtual void d18();
    virtual void d1C();
    virtual void d20();
    virtual void d24();
    virtual void d28();
    virtual void d2C();
    virtual void d30();
    virtual void d34();
    virtual void d38();
    virtual void d3C();
    virtual void d40();
    virtual void d44();
    virtual void d48();
    virtual void d4C();
    virtual void d50();
    virtual void d54();
    virtual void d58();
    virtual void d5C();
    virtual void d60();
    virtual void d64();
    virtual void SetZoom(f32);
    virtual void d6C();
    virtual void d70();
    virtual void d74();
    virtual void d78();
    virtual void d7C();
    virtual void d80();
    virtual void d84();
    virtual void d88();
    virtual void d8C();
    virtual void d90();
    virtual void d94();
    virtual void d98();
    virtual void d9C();
    virtual void dA0();
    virtual void GetPos(Vec *);
    virtual void GetAt(Vec *);
    virtual void dAC();
    virtual void SetPos(Vec *);
    virtual void dB4();
    virtual void dB8();
    virtual void dBC();
    virtual void dC0();
    virtual void dC4();
    virtual void SetMode(f32);
};
class Ally {
public:
    virtual void d8();
    virtual void dC();
    virtual void d10();
    virtual void d14();
    virtual void d18();
    virtual void d1C();
    virtual void d20();
    virtual void d24();
    virtual void d28();
    virtual void d2C();
    virtual void d30();
    virtual void d34();
    virtual void d38();
    virtual void d3C();
    virtual void d40();
    virtual void d44();
    virtual void d48();
    virtual void d4C();
    virtual void d50();
    virtual void d54();
    virtual void d58();
    virtual void d5C();
    virtual void d60();
    virtual void d64();
    virtual void d68();
    virtual void d6C();
    virtual void d70();
    virtual void d74();
    virtual void d78();
    virtual void d7C();
    virtual void d80();
    virtual void d84();
    virtual void d88();
    virtual void d8C();
    virtual void d90();
    virtual void d94();
    virtual void d98();
    virtual void d9C();
    virtual void dA0();
    virtual void dA4();
    virtual void dA8();
    virtual void dAC();
    virtual void dB0();
    virtual void dB4();
    virtual void dB8();
    virtual void dBC();
    virtual s32 Busy();
    virtual void dC4();
    virtual void dC8();
    virtual void dCC();
    virtual void dD0();
    virtual void dD4();
    virtual void dD8();
    virtual void dDC();
    virtual void dE0();
    virtual void dE4();
    virtual void dE8();
    virtual void dEC();
    virtual void dF0();
    virtual void dF4();
    virtual void dF8();
    virtual void dFC();
    virtual void d100();
    virtual void d104();
    virtual void d108();
    virtual void d10C();
    virtual void d110();
    virtual void d114();
    virtual void d118();
    virtual void d11C();
    virtual void d120();
    virtual void d124();
    virtual void d128();
    virtual void d12C();
    virtual void d130();
    virtual void d134();
    virtual void d138();
    virtual void d13C();
    virtual void d140();
    virtual void d144();
    virtual void d148();
    virtual void d14C();
    virtual void d150();
    virtual void d154();
    virtual void d158();
    virtual void d15C();
    virtual void d160();
    virtual void d164();
    virtual void d168();
    virtual void d16C();
    virtual void d170();
    virtual void d174();
    virtual void d178();
    virtual void d17C();
    virtual void d180();
    virtual void d184();
    virtual void d188();
    virtual void d18C();
    virtual void d190();
    virtual void d194();
    virtual void d198();
    virtual void d19C();
    virtual void d1A0();
    virtual void d1A4();
    virtual void d1A8();
    virtual void d1AC();
    virtual void d1B0();
    virtual void d1B4();
    virtual void d1B8();
    virtual void d1BC();
    virtual void d1C0();
    virtual void d1C4();
    virtual void d1C8();
    virtual void d1CC();
    virtual void d1D0();
    virtual void d1D4();
    virtual void d1D8();
    virtual void d1DC();
    virtual void d1E0();
    virtual void d1E4();
    virtual void d1E8();
    virtual void d1EC();
    virtual void d1F0();
    virtual void d1F4();
    virtual void d1F8();
    virtual void d1FC();
    virtual void d200();
    virtual void d204();
    virtual void d208();
    virtual void d20C();
    virtual void d210();
    virtual void d214();
    virtual void d218();
    virtual void d21C();
    virtual void d220();
    virtual void d224();
    virtual void d228();
    virtual s32 Ready();
};
class Unit {
public:
    virtual void d8();
    virtual void dC();
    virtual void d10();
    virtual void d14();
    virtual void d18();
    virtual void d1C();
    virtual void d20();
    virtual void d24();
    virtual void d28();
    virtual void d2C();
    virtual void d30();
    virtual void d34();
    virtual void d38();
    virtual void d3C();
    virtual void d40();
    virtual void d44();
    virtual void d48();
    virtual void d4C();
    virtual void d50();
    virtual void d54();
    virtual void d58();
    virtual void d5C();
    virtual void d60();
    virtual void d64();
    virtual void d68();
    virtual void d6C();
    virtual void d70();
    virtual void d74();
    virtual void d78();
    virtual void d7C();
    virtual void d80();
    virtual void d84();
    virtual void d88();
    virtual void d8C();
    virtual void d90();
    virtual void d94();
    virtual void d98();
    virtual void d9C();
    virtual void dA0();
    virtual void dA4();
    virtual void dA8();
    virtual void dAC();
    virtual void dB0();
    virtual void dB4();
    virtual void dB8();
    virtual void dBC();
    virtual void dC0();
    virtual void dC4();
    virtual void dC8();
    virtual void dCC();
    virtual void dD0();
    virtual void dD4();
    virtual void dD8();
    virtual void dDC();
    virtual void dE0();
    virtual void dE4();
    virtual void dE8();
    virtual void dEC();
    virtual void dF0();
    virtual void dF4();
    virtual void dF8();
    virtual void dFC();
    virtual void d100();
    virtual void d104();
    virtual void d108();
    virtual void d10C();
    virtual void d110();
    virtual void d114();
    virtual void d118();
    virtual void d11C();
    virtual void d120();
    virtual void d124();
    virtual void d128();
    virtual void d12C();
    virtual void d130();
    virtual void d134();
    virtual void d138();
    virtual void d13C();
    virtual void d140();
    virtual void d144();
    virtual void d148();
    virtual void d14C();
    virtual void d150();
    virtual void d154();
    virtual void d158();
    virtual void d15C();
    virtual void d160();
    virtual void d164();
    virtual void d168();
    virtual void d16C();
    virtual void d170();
    virtual void d174();
    virtual void d178();
    virtual void d17C();
    virtual void d180();
    virtual void d184();
    virtual void d188();
    virtual void d18C();
    virtual void d190();
    virtual void d194();
    virtual void d198();
    virtual void d19C();
    virtual void d1A0();
    virtual void d1A4();
    virtual void d1A8();
    virtual void d1AC();
    virtual void d1B0();
    virtual void d1B4();
    virtual void d1B8();
    virtual void d1BC();
    virtual void d1C0();
    virtual void d1C4();
    virtual void d1C8();
    virtual void d1CC();
    virtual void d1D0();
    virtual void d1D4();
    virtual void d1D8();
    virtual void d1DC();
    virtual void d1E0();
    virtual void d1E4();
    virtual void d1E8();
    virtual void d1EC();
    virtual void d1F0();
    virtual void d1F4();
    virtual void d1F8();
    virtual void d1FC();
    virtual void d200();
    virtual void d204();
    virtual void d208();
    virtual void d20C();
    virtual void d210();
    virtual void d214();
    virtual void d218();
    virtual void d21C();
    virtual void d220();
    virtual void d224();
    virtual void d228();
    virtual void d22C();
    virtual void d230();
    virtual void d234();
    virtual void d238();
    virtual void d23C();
    virtual void d240();
    virtual void d244();
    virtual void d248();
    virtual void d24C();
    virtual void d250();
    virtual void d254();
    virtual void d258();
    virtual void d25C();
    virtual void d260();
    virtual void d264();
    virtual void d268();
    virtual void d26C();
    virtual void d270();
    virtual void d274();
    virtual void d278();
    virtual void d27C();
    virtual void d280();
    virtual void d284();
    virtual void d288();
    virtual void d28C();
    virtual void d290();
    virtual void d294();
    virtual void d298();
    virtual void d29C();
    virtual void d2A0();
    virtual void d2A4();
    virtual void d2A8();
    virtual void d2AC();
    virtual void d2B0();
    virtual void d2B4();
    virtual void d2B8();
    virtual void d2BC();
    virtual void d2C0();
    virtual void d2C4();
    virtual void d2C8();
    virtual void d2CC();
    virtual void d2D0();
    virtual void d2D4();
    virtual void d2D8();
    virtual void d2DC();
    virtual void d2E0();
    virtual void d2E4();
    virtual void d2E8();
    virtual void d2EC();
    virtual void d2F0();
    virtual void d2F4();
    virtual void d2F8();
    virtual void d2FC();
    virtual void d300();
    virtual void d304();
    virtual void d308();
    virtual void d30C();
    virtual void d310();
    virtual void d314();
    virtual void d318();
    virtual void d31C();
    virtual void d320();
    virtual void d324();
    virtual void d328();
    virtual void d32C();
    virtual void d330();
    virtual void d334();
    virtual void d338();
    virtual void d33C();
    virtual void d340();
    virtual void d344();
    virtual void d348();
    virtual void d34C();
    virtual void d350();
    virtual void d354();
    virtual void d358();
    virtual void d35C();
    virtual void d360();
    virtual void d364();
    virtual void d368();
    virtual void d36C();
    virtual void d370();
    virtual void d374();
    virtual void d378();
    virtual void d37C();
    virtual void d380();
    virtual void d384();
    virtual void d388();
    virtual void d38C();
    virtual void d390();
    virtual void d394();
    virtual void d398();
    virtual void d39C();
    virtual void d3A0();
    virtual void d3A4();
    virtual void d3A8();
    virtual void d3AC();
    virtual void d3B0();
    virtual void d3B4();
    virtual void d3B8();
    virtual void d3BC();
    virtual void d3C0();
    virtual void d3C4();
    virtual void d3C8();
    virtual void d3CC();
    virtual void d3D0();
    virtual void d3D4();
    virtual void d3D8();
    virtual void d3DC();
    virtual void d3E0();
    virtual void d3E4();
    virtual void d3E8();
    virtual void d3EC();
    virtual void d3F0();
    virtual void d3F4();
    virtual void d3F8();
    virtual void d3FC();
    virtual void d400();
    virtual void d404();
    virtual void d408();
    virtual void d40C();
    virtual void d410();
    virtual void d414();
    virtual void d418();
    virtual void d41C();
    virtual void d420();
    virtual void d424();
    virtual void d428();
    virtual void d42C();
    virtual void d430();
    virtual void d434();
    virtual void d438();
    virtual void d43C();
    virtual void d440();
    virtual void d444();
    virtual void d448();
    virtual void d44C();
    virtual void d450();
    virtual void d454();
    virtual void d458();
    virtual void d45C();
    virtual void d460();
    virtual void d464();
    virtual void d468();
    virtual void d46C();
    virtual void d470();
    virtual void d474();
    virtual void d478();
    virtual void d47C();
    virtual void d480();
    virtual void d484();
    virtual void d488();
    virtual void d48C();
    virtual void d490();
    virtual void d494();
    virtual void d498();
    virtual void d49C();
    virtual void d4A0();
    virtual void d4A4();
    virtual void d4A8();
    virtual void d4AC();
    virtual void d4B0();
    virtual void d4B4();
    virtual void d4B8();
    virtual void d4BC();
    virtual void d4C0();
    virtual s32 Kind();
};
class Site {
public:
    virtual void d8();
    virtual void dC();
    virtual void d10();
    virtual void d14();
    virtual void d18();
    virtual void d1C();
    virtual void d20();
    virtual void d24();
    virtual void d28();
    virtual void d2C();
    virtual void d30();
    virtual void d34();
    virtual void d38();
    virtual void d3C();
    virtual void d40();
    virtual void d44();
    virtual void d48();
    virtual void d4C();
    virtual void d50();
    virtual void d54();
    virtual void d58();
    virtual void d5C();
    virtual void d60();
    virtual void d64();
    virtual void d68();
    virtual void d6C();
    virtual void d70();
    virtual void d74();
    virtual void d78();
    virtual void d7C();
    virtual void d80();
    virtual void d84();
    virtual void d88();
    virtual void d8C();
    virtual void d90();
    virtual void d94();
    virtual void d98();
    virtual void d9C();
    virtual void dA0();
    virtual void dA4();
    virtual void dA8();
    virtual void dAC();
    virtual void dB0();
    virtual void dB4();
    virtual void dB8();
    virtual void dBC();
    virtual void dC0();
    virtual void dC4();
    virtual void dC8();
    virtual void dCC();
    virtual void dD0();
    virtual void dD4();
    virtual void dD8();
    virtual void dDC();
    virtual void dE0();
    virtual void dE4();
    virtual void dE8();
    virtual void dEC();
    virtual void dF0();
    virtual void dF4();
    virtual void dF8();
    virtual void dFC();
    virtual void d100();
    virtual void d104();
    virtual void d108();
    virtual void d10C();
    virtual void d110();
    virtual void d114();
    virtual void d118();
    virtual void d11C();
    virtual void d120();
    virtual void d124();
    virtual void d128();
    virtual void d12C();
    virtual void d130();
    virtual void d134();
    virtual void d138();
    virtual void d13C();
    virtual void d140();
    virtual void d144();
    virtual void d148();
    virtual void d14C();
    virtual void d150();
    virtual void d154();
    virtual void d158();
    virtual void d15C();
    virtual void d160();
    virtual void d164();
    virtual void d168();
    virtual void d16C();
    virtual void d170();
    virtual void d174();
    virtual void d178();
    virtual void d17C();
    virtual void d180();
    virtual void d184();
    virtual void d188();
    virtual void d18C();
    virtual void d190();
    virtual void d194();
    virtual void d198();
    virtual void d19C();
    virtual void d1A0();
    virtual void d1A4();
    virtual void d1A8();
    virtual void d1AC();
    virtual void d1B0();
    virtual void d1B4();
    virtual void d1B8();
    virtual void d1BC();
    virtual void d1C0();
    virtual void d1C4();
    virtual void d1C8();
    virtual void d1CC();
    virtual void d1D0();
    virtual void d1D4();
    virtual void d1D8();
    virtual void d1DC();
    virtual void d1E0();
    virtual void d1E4();
    virtual void d1E8();
    virtual void d1EC();
    virtual void d1F0();
    virtual void d1F4();
    virtual void d1F8();
    virtual void d1FC();
    virtual void d200();
    virtual void d204();
    virtual void d208();
    virtual void d20C();
    virtual void d210();
    virtual void d214();
    virtual void d218();
    virtual void d21C();
    virtual void d220();
    virtual void d224();
    virtual void d228();
    virtual void d22C();
    virtual void d230();
    virtual void d234();
    virtual void d238();
    virtual void d23C();
    virtual void d240();
    virtual void d244();
    virtual void d248();
    virtual void d24C();
    virtual void d250();
    virtual void d254();
    virtual void d258();
    virtual void d25C();
    virtual void d260();
    virtual void d264();
    virtual void d268();
    virtual void d26C();
    virtual void d270();
    virtual void d274();
    virtual void d278();
    virtual void d27C();
    virtual void d280();
    virtual void d284();
    virtual void d288();
    virtual void d28C();
    virtual void d290();
    virtual void d294();
    virtual void d298();
    virtual void d29C();
    virtual void d2A0();
    virtual void d2A4();
    virtual void d2A8();
    virtual void d2AC();
    virtual void d2B0();
    virtual void d2B4();
    virtual void d2B8();
    virtual void d2BC();
    virtual void d2C0();
    virtual void d2C4();
    virtual void d2C8();
    virtual void d2CC();
    virtual void d2D0();
    virtual void d2D4();
    virtual void d2D8();
    virtual void d2DC();
    virtual void d2E0();
    virtual void d2E4();
    virtual void d2E8();
    virtual void d2EC();
    virtual void d2F0();
    virtual void d2F4();
    virtual void d2F8();
    virtual void d2FC();
    virtual void d300();
    virtual void d304();
    virtual void d308();
    virtual void d30C();
    virtual void d310();
    virtual void d314();
    virtual void d318();
    virtual void d31C();
    virtual void d320();
    virtual void d324();
    virtual void d328();
    virtual void d32C();
    virtual void d330();
    virtual void d334();
    virtual void d338();
    virtual void d33C();
    virtual void d340();
    virtual void d344();
    virtual void d348();
    virtual void d34C();
    virtual void d350();
    virtual struct SiteInfo *Info();
};
class Book {
public:
    virtual void d8();
    virtual void dC();
    virtual void d10();
    virtual void d14();
    virtual void d18();
    virtual void d1C();
    virtual void d20();
    virtual void d24();
    virtual void d28();
    virtual void d2C();
    virtual void d30();
    virtual void d34();
    virtual void d38();
    virtual void d3C();
    virtual void d40();
    virtual void d44();
    virtual void d48();
    virtual void d4C();
    virtual void d50();
    virtual void d54();
    virtual void d58();
    virtual void d5C();
    virtual void d60();
    virtual void d64();
    virtual void d68();
    virtual void d6C();
    virtual struct Page *Find(s16);
};

extern "C" {
f32 Atan2f_1291a8(f32, f32);
void Abort_12de80(void);
void Fprintf_12f9a0(s32, const char *);
s32 PadIsTriggered_1839f0(void *, s32);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
void SoundBankStopAll_1bad70(s32);
Cam *ObjRecGetLiveObject_1c3bc0(World *, s32);
s32 ObjRecGetFlags_1c3d90(World *, s32, s32);
f32 RandRangeFloat_1ca5d0(f32);
void MatFromRotPos_1caf90(Mat *, Vec *, Vec *);
f32 VecDistSqXZ_1cb390(Vec *, Vec *);
f32 VecLengthSqXZ_1cb450(Vec *);
void VecScaleToLength_1cb510(Vec *, Vec *, f32);
void MatMulPoint_1cb8e0(Vec *, Mat *, Vec *);
void VecScale_1cbca0(Vec *, Vec *, f32);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
void VecAdd_1cbdc0(Vec *, Vec *, Vec *);
void VecCopy_1cbe30(Vec *, Vec *);
void StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);
void StreamPauseChan_1cd9f0(s32, s32);
void StreamStopChan_1cda60(s32, s32);
void GameSceneSetTimeScaleLockedMaybe_1ceb90(World *, s32);
f32 GameSceneGetTimeStep_1ceba0(World *);
void ScreenFadeCaptureFrame_1cf550(World *);
void ScreenFadeDissolveIn_1cf720(World *, s32, f32);
void ScreenFadeReset_1cf760(World *);
void ParamTableFadeToZero_1cf9d0(World *, s32, s32);
void GameSceneSoundFadeOut_1d0340(World *, s32);
void GameSceneSoundSlot0PlaySeVol_1d05f0(World *, s32, f32);
s32 GameSceneSoundSlot5GetHandle_1d0790(World *);
s32 MapSlotsFindById_1e4b90(s32, s32, s32);
s32 MapMgrGetCaption_1e56c0(s32);
s32 MapDataIsBattleForceWarp_1e7a10(s32);
void CharaDataReleaseId12_1f00b0(s32, World *);
void CharaResLoadListMaybe_1f02d0(s32, World *, s32 *, s32);
void ClearGameReqHold_1f5880(void);
void SetGameReqHold_1f5890(void);
void SetGameModePhase_1f59a0(s32);
s32 GetGameModePhase_1f59b0(void);
s32 GetLoaderMgr_1f59d0(void);
void GameReqQueueRemoveById_1f5a10(s32);
s32 GameReqQueuePeekWarp_1f5a40(s16 *);
s32 GameReqQueuePeekHead_1f5a70(s32);
void GameReqQueuePushFront_1f5ab0(s32, s32);
void GameReqQueuePushBack_1f5b50(s32, s32);
s32 GameReqQueueContainsId_1f5b90(s32);
World *GetCurrentScene_1f5be0(void);
void CameraSnapReqEye_1f6d60(s32);
void CameraSnapReqAt_1f6d70(s32);
void FieldReqHookStubRelated_1f9750(void);
void ScatterCharasOnGroundMaybe_1fbe70(Vec *, Vec *);
void *GetActionMgr_1fdb50(void);
s32 GetCharaResMgr_1fdb60(void);
Ctx *GetGameData_1fede0(void);
void FuncPointDeactivate_2000e0(s32, s32);
s32 GetMapMgr_201a90(void);
void FieldHudAllySuggestCancel_203c80(void);
s64 FieldHudBtlEscGetResult_203cb0(void);
void FieldHudBtlEscOpen_203d20(s32);
s32 FieldHudRowsSettled_203d30(void);
void FieldHudTeardown_203d60(void);
void FieldHudHideAll_203e20(void);
void FieldHudLogOpen_203fb0(void);
void FieldHudWidget82Open_204030(void);
void FieldHudWidget81Open_204050(void);
void FieldHudEnemyListRefreshMaybe_2040d0(void);
void FieldHudMissionBannerHideMaybe_204100(void);
void FieldHudMissionBannerShowMaybe_204110(s32);
void FieldHudInitOnce_204120(void);
void FieldHudSetup_2041d0(s32);
void MenuBattleEndResRelease_204250(void);
s32 MenuBattleEndIsOpen_204330(void);
s32 MenuBattleEndOpenIfReady_204360(void);
void MenuBattleEndResLoad_2043b0(u8);
s32 BtlChgMenuGetResult_204ac0(void);
s32 ReturnTrue_204b40(void);
void BtlChgMenuOpen_204b50(s32);
s32 GetHpGaugeThin_206220(void);
void StreamPlayMwv_207340(s32, s32, f32);
void StreamChan0SetFillThreshold_2073e0(f32);
void BgmResumeSavedTrack_207420(s32);
void BgmSwitchTrackSaveResume_2076c0(s32, s32);
s32 BgmGetCurrent_207e70(void);
void BgmSetResumeWaitChan_207e80(s32);
void Nop_207ec0(void);
s32 CharaIsLocoModeMaybe_210070(Chr *);
s32 CharaIsFreeMoveStateMaybe_210190(Chr *);
s32 CharaIsDeadBodyKeptMaybe_210ae0(Chr *);
void CharaRequestAction_212410(Chr *, s32, f32);
void CharaAddFlags_212460(Chr *, u64);
void CharaInvokeInitNrm_212b30(Chr *);
void CharaResetBattleStateMaybe_212f20(Chr *, s32);
void CharaSetBaseActionMode_213820(Chr *, s32);
s32 CharaGetBaseActionMode_213830(Chr *);
void CharaSetPos_213a40(Chr *, Vec *);
void CharaSetLastSafePosMaybe_213a80(Chr *, Vec *);
s32 CharaGetAreaId_213c90(Chr *);
void CharaRequestBattleExit3_213e60(Chr *);
void CharaRequestBattleExit2_213e80(Chr *);
void CharaRequestBattleExit1_213ea0(Chr *);
void CharaRequestBattleEnter_213ec0(Chr *, s32);
s32 CharaCurMotionIsBattleSetMaybe_213ef0(Chr *);
s32 CharaHasEvObjContact_214960(Chr *);
s32 CharaGetAi_214a10(Chr *);
s32 CharaGetTargetRef_214a30(Chr *);
void CharaGetLastSafePosMaybe_214a50(Chr *, Vec *);
s32 CharaGetId_214a80(Chr *);
s32 ActionMgrGetCharaList_233b40(void *);
Chr *ActionMgrFindById_233b50(void *, s32);
void CharaGetPlacedPosMaybe_238280(Chr *, Vec *);
s32 CharaGetGroundPos_2382d0(Chr *, Vec *);
void CharaGetPos_2388a0(Chr *, Vec *);
void CharaGetRot_2388b0(Chr *, Vec *);
void MesSlot0Close_278e40(void);
void BtlChgMenuAbilityReqApply_27a4c0(World *);
void TaskStatePushAll_27c220(void);
void TaskStatePopAll_27c250(void);
void TaskSetEnabled_27c2a0(s32, void *);
void GameFlowSetChainNo_285ee0(s32);
void GameFlowSetChainTargetKind_285ef0(s32);
void GameFlowSetChainTargetId_285f00(s32);
s32 GameFlowGetChainNo_285f20(void);
s32 GameFlowGetChainTargetId_285f40(void);
s32 GameFlowGetChainCharaId_285f50(void);
void TaskEnableBattleSet_2873f0(void);
void TaskSetUpdateTasksPaused_287dd0(s32);
void TaskSetCharaTasksPaused_288130(s32);
void FieldHudCloseWidgets_288240(s32);
void SceneTimeScaleRestore_2882d0(void);
void ClearInBattle_288400(void);
void SetInBattle_288410(void);
f32 AiGetCurWaypointGoalDistMaybe_2c0f40(s32);
void ScriptStrTableFree_2ccaa0(void);
void ScriptStrTableInit_2ccae0(void);
void EvMapObjScatterInBattleAreaMaybe_2d0b60(Vec *);
s32 GetNavMgr_2d1950(void);
s32 GetEventObjMgr_2d1960(void);
void DamagePopupListInitCullDist_2d8890(void);
s32 GetEffectMgr_2d9040(void);
s32 EffectMgrIsLoadDone_2dffc0(s32);
void TargetRefClear_2e71d0(s32);
void EvMapObjResetAreaObjsAllMaybe_2e9440(s32);
void EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(s32, s32, s32);
void EventObjMgrMapObjsSetRateFromFrames_2e9500(s32, s32);
s32 EventObjMgrGetTypeList_2e9d60(s32, s32);
void BattleEncounterPlaceAtSpawnMaybe_2f2300(void);
void BattleEncounterSetupMaybe_2f25f0(void);
void BattleEncounterUnitsSetupMaybe_2f2b60(void);
void FieldViewModeActivateEncounterMaybe_2f3400(void);
void FieldViewModeActivateMaybe_2f34d0(void);
s32 FieldViewModeGet_2f35a0(void);
void FieldModeResReleaseMaybe_2f35b0(void);
void PartyApplyLeaderChange_2f36f0(void);
void GameDataLatchLeaderId_2f38e0(void);
void CharaPlaceAt_2f3a40(s32, Vec *, s32, f32);
void HudFadeOutAll_2f47e0(s32);
s32 LeaderGetControlStateMaybe_2f5440(void);
void SceneSoundMutePop_2f6670(void);
void SceneSoundMutePush_2f6710(void);
void EvDoorObjSetOpenRequest_303d10(Chr *, s32, s32);
void CameraSetDefaultParams_309260(Cam *, World *);
s32 CameraGetOptionFlag_309d70(void);
void CameraPopModeCurrent_309db0(void);
void CameraPushModeOpenHudWidget81_309df0(s8);
void CameraResetLevelViewMaybe_30a150(s32);
void CameraSwitchTo3Fixed_30a2a0(void);
s32 NavFindApproachPointMaybe_30bf70(s32, Vec *, Vec *, s16, Vec *, Vec *);
s32 NavMgrFindGraphById_30cae0(s32, s32);
s32 NavFindNearestCenterEdgePoint_30fe80(s32, Vec *, Vec *, s32);
void TargetMngCycleAndSetTarget_313a10(s32);
void TargetMngCancel_313a70(void);
void TargetMngSetTarget_313ad0(s32);
s32 TargetMngGetTargetId_313be0(void);
s32 TargetMngHasTargetId_313bf0(void);
void TargetMngClearTarget_313c00(void);
s32 GetTargetMng_313dd0(void);
void HpGaugeDisable_31d410(s32);
void HpGaugeRequestReset_31e1d0(s32);
void TargetMngSetEnabled_31f4e0(s32, s32);
s32 TargetMngGetTargetRef_320820(s32);
void MapCaptionClose_33f9a0(s32, f32);
s32 CharaSysGetEncounterIdMaybe_3a36d0(Game *);
void CharaSysDeactivateMaybe_3a3760(Game *);
void CharaSysStateGetBattlePosMaybe_3a3840(Game *, Vec *);
s32 CharaSysStateFlag24Bit2Related_3a3880(Game *);
s32 CharaSysStateFlag24Bit1Related_3a38a0(Game *);
s32 CharaSysEncounterBindAndStartMaybe_3a5340(Game *, s32, s32);
s32 CharaSysStartQueuedEncounterMaybe_3a54f0(Game *);
void CharaSysEncounterDistRoll_3a59d0(Game *, s32);
Unit *CharaMgrPoolFindById_3a8c60(s32, s32);
Site *ObjFindById_3bb3a0(s32, s32);
s32 PartyCountMembers_3c2010(Party *, s32, s32);
s32 PartyGetMemberId_3c2490(Party *, s32);
s32 PartyCountExcludingLeader_3c2610(Party *, s32, s32);
s32 PartyGetNonLeaderId_3c2750(Party *, s32);
u8 *PartyGetBgmOverride_3cb100(Party *);
void StateFlagSet_3ccb70(s32, s32, s32, s32);
s32 StateFlagTest_3ccd70(s32, s32);
void EventRunPendingTriggerAction_3e0630(void);
void PartyBattleEndTriggerCheckMaybe_3e06c0(s32, s32);
void PartyBattleEndTriggerSetDelayMaybe_3e0840(s32, s32);
s32 EventFireTriggers_3e2660(Dlg *, u8 *);
void ActionPacketInitBattleEnd_3e3550(Dlg *, World *, s32);
void ActionPacketReset_3e3d00(Dlg *);
void GameDataBattleEnd_3e67c0(Ctx *, s32, s32, s32, s32);
void GameDataBattleBroadcastPhase_3e6890(Ctx *, s32);
void GameDataBattleBegin_3e6930(Ctx *);
void SkillLockClearResetSpot_3eb6c0(Ctx *, s32);
void SkillLockSetResetSpot_3eb6f0(Ctx *, s32);
Ally *ActorFindById_3eb870(Ctx *, s32);
Node *DListGetHead_42ea60(s32);
Node *DListGetNext_42eb30(Node *);
void BtlChgMenuCloseThunk_4f9d70(void);
s32 BtlChgMenuIsAbilityListOpenThunk_4f9f60(void);
void TargetMngClearTargetThunk_313c00(void);

extern Con *const D_00449858;
extern f32 D_0045B080[];
extern u8 D_0045FF78[];
extern u8 D_0045FF98[];
extern u8 D_0045FFB8[];
extern u8 D_004600B8[];
extern u8 D_004602D8[];
extern u8 D_00460390[];
extern u8 D_004603D0[];
extern u8 D_004603F0[];
extern u8 D_004604F0[];
extern u8 D_00460588[];
extern u8 D_004605D8[];
extern u8 D_00460850[];
extern u8 D_00460AB0[];
extern u8 D_00460BC8[];
extern u8 D_00460C48[];
extern const char D_00460E80[];
extern const s32 D_00465C80;
extern const f32 D_0047D1EC __attribute__((section(".sdata")));
extern f32 D_0047D288;
extern f32 D_0047D5D0;
extern s32 D_0047EA00;
extern Vec D_0047EA10 __attribute__((section(".sdata")));
extern Vec D_00482200 __attribute__((section(".sdata")));
extern f32 D_00482210;
extern f32 D_00482214;
extern f32 D_00482218;
extern f32 D_0048221C;
extern u8 D_00482220;
extern u8 D_00482224;
extern u8 D_00482228;
extern u8 D_0048222C;
extern f32 D_00482230;
extern f32 D_00482234;
extern u8 D_004B2570[];
}

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 16; if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

static inline Chr *Member(void *mgr, Ctx *ctx, s32 i) {
    return ActionMgrFindById_233b50(mgr, PartyGetMemberId_3c2490(ctx->f18, i));
}

static inline f32 AbsI(f32 x) {
    return x < 0.0f ? -x : x;
}

static inline s32 Mode(Ctx *ctx) {
    Mission *m = ctx->f20->f238;

    return m ? m->f168 : 0;
}

static inline Info *MInfo(Ctx *ctx) {
    Mission *m = ctx->f20->f238;

    return m ? m->f18 : 0;
}

static inline void Clear(Ctx *ctx) {
    Mission *m = ctx->f20->f238;

    if (m) m->f0 = 0;
}

static inline f32 Tick(World *w) {
    return D_00482218 = D_00482218 - GameSceneGetTimeStep_1ceba0(w);
}

struct Bit64 {
    u64 *p;
    s32 n;
};

static inline void Set64(Bit64 *b, u64 *p, s32 n) {
    s32 k;

    b->p = p;
    b->n = n;
    k = *(s32 *)&b->n;
    if (k != 0) {
        Fprintf_12f9a0(D_00449858->fC, D_00460E80);
        Abort_12de80();
    }
    *b->p |= 1ULL << k;
}

static inline u8 Pinned(Info *in) {
    u8 r = 0;

    if (in) r = in->f7E.on != 0;
    return r;
}

extern "C" s32 BattleModeUpdate_280220(void) {
    Ctx *ctx;
    World *w;
    s32 area;
    void *mgr;
    s32 n;
    s32 i;
    s32 k;
    s32 v;
    s32 h;
    s32 id;
    s32 best;
    bool ok;
    s32 pin;
    Chr *c;
    Cam *cam;
    Ally *al;
    Info *in;
    Game *g;
    Node *nd;
    s32 n1;
    s32 i1;
    Chr *c1;
    s32 n2;
    s32 i2;
    s32 k2;
    s32 n3;
    s32 i3;
    Chr *c3;
    s32 n4;
    s32 i4;
    Chr *c4;
    Node *nd5;
    Chr *c5;
    Node *nd6;
    Chr *c6;
    Node *nd7;
    Chr *c7;
    s32 i8;
    Chr *c8;
    s32 n8;
    s32 n9;
    s32 i9;
    Chr *c9;
    s32 i10;
    Chr *c10;
    s32 n10;
    s32 n11;
    s32 i11;
    Chr *c11;
    s32 n12;
    s32 id12;
    s32 i12;
    Chr *c12;
    s32 i13;
    Chr *c13;
    s32 n13;
    s32 n14;
    s32 i14;
    Chr *c14;
    Chr *c15;
    s32 n15;
    s32 i15;
    u8 sp41F;
    s16 sp410[7];
    s16 sp400[7];
    Bit64 bits;
    Vec vec3E0;
    Vec vec3D0;
    Vec vec3C0;
    Vec vec3B0;
    Mat mat370;
    Vec vec360;
    Vec vec350;
    Vec vec340;
    s32 ids[12];
    Vec vec300;
    Vec vec2F0;
    Vec vec2E0;
    Vec vec2D0;
    Vec vec2C0;
    Vec vec2B0;
    Vec vec2A0;
    Vec vec290;
    Vec vec280;
    Vec vec270;
    Vec vec260;
    Vec vec250;
    Vec vec240;
    Dlg dlg210;
    Dlg dlg1E0;
    Dlg dlg1B0;
    Vec vec1A0;
    Vec vec190;
    Vec vec180;
    Vec vec170;
    Vec vec160;
    Vec vec150;
    Vec vec140;
    Vec vec130;
    Vec vec120;
    Vec vec110;
    Dlg dlgE0;
    Dlg dlgB0;
    f32 m23;
    f32 b23;
    f32 f23;
    f32 m22;
    f32 b22;
    f32 f22;
    f32 unit;
    f32 m21;
    f32 b21;
    f32 e21;
    f32 g21;
    f32 f21;
    f32 r30;
    f32 m20;
    f32 b20;
    f32 e20;
    f32 g20;
    f32 f20;
    f32 d;

    ctx = GetGameData_1fede0();
    w = GetCurrentScene_1f5be0();
    area = GetMapMgr_201a90();
    mgr = GetActionMgr_1fdb50();
    GameReqQueueRemoveById_1f5a10(7);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        SetGameReqHold_1f5890();
        if (ctx->f20->f238) Set64(&bits, &ctx->f20->f238->f0, 0);
        SetGameModePhase_1f59a0(100);
        g = ctx->f20;
        if (!(g->f24C & 1)) CharaSysDeactivateMaybe_3a3760(g);
        FieldViewModeActivateMaybe_2f34d0();
        return 1;
    case 0:
        Clear(ctx);
        if (CharaSysStartQueuedEncounterMaybe_3a54f0(ctx->f20) <= 0) {
            CharaSysEncounterDistRoll_3a59d0(ctx->f20, 1);
            GameReqQueuePushBack_1f5b50(0, -1);
            return 1;
        }
        FieldViewModeActivateMaybe_2f34d0();
        SetGameReqHold_1f5890();
        SetGameModePhase_1f59a0(100);
        return 1;
    case 1:
        Clear(ctx);
        if (CharaSysEncounterBindAndStartMaybe_3a5340(ctx->f20, -1, -1) <= 0) {
            CharaSysEncounterDistRoll_3a59d0(ctx->f20, 1);
            GameReqQueuePushBack_1f5b50(0, -1);
            return 1;
        }
        FieldViewModeActivateEncounterMaybe_2f3400();
    case 2:
        Clear(ctx);
        if (FieldViewModeGet_2f35a0() == 0) {
            Mission *m;

            g = ctx->f20;
            m = g->f238;
            pin = 0;
            in = m ? m->f18 : 0;
            if (in) pin = in->f7E.on != 0;
            if (pin || CharaSysStateFlag24Bit2Related_3a3880(g)) {
                FieldViewModeActivateEncounterMaybe_2f3400();
                BattleEncounterSetupMaybe_2f25f0();
            } else {
                FieldViewModeActivateMaybe_2f34d0();
            }
        }
        SetGameReqHold_1f5890();
        SetGameModePhase_1f59a0(100);
        return 1;
    case 100:
        D_00482234 = 0.0f;
        GameReqQueueRemoveById_1f5a10(0xC);
        GameReqQueueRemoveById_1f5a10(0xD);
        GameReqQueueRemoveById_1f5a10(8);
        GameReqQueueRemoveById_1f5a10(9);
        GameReqQueueRemoveById_1f5a10(0x11);
        GameReqQueueRemoveById_1f5a10(0x14);
        GameReqQueueRemoveById_1f5a10(0x13);
        MesSlot0Close_278e40();
        v = MapMgrGetCaption_1e56c0(area);
        if (v != 0) MapCaptionClose_33f9a0(v, 15.0f);
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        TaskEnableBattleSet_2873f0();
        SetInBattle_288410();
        Nop_207ec0();
        FuncPointDeactivate_2000e0(0, 0);
        HudFadeOutAll_2f47e0(0xF);
        {
            s32 id_ = w->f4344;

            D_0048221C = 0.0f;
            cam = ObjRecGetLiveObject_1c3bc0(w, id_);
        }
        if (cam != 0) {
            cam->GetPos(&vec3E0);
            cam->GetAt(&vec3D0);
            D_0048221C = vec3E0.y - vec3D0.y;
        }
        D_00482228 = 0;
        D_0047EA00 = 2;
        r30 = 30.0f * (unit = D_0045B080[0]);
        pin = 0;
        D_00482210 = r30;
        g = ctx->f20;
        {
            Mission *m = g->f238;

            D_0048222C = 0;
            in = m ? m->f18 : 0;
        }
        if (in) pin = in->f7E.on != 0;
        if (pin || CharaSysStateFlag24Bit2Related_3a3880(g)) {
            BattleEncounterPlaceAtSpawnMaybe_2f2300();
            best = in->f2C;
            D_0048222C = 1;
            CameraPushModeOpenHudWidget81_309df0(best);
            FieldHudWidget82Open_204030();
            BgmSwitchTrackSaveResume_2076c0(in->f18, 1);
            CharaSysStateGetBattlePosMaybe_3a3840(ctx->f20, &D_00482200);
            if ((D_00482210 = in->f20) <= 0.0f) {
                D_0047EA00 = 0;
            } else if (CharaSysStateFlag24Bit1Related_3a38a0(ctx->f20) != 0) {
                D_0047EA00 = 1;
            } else {
                D_0047EA00 = 2;
            }
            if (CharaSysStateFlag24Bit2Related_3a3880(ctx->f20) != 0) {
                c = ActionMgrFindById_233b50(mgr, ctx->f18->f18E);
                if (c != 0) {
                    CharaGetPos_2388a0(c, &vec3C0);
                    CharaGetRot_2388b0(c, &vec3B0);
                    MatFromRotPos_1caf90(&mat370, &vec3B0, &vec3C0);
                    n1 = PartyCountExcludingLeader_3c2610(ctx->f18, 1, 1);
                    i1 = 0;
                    b22 = D_0045B080[0];
                    b21 = 20.0f * b22;
                    b20 = -2.0f * b22;
                    for (; i1 < n1; i1++) {
                        c1 = ActionMgrFindById_233b50(mgr, PartyGetNonLeaderId_3c2750(ctx->f18, i1));
                        if (c1 != 0) {
                            CharaGetPos_2388a0(c1, &vec360);
                            if (AiGetCurWaypointGoalDistMaybe_2c0f40(CharaGetAi_214a10(c1)) <= b21 && CharaGetGroundPos_2382d0(c1, &vec350) != 0) {
                                d = AbsI(vec350.y - vec3C0.y);
                                if (d <= 2.0f * b22) {
                                    d = D_00482210;
                                    b23 = 0.75f * d;
                                    if (VecDistSqXZ_1cb390(&D_00482200, &vec360) <= b23 * b23) {
                                        v = MapSlotsFindById_1e4b90(area, CharaGetAreaId_213c90(c1), 0);
                                        if (v != 0 && MapDataIsBattleForceWarp_1e7a10(v) == 0) continue;
                                    }
                                }
                            }
                            {
                                Vec *__restrict p_ = &vec340;

                                d = (f32)(1 - i1 * 2);
                                *p_ = D_0047EA10;
                                p_->x = d * b22;
                                p_->z = b20;
                                MatMulPoint_1cb8e0(&vec360, &mat370, p_);
                            }
                            CharaPlaceAt_2f3a40(CharaGetId_214a80(c1), &vec360, 0xF, vec3B0.y);
                        }
                    }
                }
            }
        } else {
            Party *pt = ctx->f18;

            k2 = 0;
            ids[k2++] = pt->f18E;
            n2 = PartyCountExcludingLeader_3c2610(pt, 1, 1);
            for (i2 = 0; i2 < n2; i2++) {
                ids[k2++] = PartyGetNonLeaderId_3c2750(ctx->f18, i2);
            }
            CharaResLoadListMaybe_1f02d0(GetCharaResMgr_1fdb60(), w, ids, k2);
            GameDataBattleBegin_3e6930(ctx);
            n3 = PartyCountMembers_3c2010(ctx->f18, 1, 1);
            for (i3 = 0; i3 < n3; i3++) {
                c3 = Member(mgr, ctx, i3);
                if (c3 != 0) CharaRequestBattleEnter_213ec0(c3, 0);
            }
            cam->GetAt(&vec2F0);
            cam->GetPos(&vec300);
            VecSub_1cbd00(&vec2E0, &vec2F0, &vec300);
            ZERO16(&vec2C0);
            c = ActionMgrFindById_233b50(mgr, ctx->f18->f18E);
            if (c != 0) {
                CharaGetRot_2388b0(c, &vec2C0);
                CharaGetGroundPos_2382d0(c, &vec2D0);
                CharaGetPlacedPosMaybe_238280(c, &vec2B0);
                CharaGetPlacedPosMaybe_238280(c, &vec2A0);
                d = VecDistSqXZ_1cb390(&vec2A0, &vec2D0);
                if (!(d <= 0.0f)) {
                    m23 = D_0045B080[0];
                    m23 = D_0047D5D0 * (volatile f32)m23;
                    if (d < m23 * m23) {
                        CharaGetPos_2388a0(c, &vec290);
                        vec290.x = vec2B0.x;
                        vec290.z = vec2B0.z;
                        CharaSetPos_213a40(c, &vec290);
                    } else {
                        vec2C0.y = Atan2f_1291a8(vec2B0.x - vec2D0.x, vec2B0.z - vec2D0.z);
                        CharaPlaceAt_2f3a40(CharaGetId_214a80(c), &vec2B0, 0xF, vec2C0.y);
                    }
                    VecCopy_1cbe30(&vec2D0, &vec2B0);
                }
            } else {
                VecCopy_1cbe30(&vec2D0, &vec2F0);
            }
            h = GetNavMgr_2d1950();
            if (NavFindApproachPointMaybe_30bf70(h, &D_00482200, &vec2D0, ctx->f18->fC, &vec300, &vec2E0) == 0) {
                VecCopy_1cbe30(&D_00482200, &vec2D0);
            }
            ZERO16(&vec270);
            v = NavMgrFindGraphById_30cae0(h, ctx->f18->f10);
            if (v == 0 || NavFindNearestCenterEdgePoint_30fe80(v, &vec280, &vec2D0, 0) == 0) {
                VecCopy_1cbe30(&vec280, &vec2D0);
            } else {
                VecCopy_1cbe30(&vec280, &vec2D0);
                VecSub_1cbd00(&vec270, &vec2D0, &vec280);
                VecScaleToLength_1cb510(&vec270, &vec270, unit);
            }
            n4 = PartyCountExcludingLeader_3c2610(ctx->f18, 1, 1);
            i4 = 0;
            m22 = D_0045B080[0];
            m21 = 20.0f * m22;
            for (; i4 < n4; i4++) {
                c4 = ActionMgrFindById_233b50(mgr, PartyGetNonLeaderId_3c2750(ctx->f18, i4));
                if (c4 != 0) {
                    k = CharaGetAi_214a10(c4);
                    CharaGetPos_2388a0(c4, &vec260);
                    if (AiGetCurWaypointGoalDistMaybe_2c0f40(k) <= m21 && CharaGetGroundPos_2382d0(c4, &vec250) != 0) {
                        d = AbsI(vec250.y - vec2D0.y);
                        if (d <= 2.0f * m22) {
                            d = D_00482210;
                            m23 = 0.75f * d;
                            if (VecDistSqXZ_1cb390(&D_00482200, &vec260) <= m23 * m23) {
                                v = MapSlotsFindById_1e4b90(area, CharaGetAreaId_213c90(c4), 0);
                                if (v != 0 && MapDataIsBattleForceWarp_1e7a10(v) == 0) continue;
                            }
                        }
                    }
                    VecScale_1cbca0(&vec260, &vec270, (f32)(1 - i4 * 2));
                    VecAdd_1cbdc0(&vec260, &vec260, &vec280);
                    vec260.x += RandRangeFloat_1ca5d0(2.0f) - 1.0f;
                    vec260.z += RandRangeFloat_1ca5d0(2.0f) - 1.0f;
                    CharaPlaceAt_2f3a40(CharaGetId_214a80(c4), &vec260, 0xF, vec2C0.y);
                }
            }
            BattleEncounterUnitsSetupMaybe_2f2b60();
            ScatterCharasOnGroundMaybe_1fbe70(&D_00482200, &vec2D0);
            VecSub_1cbd00(&vec240, &D_00482200, &vec2D0);
            vec240.y = 0.0f;
            m21 = D_0045B080[0];
            m21 = (volatile f32)m21 * 15.0f;
            if (!(VecLengthSqXZ_1cb450(&vec240) < m21 * m21)) {
                VecScaleToLength_1cb510(&vec240, &vec240, m21);
                VecAdd_1cbdc0(&D_00482200, &vec2D0, &vec240);
            }
            D_00482210 = r30;
            if (in != 0) {
                D_0047EA00 = 1;
            } else {
                D_0047EA00 = 2;
            }
            D_00482214 = 0.0f;
            id = BgmGetCurrent_207e70();
            {
                u8 *q = PartyGetBgmOverride_3cb100(ctx->f18);

                if (q == 0 || (q != 0 && !(q[2] & 1))) {
                    Mission *m = ctx->f20->f238;

                    id = m ? m->f162 : D_00465C80;
                }
            }
            BgmSwitchTrackSaveResume_2076c0(id, 1);
            SoundPlayScaledVolume_1b9520(GameSceneSoundSlot5GetHandle_1d0790(w), 0x46, 0, 1.0f);
        }
        EvMapObjScatterInBattleAreaMaybe_2d0b60(&D_00482200);
        FieldHudSetup_2041d0(1);
        DamagePopupListInitCullDist_2d8890();
        in = MInfo(ctx);
        if (in == 0 || in->f1A != 0) FieldHudMissionBannerShowMaybe_204110(0x5A);
        ScriptStrTableInit_2ccae0();
        HpGaugeRequestReset_31e1d0(GetHpGaugeThin_206220());
        TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
        D_00482218 = 45.0f;
        SetGameModePhase_1f59a0(0x65);
        for (nd5 = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(GetEventObjMgr_2d1960(), 9)); nd5 != 0; ) {
            c5 = (Chr *)(nd5 + 1);
            nd5 = DListGetNext_42eb30(nd5);
            EvDoorObjSetOpenRequest_303d10(c5, 0, 0);
        }
        return 0;
    case 101:
        if (StateFlagTest_3ccd70(ctx->f10, 0x7F8) != 0) {
            ClearGameReqHold_1f5880();
            GameReqQueuePushBack_1f5b50(0x11, -1);
            return 1;
        }
        {
            if (!(Tick(w) < 0.0f)) return 0;
            if (D_0048222C == 0) {
                CameraPushModeOpenHudWidget81_309df0(2);
                FieldHudWidget82Open_204030();
                if (CameraGetOptionFlag_309d70() == 0) {
                    ScreenFadeReset_1cf760(w);
                    ScreenFadeCaptureFrame_1cf550(w);
                    ScreenFadeDissolveIn_1cf720(w, 0xF, 1.0f);
                }
            }
            GetCharaResMgr_1fdb60();
            PartyCountMembers_3c2010(ctx->f18, 1, 1);
            StreamChan0SetFillThreshold_2073e0(D_0047D288);
            TaskSetCharaTasksPaused_288130(0);
            FieldHudMissionBannerHideMaybe_204100();
            in = MInfo(ctx);
            if (in == 0 || in->f1A != 0) FieldHudEnemyListRefreshMaybe_2040d0();
            FieldHudInitOnce_204120();
            SetGameModePhase_1f59a0(0xC8);
            TargetMngClearTarget_313c00();
            return 0;
        }
    case 200:
        if (D_00482230 <= 0.0f) {
            SkillLockClearResetSpot_3eb6c0(ctx, 1);
            TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 2);
            SetGameReqHold_1f5890();
            TaskEnableBattleSet_2873f0();
            FieldHudLogOpen_203fb0();
            SceneSoundMutePop_2f6670();
            GameSceneSetTimeScaleLockedMaybe_1ceb90(w, 0);
            EventObjMgrMapObjsSetRateFromFrames_2e9500(GetEventObjMgr_2d1960(), 0xF);
        }
        D_00482230 = D_00482230 + GameSceneGetTimeStep_1ceba0(w);
        if (!(D_00482230 <= D_00482234)) {
            SetGameModePhase_1f59a0(0xC9);
        } else {
            return 0;
        }
    case 201: {
        Mission *m;

        g = ctx->f20;
        D_00482230 = 0.0f;
        m = g->f238;
        D_00482234 = 0.0f;
        k = m ? m->f168 : 0;
    }
        if (k != 0) {
            GameReqQueueRemoveById_1f5a10(8);
            GameReqQueueRemoveById_1f5a10(9);
            SkillLockSetResetSpot_3eb6f0(ctx, 1);
            TargetMngClearTarget_313c00();
            FieldHudCloseWidgets_288240(1);
            switch (Mode(ctx)) {
            case 1:
                ClearInBattle_288400();
                ActionPacketReset_3e3d00(&dlg210);
                ActionPacketInitBattleEnd_3e3550(&dlg210, w, 1);
                sp41F = 0;
                EventFireTriggers_3e2660(&dlg210, &sp41F);
                if (sp41F != 0) {
                    if (StateFlagTest_3ccd70(ctx->f10, 0x7F6) == 0) StreamSetChanVolumeFade_1cd960(GetLoaderMgr_1f59d0(), 0, 0xF, 0.0f);
                    GameDataBattleBroadcastPhase_3e6890(ctx, 1);
                    SetGameModePhase_1f59a0(0xFA0);
                    return 1;
                }
                SetGameModePhase_1f59a0(0x1F4);
                goto L_menu;
            case 2:
                ActionPacketReset_3e3d00(&dlg1E0);
                ActionPacketInitBattleEnd_3e3550(&dlg1E0, w, 0);
                EventFireTriggers_3e2660(&dlg1E0, 0);
                SetGameModePhase_1f59a0(0x2BC);
                GameReqQueuePushBack_1f5b50(2, -1);
                return 1;
            case 3:
                ActionPacketReset_3e3d00(&dlg1B0);
                ActionPacketInitBattleEnd_3e3550(&dlg1B0, w, 0);
                EventFireTriggers_3e2660(&dlg1B0, 0);
                ClearInBattle_288400();
                SetGameModePhase_1f59a0(0x258);
                return 1;
            case 4:
                GameDataBattleBroadcastPhase_3e6890(ctx, 4);
                SetGameModePhase_1f59a0(0xFA0);
                return 1;
            }
        }
    L_menu:
        switch (GameReqQueuePeekHead_1f5a70(0)) {
        case 11:
            EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(GetEventObjMgr_2d1960(), 0xF, 0);
            FieldReqHookStubRelated_1f9750();
            GameReqQueuePeekWarp_1f5a40(sp410);
            FieldHudCloseWidgets_288240(1);
            TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
            TargetMngClearTarget_313c00();
            if (GetGameModePhase_1f59b0() == 0x1F4 && GameReqQueuePeekWarp_1f5a40(sp400) != 0) {
                Page *pg = ctx->f8->f38->f8->Find(sp400[0]);

                if (pg != 0) {
                    D_00482218 = (f32)pg->f4;
                } else {
                    D_00482218 = 0.0f;
                }
                SetGameModePhase_1f59a0(0xBB8);
                return 1;
            } else {
                SetGameModePhase_1f59a0(0xC8);
                ClearGameReqHold_1f5880();
                return 1;
            }
        case 9: {
            Unit *u = CharaMgrPoolFindById_3a8c60(ctx->f14, GameFlowGetChainCharaId_285f50());

            if (u != 0) {
                switch (u->Kind()) {
                case 1:
                    GameFlowSetChainNo_285ee0(5);
                    break;
                case 2:
                    GameFlowSetChainNo_285ee0(7);
                    break;
                case 3:
                    GameFlowSetChainNo_285ee0(9);
                    break;
                }
            }
            if (GameFlowGetChainNo_285f20() == 0) {
                GameReqQueueRemoveById_1f5a10(9);
                goto L_def;
            }
            {
                TargetMngClearTarget_313c00();
                EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(GetEventObjMgr_2d1960(), 0, 0);
                if (GameFlowGetChainTargetId_285f40() < 0) {
                    void *mg = GetActionMgr_1fdb50();

                    c = ActionMgrFindById_233b50(mg, GameFlowGetChainCharaId_285f50());
                    if (c != 0) {
                        CharaGetPos_2388a0(c, &vec1A0);
                        best = -1;
                        for (id = 0x80; id <= 0x9B; id++) {
                            Chr *e;

                            al = ActorFindById_3eb870(ctx, id);
                            if (al != 0 && al->Busy() == 0 && (e = ActionMgrFindById_233b50(mg, id)) != 0 && !(e->fA44 & 0x80000)) {
                                CharaGetPos_2388a0(e, &vec190);
                                if (!(D_0047D1EC <= VecDistSqXZ_1cb390(&vec190, &vec1A0))) {
                                    best = id;
                                    break;
                                }
                            }
                        }
                        GameFlowSetChainTargetId_285f00(best);
                    }
                }
                if (GameFlowGetChainTargetId_285f40() >= 0) {
                    Site *st = ObjFindById_3bb3a0(ctx->f1C, GameFlowGetChainTargetId_285f40());

                    if (st != 0) {
                        SiteInfo *si = st->Info();

                        if (si != 0) {
                            switch (si->hi) {
                            case 1:
                                GameFlowSetChainTargetKind_285ef0(1);
                                break;
                            case 2:
                                GameFlowSetChainTargetKind_285ef0(2);
                                break;
                            case 3:
                                GameFlowSetChainTargetKind_285ef0(3);
                                break;
                            }
                        }
                    }
                }
            }
        }
        case 8:
            TargetMngClearTarget_313c00();
            FieldHudCloseWidgets_288240(1);
            SetGameModePhase_1f59a0(0xC8);
            ClearGameReqHold_1f5880();
            return 1;
        case 10:
            SceneSoundMutePush_2f6710();
            EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(GetEventObjMgr_2d1960(), 0, 0);
            FieldReqHookStubRelated_1f9750();
            FieldHudCloseWidgets_288240(1);
            D_00482234 = 8.0f;
            SetGameModePhase_1f59a0(0xC8);
            ClearGameReqHold_1f5880();
            return 1;
        case 17:
            FieldReqHookStubRelated_1f9750();
            FieldHudCloseWidgets_288240(1);
            SetGameModePhase_1f59a0(0xC8);
            ClearGameReqHold_1f5880();
            return 1;

        default:
        L_def:
            if (StateFlagTest_3ccd70(ctx->f10, 0x7F8) != 0) {
                GameReqQueuePushBack_1f5b50(0x11, -1);
                return 1;
            }
            if (TargetMngHasTargetId_313bf0() != 0) {
                al = ActorFindById_3eb870(ctx, TargetMngGetTargetId_313be0());
                if (al == 0 || al->Busy() != 0) {
                    TargetMngClearTargetThunk_313c00();
                } else {
                    if (al->Ready() == 0 || PadIsTriggered_1839f0(D_004B2570, 0x5000) != 0) TargetMngCancel_313a70();
                    if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) TargetMngCycleAndSetTarget_313a10(1);
                    if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) TargetMngCycleAndSetTarget_313a10(0);
                }
            } else {
                if (PadIsTriggered_1839f0(D_004B2570, 0x5000) != 0) TargetMngSetTarget_313ad0(TargetMngGetTargetRef_320820(GetTargetMng_313dd0()));
            }
            c = ActionMgrFindById_233b50(mgr, ctx->f18->f18E);
            if (c != 0 && CharaIsFreeMoveStateMaybe_210190(c) != 0 && PadIsTriggered_1839f0(D_004B2570, 0x400) != 0) {
                FieldHudCloseWidgets_288240(1);
                TargetMngClearTarget_313c00();
                CameraSwitchTo3Fixed_30a2a0();
                TaskSetEnabled_27c2a0(0, D_004600B8);
                SetGameModePhase_1f59a0(0x12C);
                return 0;
            }
            if (D_0047EA00 != 0) {
                ok = 1;
                nd6 = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(mgr));
                e21 = 5.0f * D_0045B080[0];
                for (; nd6 != 0; nd6 = DListGetNext_42eb30(nd6)) {
                    c6 = (Chr *)(nd6 + 1);
                    if (c6 != 0) {
                        if (!(c6->fA44 & 0x80000) && CharaGetId_214a80(c6) >= 0x80 && CharaGetId_214a80(c6) < 0x9C &&
                            !(ObjRecGetFlags_1c3d90(w, 1, CharaGetId_214a80(c6)) & 0x800000)) {
                            ok = 0;
                        }
                        if ((c6->f3D8 & 1) && CharaHasEvObjContact_214960(c6) == 0) {
                            CharaGetPos_2388a0(c6, &vec180);
                            e20 = D_00482210 - e21;
                            if (VecDistSqXZ_1cb390(&vec180, &D_00482200) <= e20 * e20) CharaSetLastSafePosMaybe_213a80(c6, &vec180);
                        }
                    }
                }
                if (ok) {
                    c = ActionMgrFindById_233b50(mgr, ctx->f18->f18E);
                    if (c != 0 && CharaIsLocoModeMaybe_210070(c) != 0) {
                        CharaGetPos_2388a0(c, &vec170);
                        e20 = D_00482210;
                        if (!(VecDistSqXZ_1cb390(&vec170, &D_00482200) <= e20 * e20)) D_00482214 -= 1.0f;
                    }
                }
                if (D_00482214 < 0.0f) {
                    D_00482214 = 1.0f;
                    FieldHudBtlEscOpen_203d20(D_0047EA00 == 1);
                    TaskStatePushAll_27c220();
                    TaskSetUpdateTasksPaused_287dd0(1);
                    TaskSetEnabled_27c2a0(1, D_00460588);
                    TaskSetEnabled_27c2a0(1, D_00460C48);
                    TaskSetEnabled_27c2a0(1, D_00460390);
                    TaskSetEnabled_27c2a0(1, D_004603F0);
                    SceneSoundMutePush_2f6710();
                    FieldHudCloseWidgets_288240(1);
                    TargetMngClearTarget_313c00();
                    SetGameModePhase_1f59a0(0x834);
                    return 1;
                }
            }
            {
                Ally *a_;

            a_ = ActorFindById_3eb870(ctx, ctx->f18->f18E);
                if (a_ != 0 && GameReqQueueContainsId_1f5b90(0xA) == 0 && GameReqQueueContainsId_1f5b90(9) == 0) {
                    Chr *lead;
    
                    c = ActionMgrFindById_233b50(mgr, 0);
                    lead = ActionMgrFindById_233b50(mgr, ctx->f18->f18E);
                    if ((c == 0 || !(c->fA44 & 0x100)) && !(lead->fA44 & 0x100) &&
                        ((a_->Busy() != 0 && lead != 0 && CharaIsDeadBodyKeptMaybe_210ae0(lead) != 0) ||
                         (a_->Busy() == 0 && PadIsTriggered_1839f0(D_004B2570, 0x10) != 0))) {
                        GameSceneSoundSlot0PlaySeVol_1d05f0(w, 0x11, 1.0f);
                        BtlChgMenuOpen_204b50(a_->Busy());
                        {
                            Cfg *cf;
    
                            v = CameraGetOptionFlag_309d70() != 0;
                            cf = ctx->fC;
                            D_00482220 = v;
                            D_00482224 = cf->f22 != 0;
                        }
                        GameDataLatchLeaderId_2f38e0();
                        FieldHudCloseWidgets_288240(1);
                        TaskStatePushAll_27c220();
                        TaskSetUpdateTasksPaused_287dd0(1);
                        TaskSetEnabled_27c2a0(1, D_00460588);
                        TaskSetEnabled_27c2a0(1, D_00460390);
                        SceneSoundMutePush_2f6710();
                        SetGameModePhase_1f59a0(0x7D0);
                        return 0;
                    }
                }
            }
            return 0;
        }
    case 300: {
        Mission *m;
        bool a;
        bool b;

        c = ActionMgrFindById_233b50(mgr, ctx->f18->f18E);
        m = ctx->f20->f238;
        a = (s32)((m ? m->f168 : 0) == 0);
        b = c != 0 && CharaIsFreeMoveStateMaybe_210190(c) != 0;
        a = a & b;
        a = a & !PadIsTriggered_1839f0(D_004B2570, 0x400);
        a = a & (~GameReqQueuePeekHead_1f5a70(0) == 0);
        if (!a) {
            v = 0;
            if (c != 0) v = CharaHasEvObjContact_214960(c) & 0xFF;
            CameraResetLevelViewMaybe_30a150(v);
            SetGameModePhase_1f59a0(0xC8);
            return 0;
        }
        TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
        TaskSetEnabled_27c2a0(0, D_00460850);
        if (c != 0) c->f3D0 |= 0x200000000000ULL;
        return 0;
    }
    case 2000:
        StreamChan0SetFillThreshold_2073e0(BtlChgMenuIsAbilityListOpenThunk_4f9f60() != 0 ? D_0047D5D0 : D_0047D288);
        v = BtlChgMenuGetResult_204ac0();
        if (v != 0) {
            TaskSetEnabled_27c2a0(0, D_004603D0);
            TaskSetEnabled_27c2a0(0, D_00460AB0);
            BtlChgMenuCloseThunk_4f9d70();
            switch (v) {
            case 1:
                if (EffectMgrIsLoadDone_2dffc0(GetEffectMgr_2d9040()) == 0) return 0;
                PartyApplyLeaderChange_2f36f0();
                if (D_00482220 != ((ctx->fC->f1A & 1) == 1)) FieldHudWidget81Open_204050();
                if (D_00482224 != (ctx->fC->f22 != 0)) FieldHudWidget82Open_204030();
                SceneSoundMutePop_2f6670();
                StreamChan0SetFillThreshold_2073e0(D_0047D288);
                TaskStatePopAll_27c250();
                SetGameModePhase_1f59a0(0xC8);
                return 1;
            case 2:
                SceneSoundMutePop_2f6670();
                StreamChan0SetFillThreshold_2073e0(D_0047D288);
                TaskStatePopAll_27c250();
                SetGameModePhase_1f59a0(0xC8);
                BtlChgMenuAbilityReqApply_27a4c0(w);
                return 1;
            }
        }
        if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0 && LeaderGetControlStateMaybe_2f5440() == 0) {
            StreamChan0SetFillThreshold_2073e0(D_0047D288);
            GameReqQueuePushBack_1f5b50(0x11, -1);
            ClearGameReqHold_1f5880();
            return 1;
        }
        if (ReturnTrue_204b40() != 0) {
            TaskSetEnabled_27c2a0(0, D_0045FF78);
            TaskSetEnabled_27c2a0(0, D_0045FF98);
            TaskSetEnabled_27c2a0(0, D_0045FFB8);
            TaskSetEnabled_27c2a0(0, D_004602D8);
            TaskSetEnabled_27c2a0(1, D_004603D0);
            TaskSetEnabled_27c2a0(1, D_00460AB0);
        }
        return 0;
    case 2100:
        switch ((s16)FieldHudBtlEscGetResult_203cb0()) {
        case 1:
            nd7 = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(mgr));
            g21 = 5.0f * D_0045B080[0];
            for (; nd7 != 0; nd7 = DListGetNext_42eb30(nd7)) {
                c7 = (Chr *)(nd7 + 1);
                if (!(c7->fA44 & 0x80000)) {
                    CharaGetLastSafePosMaybe_214a50(c7, &vec160);
                    VecSub_1cbd00(&vec150, &D_00482200, &vec160);
                    g20 = D_00482210 - g21;
                    if (!(VecLengthSqXZ_1cb450(&vec150) <= g20 * g20)) {
                        CharaSetLastSafePosMaybe_213a80(c7, &D_00482200);
                        VecCopy_1cbe30(&vec160, &D_00482200);
                    }
                    CharaPlaceAt_2f3a40(CharaGetId_214a80(c7), &vec160, 0, Atan2f_1291a8(vec150.x, vec150.z));
                }
            }
            CameraSnapReqAt_1f6d70(1);
            CameraSnapReqEye_1f6d60(1);
            ScreenFadeReset_1cf760(w);
            ScreenFadeCaptureFrame_1cf550(w);
            ScreenFadeDissolveIn_1cf720(w, 0xF, 1.0f);
            SceneSoundMutePop_2f6670();
            TaskStatePopAll_27c250();
            SetGameModePhase_1f59a0(0xC8);
            return 1;
        case 2:
            SceneSoundMutePop_2f6670();
            GameDataBattleBroadcastPhase_3e6890(ctx, 3);
            TaskStatePopAll_27c250();
            SetGameModePhase_1f59a0(0xC8);
            return 1;
        case 0:
            break;
        }
        return 0;
    case 500:
        {
            Mission *m = ctx->f20->f238;

            D_00482228 = 0;
            in = m ? m->f18 : 0;
        }
        if (in != 0 && *(s16 *)in != 1) D_00482228 = 1;
        TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
        n8 = PartyCountMembers_3c2010(ctx->f18, 1, 1);
        for (i8 = 0; i8 < n8; i8++) {
            c8 = Member(mgr, ctx, i8);
            if (c8 != 0) {
                {
                    u32 r_;
                    u8 f_;

                    r_ = c8->fA44 & ~0x8000;
                    f_ = D_00482228;
                    c8->fA44 = r_;
                    c8->fA44 = f_ ? (c8->fA44 | 0x800000) : (c8->fA44 & ~0x800000);
                }
                CharaRequestAction_212410(c8, 0, 1.0f);
                TargetRefClear_2e71d0(CharaGetTargetRef_214a30(c8));
            }
        }
        SetGameModePhase_1f59a0(0x1F5);
        return 1;
    case 501:
        v = GetLoaderMgr_1f59d0();
        StreamSetChanVolumeFade_1cd960(v, 0, 0xF, 0.0f);
        StreamSetChanVolumeFade_1cd960(v, 1, 0xF, 0.0f);
        StreamSetChanVolumeFade_1cd960(v, 2, 0xF, 0.0f);
        D_00482218 = 15.0f;
        SetGameModePhase_1f59a0(0x1F6);
        return 0;
    case 502:
        FieldHudHideAll_203e20();
        if (!(Tick(w) < 0.0f)) return 0;
        EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(GetEventObjMgr_2d1960(), 0xF, 1);
        GameDataBattleBroadcastPhase_3e6890(ctx, 1);
        FieldHudTeardown_203d60();
        MenuBattleEndResLoad_2043b0(D_00482228);
        TaskSetEnabled_27c2a0(1, D_004604F0);
        TaskSetEnabled_27c2a0(1, D_00460BC8);
        StreamPlayMwv_207340(0x320, 0, 1.0f);
        if (D_00482228 != 0) {
            TaskSetEnabled_27c2a0(0, D_004600B8);
        } else {
            BgmSetResumeWaitChan_207e80(1);
        }
        n9 = PartyCountMembers_3c2010(ctx->f18, 1, 1);
        for (i9 = 0; i9 < n9; i9++) {
            c9 = Member(mgr, ctx, i9);
            if (c9 != 0) {
                if (StateFlagTest_3ccd70(ctx->f10, 0x7F9) == 0) CharaRequestBattleExit3_213e60(c9);
                CharaAddFlags_212460(c9, 0x100000000000ULL);
            }
        }
        if (CameraGetOptionFlag_309d70() == 0) {
            ScreenFadeReset_1cf760(w);
            ScreenFadeCaptureFrame_1cf550(w);
            ScreenFadeDissolveIn_1cf720(w, 0xF, 1.0f);
        }
        TaskSetEnabled_27c2a0(0, D_00460850);
        CameraPopModeCurrent_309db0();
        cam = ObjRecGetLiveObject_1c3bc0(w, w->f4344);
        if (cam != 0) {
            CameraSetDefaultParams_309260(cam, w);
            cam->GetPos(&vec130);
            cam->GetAt(&vec140);
            d = D_0048221C;
            *(f32 *)((u8 *)cam + 0x16C) = d;
            vec130.y += d;
            cam->SetPos(&vec130);
            *(u128 *)((u8 *)cam + 0xF0) = *(u128 *)&vec130;
        }
        PartyBattleEndTriggerSetDelayMaybe_3e0840(0x1E, 1);
        SetGameModePhase_1f59a0(0x1F7);
        return 0;
    case 503:
        PartyBattleEndTriggerCheckMaybe_3e06c0(0, 1);
        if (MenuBattleEndOpenIfReady_204360() == 0) return 0;
        SetGameModePhase_1f59a0(0x1F8);
        return 1;
    case 504:
        PartyBattleEndTriggerCheckMaybe_3e06c0(0, 1);
        if (MenuBattleEndIsOpen_204330() != 0) return 0;
        TaskSetEnabled_27c2a0(1, D_004600B8);
        if (D_00482228 != 0) BgmResumeSavedTrack_207420(1);
        SetGameModePhase_1f59a0(0x1F9);
        D_00482218 = 450.0f;
        return 1;
    case 505:
        if (!(Tick(w) < 0.0f) && StateFlagTest_3ccd70(ctx->f10, 0x7F9) == 0) {
            n10 = PartyCountMembers_3c2010(ctx->f18, 1, 1);
            for (i10 = 0; i10 < n10; i10++) {
                c10 = Member(mgr, ctx, i10);
                if (c10 != 0 && CharaCurMotionIsBattleSetMaybe_213ef0(c10) != 0) {
                    CharaRequestBattleExit3_213e60(c10);
                    return 0;
                }
            }
        }
        PartyBattleEndTriggerCheckMaybe_3e06c0(0, 1);
        HpGaugeDisable_31d410(GetHpGaugeThin_206220());
        MenuBattleEndResRelease_204250();
        SetGameModePhase_1f59a0(0x3E8);
        return 0;
    case 600:
        k = 0x80;
        do {
            ParamTableFadeToZero_1cf9d0(w, k, 0xF);
            c = ActionMgrFindById_233b50(mgr, k);
            if (c != 0) c->fA44 |= 0x800000;
            k++;
        } while (k <= 0x9B);
        v = GetLoaderMgr_1f59d0();
        StreamSetChanVolumeFade_1cd960(v, 0, 0xF, 0.0f);
        StreamSetChanVolumeFade_1cd960(v, 1, 0xF, 0.0f);
        StreamSetChanVolumeFade_1cd960(v, 2, 0xF, 0.0f);
        TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
        TargetMngClearTarget_313c00();
        EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(GetEventObjMgr_2d1960(), 0xF, 1);
        FieldHudHideAll_203e20();
        TaskSetEnabled_27c2a0(0, D_004600B8);
        n11 = PartyCountMembers_3c2010(ctx->f18, 1, 1);
        for (i11 = 0; i11 < n11; i11++) {
            c11 = Member(mgr, ctx, i11);
            if (c11 != 0) {
                CharaRequestBattleExit2_213e80(c11);
                c11->fA44 &= ~0x8000;
                CharaAddFlags_212460(c11, 0x100000000000ULL);
                TargetRefClear_2e71d0(CharaGetTargetRef_214a30(c11));
            }
        }
        if (CameraGetOptionFlag_309d70() == 0) {
            ScreenFadeReset_1cf760(w);
            ScreenFadeCaptureFrame_1cf550(w);
            ScreenFadeDissolveIn_1cf720(w, 0xF, 1.0f);
        }
        HpGaugeDisable_31d410(GetHpGaugeThin_206220());
        D_00482218 = 30.0f;
        SetGameModePhase_1f59a0(0x259);
        return 1;
    case 601:
        if (!(Tick(w) < 0.0f)) return 0;
        BgmResumeSavedTrack_207420(1);
        TaskSetEnabled_27c2a0(1, D_004605D8);
        SetGameModePhase_1f59a0(0x25A);
        D_00482218 = 150.0f;
        return 1;
    case 602:
        if (!(Tick(w) < 0.0f)) {
            bool ok_;
            s32 n_;
            s32 i_;
            s32 id_;

            ok_ = 1;
            n_ = PartyCountMembers_3c2010(ctx->f18, 1, 1);
            for (i_ = 0; i_ < n_; i_++) {
                id_ = PartyGetMemberId_3c2490(ctx->f18, i_);
                c12 = ActionMgrFindById_233b50(mgr, id_);
                if (c12 != 0) {
                    if (CharaCurMotionIsBattleSetMaybe_213ef0(c12) == 0) {
                        if (id_ == ctx->f18->f18E) TaskSetEnabled_27c2a0(1, D_004600B8);
                    } else {
                        ok_ = 0;
                    }
                }
            }
            if (!ok_) return 0;
        }
        cam = ObjRecGetLiveObject_1c3bc0(w, w->f4344);
        if (cam != 0) {
            CameraSetDefaultParams_309260(cam, w);
            cam->GetPos(&vec110);
            cam->GetAt(&vec120);
            d = D_0048221C;
            *(f32 *)((u8 *)cam + 0x16C) = d;
            vec110.y += d;
            cam->SetPos(&vec110);
            *(u128 *)((u8 *)cam + 0xF0) = *(u128 *)&vec110;
        }
        FieldHudTeardown_203d60();
        SetGameModePhase_1f59a0(0x3E8);
        return 1;
    case 700:
        v = GetLoaderMgr_1f59d0();
        StreamSetChanVolumeFade_1cd960(v, 0, 0x1E, 0.0f);
        StreamSetChanVolumeFade_1cd960(v, 1, 0x1E, 0.0f);
        StreamSetChanVolumeFade_1cd960(v, 2, 0x1E, 0.0f);
        GameSceneSoundFadeOut_1d0340(w, 0x1E);
        D_00482218 = 60.0f;
        SetGameModePhase_1f59a0(0x2BD);
    case 701:
        if (!(Tick(w) < 0.0f)) return 0;
        v = GetLoaderMgr_1f59d0();
        StreamPauseChan_1cd9f0(v, 0);
        StreamPauseChan_1cd9f0(v, 1);
        StreamPauseChan_1cd9f0(v, 2);
        EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(GetEventObjMgr_2d1960(), 0xF, 1);
        TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
        TargetMngClearTarget_313c00();
        SetGameModePhase_1f59a0(0x2BE);
    case 702:
        GameDataBattleBroadcastPhase_3e6890(ctx, 1);
        HpGaugeDisable_31d410(GetHpGaugeThin_206220());
        FieldHudTeardown_203d60();
        v = GetLoaderMgr_1f59d0();
        StreamStopChan_1cda60(v, 0);
        StreamStopChan_1cda60(v, 1);
        StreamStopChan_1cda60(v, 2);
        SoundBankStopAll_1bad70(-1);
        SetGameModePhase_1f59a0(0x3E8);
        return 1;
    case 4000:
        FieldHudHideAll_203e20();
        FieldHudAllySuggestCancel_203c80();
        FieldHudCloseWidgets_288240(1);
        EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(GetEventObjMgr_2d1960(), 0xF, 1);
        TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
        TargetMngClearTarget_313c00();
        SetGameModePhase_1f59a0(0xFA1);
        return 0;
    case 4001:
        if (FieldHudRowsSettled_203d30() == 0) return 0;
        SetGameModePhase_1f59a0(0xFA2);
        if (GameReqQueuePeekHead_1f5a70(0) == 11) {
            ClearGameReqHold_1f5880();
            return 1;
        }
    case 4002:
        SetGameReqHold_1f5890();
        GameReqQueuePushFront_1f5ab0(0, -1);
        if (Mode(ctx) == 4) {
            ActionPacketReset_3e3d00(&dlgE0);
            ActionPacketInitBattleEnd_3e3550(&dlgE0, w, 0);
            EventFireTriggers_3e2660(&dlgE0, 0);
        }
        SetGameModePhase_1f59a0(0x1004);
    case 4100:
        GameDataBattleEnd_3e67c0(ctx, 1, 0, 1, 0);
        TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
        n13 = PartyCountMembers_3c2010(ctx->f18, 1, 1);
        for (i13 = 0; i13 < n13; i13++) {
            c13 = Member(mgr, ctx, i13);
            if (c13 != 0) {
                c13->fA44 &= ~0x8000;
                CharaRequestBattleExit2_213e80(c13);
                CharaAddFlags_212460(c13, 0x100000000000ULL);
                TargetRefClear_2e71d0(CharaGetTargetRef_214a30(c13));
            }
        }
        EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(GetEventObjMgr_2d1960(), 0, 1);
        FieldHudTeardown_203d60();
        CameraPopModeCurrent_309db0();
        HpGaugeDisable_31d410(GetHpGaugeThin_206220());
        ClearInBattle_288400();
        v = GetLoaderMgr_1f59d0();
        StreamStopChan_1cda60(v, 1);
        StreamStopChan_1cda60(v, 2);
        SetGameModePhase_1f59a0(0x3E8);
        return 1;
    case 1000:
        GameReqQueueRemoveById_1f5a10(0x11);
        GameReqQueueRemoveById_1f5a10(0x14);
        GameReqQueueRemoveById_1f5a10(0x13);
        GameReqQueueRemoveById_1f5a10(8);
        GameReqQueueRemoveById_1f5a10(9);
        SceneTimeScaleRestore_2882d0();
        Nop_207ec0();
        if (CharaSysGetEncounterIdMaybe_3a36d0(ctx->f20) == 0x271B) CharaDataReleaseId12_1f00b0(GetCharaResMgr_1fdb60(), w);
        n14 = PartyCountMembers_3c2010(ctx->f18, 1, 1);
        for (i14 = 0; i14 < n14; i14++) {
            c14 = Member(mgr, ctx, i14);
            if (c14 != 0 && CharaGetBaseActionMode_213830(c14) != 0) {
                CharaSetBaseActionMode_213820(c14, 0);
                CharaResetBattleStateMaybe_212f20(c14, 0);
                CharaInvokeInitNrm_212b30(c14);
            }
        }
        EvMapObjResetAreaObjsAllMaybe_2e9440(GetEventObjMgr_2d1960());
        FieldModeResReleaseMaybe_2f35b0();
        CameraPopModeCurrent_309db0();
        cam = ObjRecGetLiveObject_1c3bc0(w, w->f4344);
        if (cam != 0) {
            cam->SetZoom(D_0048221C);
            cam->SetMode(0.0f);
        }
        ScriptStrTableFree_2ccaa0();
        if (GameReqQueuePeekHead_1f5a70(0) != 0) {
            ClearGameReqHold_1f5880();
        } else {
            SetGameReqHold_1f5890();
        }
        GameReqQueueRemoveById_1f5a10(8);
        GameReqQueueRemoveById_1f5a10(9);
        GameReqQueueRemoveById_1f5a10(0xA);
        SetGameModePhase_1f59a0(0x3E9);
        return 1;
    case 1001:
        switch (GameReqQueuePeekHead_1f5a70(0)) {
        case -1:
            GameReqQueuePushBack_1f5b50(0, -1);
            break;
        case 0:
            break;
        default:
            return 1;
        }
        StateFlagSet_3ccb70(ctx->f10, 0x7F9, 0, 1);
        StateFlagSet_3ccb70(ctx->f10, 0x7FA, 0, 1);
        ClearGameReqHold_1f5880();
        *(s32 *)((u8 *)mgr + 0x38) &= 0xEFFFFFFF;
        TaskStatePopAll_27c250();
        v = 0;
        if (Mode(ctx) == 1) {
            ActionPacketReset_3e3d00(&dlgB0);
            ActionPacketInitBattleEnd_3e3550(&dlgB0, w, 0);
            v = EventFireTriggers_3e2660(&dlgB0, 0);
        }
        if (v == 0) EventRunPendingTriggerAction_3e0630();
        return 1;
    case 3000:
        v = GetLoaderMgr_1f59d0();
        if (StateFlagTest_3ccd70(ctx->f10, 0x7F6) == 0) StreamSetChanVolumeFade_1cd960(v, 0, 0xF, 0.0f);
        StreamSetChanVolumeFade_1cd960(v, 1, 0xF, 0.0f);
        StreamSetChanVolumeFade_1cd960(v, 2, 0xF, 0.0f);
        SetGameModePhase_1f59a0(GetGameModePhase_1f59b0() + 1);
        Nop_207ec0();
        SetGameModePhase_1f59a0(0xBB9);
    case 3001:
        if (!(Tick(w) < 0.0f)) return 0;
        GameDataBattleEnd_3e67c0(ctx, 1, 0, 1, 0);
        TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
        HpGaugeDisable_31d410(GetHpGaugeThin_206220());
        TargetMngClearTarget_313c00();
        GameDataBattleBroadcastPhase_3e6890(ctx, 1);
        n15 = PartyCountMembers_3c2010(ctx->f18, 1, 1);
        for (i15 = 0; i15 < n15; i15++) {
            c15 = Member(mgr, ctx, i15);
            if (c15 != 0) {
                CharaRequestBattleExit1_213ea0(c15);
                CharaAddFlags_212460(c15, 0x100000000000ULL);
            }
        }
        EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(GetEventObjMgr_2d1960(), 0xF, 1);
        CameraPopModeCurrent_309db0();
        FieldHudTeardown_203d60();
        SetGameModePhase_1f59a0(0xC1C);
        ClearGameReqHold_1f5880();
        return 0;
    case 3100:
        SetGameReqHold_1f5890();
        ClearInBattle_288400();
        if (StateFlagTest_3ccd70(ctx->f10, 0x7E5) != 0) {
            StateFlagSet_3ccb70(ctx->f10, 0x7E5, 0, 0);
        } else {
            v = GetLoaderMgr_1f59d0();
            StreamStopChan_1cda60(v, 1);
            StreamStopChan_1cda60(v, 2);
        }
        SetGameModePhase_1f59a0(0x3E8);
        return 1;
    }
    return 0;
}
