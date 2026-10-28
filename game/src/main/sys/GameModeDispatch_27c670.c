/* rgp:protos */
#define RGP_SELF_GameModeDispatch_27c670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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

    if (((unsigned char)GetGameExitRequest_1f57e0()) != 0) {
        DrawCtxVif1HandlerStop_15dc40();
        return 0;
    }
    if (GetPauseStep_2f6660() == 0 || ((unsigned char)SaveIsBusy_376b00()) != 0) {
        do {
            if (((ReturnZero_207f40() != 0) ^ 1) == 0) {
                break;
            }
            h = ((s32)GetGameReqQueue_1f5bc0());
            Nop_209f40();
            if (GameReqListPeek_20a1e0(h, &a, &b) != 0) {
                ok = ((unsigned char)GetGameReqHold_1f5870());
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
        if (((unsigned char)SaveIsBusy_376b00()) == 0) {
            TaskStatePushAll_27c220();
            TaskSetEnabled_27c2a0(0, D_0045FEB0);
            TaskSetEnabled_27c2a0(0, D_0045FED0);
            p = ((u8 *)TaskFind_27c2f0(D_0045FF78));
            e = ((u8 *)TaskFind_27c2f0(D_00460608));
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
