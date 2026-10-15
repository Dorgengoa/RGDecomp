#include "types.h"

typedef struct Inner Inner;
struct Inner {
    u8 pad0[0x1188];
    s32 *unk1188;
};

typedef struct {
    u8 pad0[0x24];
    Inner *unk24;
} Outer;

extern s32 SoundBankRelease_1bb6e0(s32);
extern s16 *SysGetModeMsg_1c39b0(void);
extern s32 MonSoundBanksReload_1efd50(s32);
extern s32 CharaResReleaseSounds_1effa0(s32);
extern s32 SetGameExitRequest_1f57d0(s32);
extern s32 GameReqQueuePushBack_1f5b50(s32, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetCharaResMgr_1fdb60(void);
extern Outer *GetGameData_1fede0(void);
extern u8 SystemVmUpdate_2509f0(u8);
extern s32 SystemVmGetRunningEntry_250b70(void);
extern s32 TreasureBoxScriptEnd_278c40(s32);
extern s32 CharaInteractScriptEndMaybe_27a6d0(s32);
extern s32 FieldControlActivate_27a960(s32);
extern s32 GameDataStatusFxRestartAll_3e66c0(Outer *);
extern s32 RecordGetStateParamMaybe_430890(Inner *);
extern u8 D_0045B090[0x400];
extern u8 D_0045B098[0x400];
extern u8 D_0047E9A8;
extern u8 D_00482178;
extern u8 D_0048217C;
extern u8 D_00482184;

void TaskStepEvent_27abc0(void) {
    s32 temp_19;
    Outer *temp_18;
    s32 temp_16;
    u8 var_17;
    u8 var_16;
    s32 temp_2;
    s16 *temp_2_2;

    temp_16 = GetCurrentScene_1f5be0();
    temp_19 = GetCharaResMgr_1fdb60();
    temp_18 = GetGameData_1fede0();
    switch (D_0048217C) {
    case 0:
        D_0047E9A8 = SystemVmUpdate_2509f0(D_0048217C);
        if (D_0047E9A8 == 1) {
            FieldControlActivate_27a960(temp_16);
            if (*temp_18->unk24->unk1188 != 0) {
                var_17 = 0;
                var_16 = 0;
                temp_2 = SystemVmGetRunningEntry_250b70();
                if ((temp_2 == (*(s32 *)D_0045B090)) || (temp_2 == (*(s32 *)D_0045B098))) {
                    if ((u32)(RecordGetStateParamMaybe_430890(temp_18->unk24) - 0x13) <= 1U) {
                        var_17 = 1;
                    } else {
                        var_16 = 1;
                    }
                }
                if (var_17) {
                    GameReqQueuePushBack_1f5b50(0xF, -1);
                }
                if (var_16) {
                    GameReqQueuePushBack_1f5b50(3, -1);
                }
            } else {
                temp_2_2 = SysGetModeMsg_1c39b0();
                if ((D_00482178 & 1) && (*temp_2_2 == 6)) {
                    SetGameExitRequest_1f57d0(1);
                }
            }
            SoundBankRelease_1bb6e0(4);
            if (D_00482184 == 0) {
                CharaResReleaseSounds_1effa0(temp_19);
                MonSoundBanksReload_1efd50(temp_19);
                D_00482184 = 1;
            }
            GameDataStatusFxRestartAll_3e66c0(temp_18);
        }
        break;
    case 1:
        D_0047E9A8 = SystemVmUpdate_2509f0(D_0048217C);
        if (D_0047E9A8 == 1) {
            CharaInteractScriptEndMaybe_27a6d0(temp_16);
        }
        break;
    case 4:
        D_0047E9A8 = SystemVmUpdate_2509f0(D_0048217C);
        if (D_0047E9A8 == 1) {
            TreasureBoxScriptEnd_278c40(temp_16);
        }
        break;
    }
}
