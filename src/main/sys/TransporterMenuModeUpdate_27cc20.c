#include "types.h"

typedef struct {
    s32 kind;
    s16 id;
    s16 pad;
} R518620;

extern s32 GetGameData_1fede0(void);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetMapMgr_201a90(void);
extern void GameReqQueueRemoveById_1f5a10(s32);
extern s32 GetGameModePhase_1f59b0(void);
extern void SetGameReqHold_1f5890(void);
extern void TaskStatePushAll_27c220(void);
extern void TaskSetEnabled_27c2a0(s32, void *);
extern void GameSceneSoundSlot0PlaySe_1d05b0(s32, s32);
extern void SetGameModePhase_1f59a0(s32);
extern void SceneSoundMutePush_2f6710(void);
extern void MenuTransStart_203890(void);
extern s32 MenuTransIsReady_203870(void);
extern s32 TransMenuIsTransitioningThunk_516a60(void);
extern void TaskSetCharaTasksPaused_288130(s32);
extern void TaskSetRenderTasksEnabled_287b90(s32);
extern void SceneOverlayModeOn_288340(void);
extern void SceneOverlayModeOff_288300(void);
extern s32 TransMenuIsOpenThunk_516a50(void);
extern void TransMenuClose_2037b0(void);
extern void ClearGameReqHold_1f5880(void);
extern R518620 func_518620(void);
extern s32 GroupGetRecordById_425590(s32, s16);
extern void MapSlotsFindBlockById_1e49b0(s32, s32, s32);
extern f32 WrapAngle_13c050(f32);
extern void GameReqQueuePushWarp_1f5af0(s32, s32, s32, s32);
extern void GameReqQueuePushBack_1f5b50(s32, s32);
extern void ScreenFadeIn_1cf740(s32, s32);
extern void SceneSoundMutePop_2f6670(void);
extern void TaskStatePopAll_27c250(void);

extern u8 D_00460038[];
extern u8 D_004600B8[];
extern u8 D_004600C8[];
extern u8 D_00460230[];
extern u8 D_004602E8[];
extern u8 D_00460350[];
extern u8 D_00460420[];
extern u8 D_00460588[];
extern u8 D_00460850[];
extern u8 D_00460870[];
extern u8 D_00460998[];
extern u8 D_00460AE0[];
extern u8 D_00460C48[];
extern f32 D_0047D1FC;
extern u8 D_004D7E00[0x40];
extern s16 D_004D7E02[0x10];
extern s16 D_004D7E04[0x10];
extern s16 D_004D7E06[0x10];
extern s16 D_004D7E08[0x10];
extern s16 D_004D7E0A[0x10];
extern f32 D_004D7E0C[0x10];
extern f32 D_004D7E10[0x10];
extern f32 D_004D7E14[0x10];
extern f32 D_004D7E18[0x10];
extern s32 D_004D7E1C[0x10];
extern s32 D_004D7E20[0x10];
extern s32 D_004D7E24[0x10];
extern s32 D_004D7E28[0x10];

