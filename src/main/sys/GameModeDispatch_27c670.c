#include "types.h"

extern void DrawCtxVif1HandlerStop_15dc40(void);
extern void TaskSetFlag_1f5750(void *, s32, s32);
extern void SetGameExitRequest_1f57d0(s32);
extern s32 GetGameExitRequest_1f57e0(void);
extern s32 GetGameReqHold_1f5870(void);
extern void GameModeStackPop_1f58a0(void);
extern void GameModeStackPush_1f58f0(s32, s32);
extern s32 GetGameModePhase_1f59b0(void);
extern s32 GetGameMode_1f59c0(void);
extern void GameReqQueuePeekWarp_1f5a40(void *);
extern s32 GetGameReqQueue_1f5bc0(void);
extern s32 ReturnZero_207f40(void);
extern void Nop_209f40(s32);
extern void GameReqListPopFront_20a0c0(s32);
extern s32 GameReqListPeek_20a1e0(s32, s32 *, s32 *);
extern void TaskStatePushAll_27c220(void);
extern void TaskStatePopAll_27c250(void);
extern s32 TaskRunAll_27c280(void);
extern void TaskSetEnabled_27c2a0(s32, void *);
extern u8 *TaskFind_27c2f0(void *);
extern s32 DebugActionModeUpdate_27ca30(void);
extern s32 TransporterMenuModeUpdate_27cc20(void);
extern s32 SpaceMenuModeUpdate_27d130(void);
extern s32 MainMenuModeUpdate_27d460(void);
extern s32 FactoryModeUpdate_27db40(void);
extern s32 InsectBattleModeUpdate_27e0d0(void);
extern s32 InsectMenuModeUpdate_27e610(void);
extern s32 TreasureBoxModeUpdate_27ea10(void);
extern s32 CharaInteractModeUpdateMaybe_27ec90(void);
extern s32 TransporterWarpModeUpdate_27f140(void);
extern s32 AbilityModeUpdate_27f810(void);
extern s32 AttackChainModeUpdate_27f840(void);
extern s32 BattleModeUpdate_280220(void);
extern s32 FieldExploreModeUpdate_2833a0(void);
extern s32 MapWarpModeUpdate_284060(void);
extern s32 DiscChangeModeUpdate_2850b0(void);
extern s32 LoadingModeUpdate_285450(void);
extern s32 GameStartModeUpdate_2858f0(void);
extern s32 GetPauseStep_2f6660(void);
extern s32 SaveIsBusy_376b00(void);
extern u8 D_0045FEB0[];
extern u8 D_0045FED0[];
extern u8 D_0045FF78[];
extern u8 D_0045FFC8[];
extern u8 D_00460608[];
extern s32 D_004821E0;

s32 GameModeDispatch_27c670(void) {
    s32 a;
    s32 b;
    s32 h;
    s32 r;
    u8 ok;
    u8 *p;
    u8 *e;

    if (GetGameExitRequest_1f57e0() != 0) {
        DrawCtxVif1HandlerStop_15dc40();
        return 0;
    }
    if (GetPauseStep_2f6660() == 0 || SaveIsBusy_376b00() != 0) {
        do {
            if (((ReturnZero_207f40() != 0) ^ 1) == 0) {
                break;
            }
            h = GetGameReqQueue_1f5bc0();
            Nop_209f40(h);
            if (GameReqListPeek_20a1e0(h, &a, &b) != 0) {
                ok = GetGameReqHold_1f5870();
                if (ok && a == 3 && GetGameMode_1f59c0() != 3) {
                    if (GetGameMode_1f59c0() != 7 || GetGameModePhase_1f59b0() >= 200) {
                        ok = 0;
                    }
                }
                if (!ok) {
                    switch (a) {
                    case 2:
                        SetGameExitRequest_1f57d0(1);
                        break;
                    case 0:
                        GameModeStackPop_1f58a0();
                        break;
                    case 11:
                        GameReqQueuePeekWarp_1f5a40(&D_004821E0);
                    default:
                        GameModeStackPush_1f58f0(a, b);
                        break;
                    }
                    GameReqListPopFront_20a0c0(h);
                }
            }
            r = 0;
            switch (GetGameMode_1f59c0()) {
            case 1: r = GameStartModeUpdate_2858f0(); break;
            case 3: r = LoadingModeUpdate_285450(); break;
            case 4: r = DiscChangeModeUpdate_2850b0(); break;
            case 5: r = MapWarpModeUpdate_284060(); break;
            case 6: r = FieldExploreModeUpdate_2833a0(); break;
            case 7: r = BattleModeUpdate_280220(); break;
            case 9: r = AttackChainModeUpdate_27f840(); break;
            case 10: r = AbilityModeUpdate_27f810(); break;
            case 11: r = TransporterWarpModeUpdate_27f140(); break;
            case 12: r = CharaInteractModeUpdateMaybe_27ec90(); break;
            case 13: r = TreasureBoxModeUpdate_27ea10(); break;
            case 14: r = InsectMenuModeUpdate_27e610(); break;
            case 15: r = InsectBattleModeUpdate_27e0d0(); break;
            case 16: r = FactoryModeUpdate_27db40(); break;
            case 17: r = MainMenuModeUpdate_27d460(); break;
            case 19: r = SpaceMenuModeUpdate_27d130(); break;
            case 20: r = TransporterMenuModeUpdate_27cc20(); break;
            case 21: r = DebugActionModeUpdate_27ca30(); break;
            }
        } while (r != 0);
    }
    if (GetPauseStep_2f6660() == 2 || GetPauseStep_2f6660() == 3) {
        if (SaveIsBusy_376b00() == 0) {
            TaskStatePushAll_27c220();
            TaskSetEnabled_27c2a0(0, D_0045FEB0);
            TaskSetEnabled_27c2a0(0, D_0045FED0);
            p = TaskFind_27c2f0(D_0045FF78);
            e = TaskFind_27c2f0(D_00460608);
            if (p != 0 && e != 0) {
                for (; p != e; p += 0x10) {
                    TaskSetFlag_1f5750(p, 0, 0);
                }
            }
            TaskSetEnabled_27c2a0(1, D_0045FFC8);
            r = (u8)TaskRunAll_27c280();
            TaskStatePopAll_27c250();
            return r;
        }
    }
    return TaskRunAll_27c280();
}
