#include "types.h"
#include "vec.h"

/* Phase driver of the SetGameModePhase_1f59a0 family.  Case order is the compare chain
   backwards -- retail tests 0xCA, 0xC9, 0xC8, 0x64, 0, -1, so the source
   order is -1, 0, 100, 200, 201, 202, and the bodies appear in that order.

   ⚠ case 0 really does FALL THROUGH into case 100: its block ends with
   `jal SetGameModePhase_1f59a0` and no branch, running straight into .L0027EB38.
   Everywhere else the family rule holds -- each guard is an early `return`
   and each exit materialises its own value in a `b epilogue` delay slot. */

struct Sub18 {
    u8 pad0[0x18E];
    s16 m18E;
};

struct Root {
    u8 pad0[0x18];
    struct Sub18 *m18;
};

struct TrackRec {
    u8 pad0[0x180];
    Vec4 m180;
    Vec4 m190;
};

extern s32 D_004821D8;

extern s32  ObjRecHasFlags6_1c3eb0(s32, s32, s32);
extern void GameSceneSetTimeScaleLockedMaybe_1ceb90(s32, s32);
extern void ClearGameReqHold_1f5880(void);
extern void SetGameReqHold_1f5890(void);
extern void SetGameModePhase_1f59a0(s32);
extern s32  GetGameModePhase_1f59b0(void);
extern void GameReqQueueRemoveById_1f5a10(s32);
extern s32  GameReqQueuePeekHead_1f5a70(s32);
extern void GameReqQueuePushFront_1f5ab0(s32, s32);
extern s32  GetCurrentScene_1f5be0(void);
extern s32  GetActionMgr_1fdb50(void);
extern struct Root *GetGameData_1fede0(void);
extern s32  GetMapMgr_201a90(void);
extern void CharaClearFlags_2124a0(s32);
extern void CharaResetBattleStateMaybe_212f20(s32, s32);
extern void CharaSetYaw_2138f0(s32, f32);
extern void CharaSetPos_213a40(s32, Vec4 *);
extern void CharaRequestBattleEnter_213ec0(s32, s32);
extern s32  CharaGetId_214a80(s32);
extern s32  ActionMgrFindById_233b50(s32, s16);
extern void CharaSetVelocity_238770(s32, f32, f32, f32);
extern void TreasureBoxRunAreaScript_278cb0(s32);
extern void SetFieldControlActive_27bd30(s32);
extern s32  GetFieldControlActive_27bd40(void);
extern void TaskStatePushAll_27c220(void);
extern void TaskStatePopAll_27c250(void);
extern void TaskSetupTreasureBoxMode_286850(void);
extern s32  GetTreasureBoxPool_3389b0(void);
extern s32  TreasureBoxPoolFindById_339150(s32, s32);
extern void TreasureBoxStartEncounter_33a6e0(s32);
extern struct TrackRec *ObjRecGetLiveObject_1c4a90(s32, s32);

s32 TreasureBoxModeUpdate_27ea10(void)
{
    Vec4 rot;
    Vec4 pos;
    struct Root *root;
    struct TrackRec *rec;
    s32 scene;
    s32 world;
    s32 obj;
    s32 h;

    root = GetGameData_1fede0();
    scene = GetCurrentScene_1f5be0();
    GetMapMgr_201a90();
    world = GetActionMgr_1fdb50();
    h = GetTreasureBoxPool_3389b0();
    obj = ActionMgrFindById_233b50(world, root->m18->m18E);
    GameReqQueueRemoveById_1f5a10(0xD);
    h = TreasureBoxPoolFindById_339150(h, D_004821D8);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        TaskStatePushAll_27c220();
        TaskSetupTreasureBoxMode_286850();
        if (h == 0) {
            SetGameModePhase_1f59a0(0xC8);
            return 1;
        }
        SetGameReqHold_1f5890();
        CharaClearFlags_2124a0(obj);
        TreasureBoxStartEncounter_33a6e0(h);
        SetFieldControlActive_27bd30(0);
        SetGameModePhase_1f59a0(0);
        return 1;
    case 0:
        GameSceneSetTimeScaleLockedMaybe_1ceb90(scene, 1);
        TreasureBoxRunAreaScript_278cb0(scene);
        SetGameModePhase_1f59a0(0x64);
    case 100:
        if (GetFieldControlActive_27bd40() != 0) {
            SetGameModePhase_1f59a0(0xC8);
            return 1;
        }
        return 0;
    case 200:
        rec = ObjRecGetLiveObject_1c4a90(scene, CharaGetId_214a80(obj));
        if (rec != 0) {
            /* ★ The qword copies are written THROUGH u128, not as Vec4
               assignments.  Both emit one lq/sq per row, but only the u128
               form materialises `daddu $4, $17, $0` BEFORE
               `addiu $5, $29, 0x40`, which is retail's order -- a plain
               `pos = rec->m180` reverses the two argument setups and is two
               wrong words.  Six spellings measured in build/pt/probe3.c. */
            *(u128 *)&pos = *(u128 *)&rec->m180;
            *(u128 *)&rot = *(u128 *)&rec->m190;
            CharaSetPos_213a40(obj, &pos);
            CharaSetYaw_2138f0(obj, rot.y);
        }
        CharaSetVelocity_238770(obj, 0.0f, 0.0f, 0.0f);
        CharaResetBattleStateMaybe_212f20(obj, 0);
        GameSceneSetTimeScaleLockedMaybe_1ceb90(scene, 0);
        SetFieldControlActive_27bd30(0);
        TaskStatePopAll_27c250();
        if (GameReqQueuePeekHead_1f5a70(0) != 7) {
            D_004821D8 = -1;
            GameReqQueuePushFront_1f5ab0(0, -1);
            ClearGameReqHold_1f5880();
            return 1;
        }
        CharaRequestBattleEnter_213ec0(obj, 0);
        SetGameModePhase_1f59a0(0xC9);
        return 1;
    case 201:
        if (ObjRecHasFlags6_1c3eb0(scene, 1, 0x80) == 0) {
            return 0;
        }
        D_004821D8 = -1;
        ClearGameReqHold_1f5880();
        SetGameModePhase_1f59a0(0xCA);
        return 1;
    case 202:
        GameReqQueuePushFront_1f5ab0(0, -1);
        ClearGameReqHold_1f5880();
        return 1;
    }
    return 0;
}