s32 TransporterMenuModeUpdate_27cc20(void) {
    s32 self;
    s32 ctx;
    s32 unit;
    s32 st;
    s32 flag;
    s32 obj;
    s32 id;
    s32 i;
    s32 t;
    R518620 tq;

    self = GetGameData_1fede0();
    ctx = GetCurrentScene_1f5be0();
    unit = GetMapMgr_201a90();
    GameReqQueueRemoveById_1f5a10(0xC);
    GameReqQueueRemoveById_1f5a10(0xD);
    GameReqQueueRemoveById_1f5a10(0x11);
    GameReqQueueRemoveById_1f5a10(0x13);
    GameReqQueueRemoveById_1f5a10(0x14);
    st = GetGameModePhase_1f59b0();
    switch (st) {
    case -1:
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        TaskSetEnabled_27c2a0(0, D_004600B8);
        TaskSetEnabled_27c2a0(0, D_004600C8);
        TaskSetEnabled_27c2a0(0, D_00460230);
        GameSceneSoundSlot0PlaySe_1d05b0(ctx, 2);
        SetGameModePhase_1f59a0(0);
        return 0;
    case 0:
        SceneSoundMutePush_2f6710();
        MenuTransStart_203890();
        SetGameModePhase_1f59a0(1);
        return 0;
    case 1:
        if (MenuTransIsReady_203870() == 0) {
            return 0;
        }
        SetGameModePhase_1f59a0(100);
        return 1;
    case 100:
        flag = TransMenuIsTransitioningThunk_516a60() != 0;
        TaskSetCharaTasksPaused_288130((flag != 0) ^ 1);
        TaskSetRenderTasksEnabled_287b90(flag);
        TaskSetEnabled_27c2a0(0, D_004602E8);
        TaskSetEnabled_27c2a0(0, D_00460998);
        TaskSetEnabled_27c2a0(0, D_004600B8);
        TaskSetEnabled_27c2a0(0, D_004600C8);
        TaskSetEnabled_27c2a0(0, D_00460850);
        TaskSetEnabled_27c2a0(0, D_00460038);
        TaskSetEnabled_27c2a0(0, D_00460350);
        TaskSetEnabled_27c2a0(0, D_00460870);
        TaskSetEnabled_27c2a0(1, D_00460420);
        TaskSetEnabled_27c2a0(1, D_00460AE0);
        if (flag == 0) {
            SceneOverlayModeOn_288340();
        } else {
            SceneOverlayModeOff_288300();
        }
        if (TransMenuIsOpenThunk_516a50() != 0) {
            return 0;
        }
        TransMenuClose_2037b0();
        SceneOverlayModeOff_288300();
        ClearGameReqHold_1f5880();
        SetGameModePhase_1f59a0(200);
        {
        R518620 r = func_518620();
        if (r.kind == 1) {
        obj = GroupGetRecordById_425590(*(s32 *)(*(s32 *)(self + 8) + 0x74), r.id);
        if (obj != 0) {
            id = *(s16 *)(obj + 0x18);
            if (*(s32 *)(obj + 0x40) & 1) {
            MapSlotsFindBlockById_1e49b0(unit, id, 0);
            *D_004D7E02 = -1;
            *D_004D7E04 = -1;
            *D_004D7E06 = -1;
            *D_004D7E08 = -1;
            *D_004D7E0A = -1;
            *D_004D7E0C = 0.0f;
            *D_004D7E10 = 0.0f;
            *D_004D7E14 = 0.0f;
            *D_004D7E18 = 0.0f;
            for (i = 0; i < 2; i++) {
                *(s32 *)(D_004D7E00 + i * 4 + 0x1C) = 0;
                *(s32 *)(D_004D7E00 + i * 4 + 0x24) = 0;
            }
            for (i = 0; i < 3; i++) {
                *(s32 *)(D_004D7E00 + i * 4 + 0x2C) = 0;
                *(s32 *)(D_004D7E00 + i * 4 + 0x38) = 0;
            }
            *D_004D7E00 = 1;
            t = *(s32 *)(self + 0x18);
            *D_004D7E02 = *(s16 *)(t + 4);
            *D_004D7E04 = *(s16 *)(t + 6);
            *D_004D7E08 = *(s16 *)(t + 0xC);
            *D_004D7E0A = *(s32 *)(t + 0x10);
            *D_004D7E06 = id;
            *D_004D7E0C = *(f32 *)(obj + 0x20);
            *D_004D7E10 = *(f32 *)(obj + 0x24);
            *D_004D7E14 = *(f32 *)(obj + 0x28);
            *D_004D7E18 = WrapAngle_13c050(D_0047D1FC + *(f32 *)(obj + 0x2C));
            *D_004D7E1C = 0x41E00000;
            *D_004D7E24 = 0xC1E00000;
            *D_004D7E20 = 0xC1E00000;
            *D_004D7E28 = 0xC1E00000;
            SetGameModePhase_1f59a0(300);
        }
        }
        }
        }
        return 1;
    case 300:
        ClearGameReqHold_1f5880();
        GameReqQueuePushWarp_1f5af0(*(s16 *)(*(s32 *)(self + 0x18) + 0xA), 0x320, 0, -1);
        GameReqQueuePushBack_1f5b50(5, -1);
        GameReqQueuePushWarp_1f5af0(*(s16 *)(*(s32 *)(self + 0x18) + 0xA), 0x321, 0, -1);
        TaskSetEnabled_27c2a0(1, D_00460588);
        TaskSetEnabled_27c2a0(1, D_00460C48);
        SetGameModePhase_1f59a0(0x12D);
        return 1;
    case 301:
        ScreenFadeIn_1cf740(ctx, 0xF);
        SetGameModePhase_1f59a0(200);
        return 1;
    case 200:
        SceneSoundMutePop_2f6670();
        ClearGameReqHold_1f5880();
        GameReqQueuePushBack_1f5b50(0, -1);
        TaskStatePopAll_27c250();
        return 1;
    }
    return 0;
}
