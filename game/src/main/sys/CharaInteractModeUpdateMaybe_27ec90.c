/* rgp:protos */
#define RGP_SELF_CharaInteractModeUpdateMaybe_27ec90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Phase driver of the SetGameModePhase_1f59a0 family.  Compare chain is 3, 1, 2, -1, so
   the source order is -1, 2, 1, 3 -- and the bodies are laid out in exactly
   that order (.L0027ED1C, .L0027EDE0, .L0027EF64, .L0027EF84).

   ★ EVERY exit materialises its own return value in its own delay slot (or,
   at .L0027F11C, in its own block), so by the pass-31 exit census they are
   all `return`s and none of them is a `break` sharing a tail.
   ★ The `slti $1, $2, 0x4` feeding a `bnez` lands in $at, so the source token
   is `> 3`, not `>= 4` -- see memory/at-compare-class.md.
   ★ D_004821D4 is a bitfield byte: bit 0 is read with `andi 1` and bits 1 and
   2 with `dsll32 30 / dsrl32 31` and `dsll32 29 / dsrl32 31`, i.e. 1-bit
   reads at positions 64-(n+32)-1.  The writes are the mwcc bitfield-INSERT
   path (`andi $3, $0, 1` is the constant 0 being inserted, `daddiu $3, $0, 4`
   the constant 1 at bit 2) -- memory/levers.d/main-bitfield-insert.md. */

struct Node {
    s16 m0;
    u8  pad2[0x36];
    f32 m38;
    f32 m3C;
    f32 m40;
};

struct Rec {
    s16 m0;
    s16 m2;
    s16 m4;
    s16 m6;
    s16 m8;
    u8  mA : 1;
    u8  mArest : 7;
    u8  padB;
    s32 mC;
    struct Node *m10;
};

struct Root {
    u8  pad0[0x34];
    struct Rec m34;
    u8  pad48[0xC];
    s32 m54;
};

struct TrackRec {
    u8   pad0[0x180];
    Vec4 m180;
};

struct Flags {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 rest : 5;
};

extern s16 D_004821D0;
extern s16 D_004821D2;
extern struct Flags D_004821D4;

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

s32 CharaInteractModeUpdateMaybe_27ec90(void)
{
    Vec4 mat __attribute__((aligned(16)));
    Vec4 wF0 __attribute__((aligned(16)));
    Vec4 wE0 __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 wC0 __attribute__((aligned(16)));
    Vec4 wB0 __attribute__((aligned(16)));
    u8   blkA[0x30] __attribute__((aligned(16)));
    u8   blkB[0x30] __attribute__((aligned(16)));
    s32  scene;
    s32  world;
    struct Root *root;
    struct Rec *obj;
    s32 h;
    s32 t;
    s32 sc2;
    struct TrackRec *rec;
    struct Node *node;

    GetGameData_1fede0();
    scene = GetCurrentScene_1f5be0();
    GetMapMgr_201a90();
    world = ((s32)GetActionMgr_1fdb50());
    root = ((struct Root *)GetGameData_1fede0());
    GetNpcObjTable_312860();
    GameReqQueueRemoveById_1f5a10(0xC);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        if (CharaInteractSetupMaybe_3eb790(root, GetCurrentScene_1f5be0(), D_004821D0, D_004821D2,
                         D_004821D4.b0, D_004821D4.b1, D_004821D4.b2) == 0) {
            GameReqQueuePushFront_1f5ab0(0, -1);
            return 0;
        }
        if (root->m34.m8 < 0) {
            GameReqQueuePushFront_1f5ab0(0, -1);
            return 0;
        }
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        TaskEnableCharaInteractSetMaybe_286d40();
        HudFadeOutAll_2f47e0(0xF);
        if (CharaInteractTalkTextRequest_3eb750(root) == 0) {
            SetGameModePhase_1f59a0(3);
            return 1;
        }
        SetGameModePhase_1f59a0(2);
        return 1;
    case 2:
        t = CharaInteractTalkTextPoll_3eb710(root);
        if (t == 2) {
            return 0;
        }
        if (t != 3) {
            SetGameModePhase_1f59a0(3);
            return 1;
        }
        obj = &root->m34;
        if (root->m54 == 0) {
            SetGameModePhase_1f59a0(3);
            return 1;
        }
        {
            SetInteractState_27a660(obj);
            h = ((s32)ActionMgrFindById_233b50(world, obj->m0));
            if (h != 0) {
                CharaSetFlags_212470(h, (long long)(0x04000000));
                rec = ((struct TrackRec *)ObjRecGetLiveObject_1c4a90(scene, obj->m2));
                if (rec != NULL) {
                    mat = rec->m180;
                    CharaGetPos_2388a0(h, &wF0);
                    VecSub_1cbd00(&wE0, &mat.x, &wF0);
                    CharaAddFlags_212460(h, (long long)(1));
                    CharaSetDirNormalizedMaybe_213b30(h, &wE0);
                } else if (obj->m4 == 2 && obj->mA) {
                    node = obj->m10;
                    if (node != NULL) {
                        pos.x = node->m38;
                        pos.y = node->m3C;
                        pos.z = node->m40;
                        CharaGetPos_2388a0(h, &wC0);
                        VecSub_1cbd00(&wB0, &pos.x, &wC0);
                        CharaAddFlags_212460(h, (long long)(1));
                        CharaSetDirNormalizedMaybe_213b30(h, &wB0);
                    }
                }
            }
            SetFieldControlActive_27bd30(0);
            CharaInteractRunAreaScriptMaybe_27a750(scene);
            TaskEnableEventCharaSetMaybe_286b10();
            HudFadeOutAll_2f47e0(0xA);
            GameSceneSetTimeScaleLockedMaybe_1ceb90(scene, 1);
            SetGameModePhase_1f59a0(1);
            return 0;
        }
    case 1:
        if (((unsigned char)GetFieldControlActive_27bd40()) != 0) {
            SetGameModePhase_1f59a0(3);
            return 1;
        }
        return 0;
    case 3:
        HudFadeInAll_2f4850(0xA);
        GameSceneSetTimeScaleLockedMaybe_1ceb90(scene, 0);
        D_004821D0 = -1;
        D_004821D2 = -1;
        D_004821D4.b0 = 0;
        D_004821D4.b1 = 0;
        D_004821D4.b2 = 1;
        SetFieldControlActive_27bd30(0);
        GameReqQueuePushBack_1f5b50(0, -1);
        ClearGameReqHold_1f5880();
        TaskStatePopAll_27c250();
        obj = &root->m34;
        if (obj == NULL) {
            return 1;
        }
        if (obj->m4 == 2 && obj->m10 != NULL) {
            sc2 = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(blkA);
            ActionPacketInitCharaInteractMaybe_3e2d80(blkA, sc2, obj->mC, obj->m10->m0, 0);
            EventFireTriggers_3e2660(blkA, 0);
        } else if (obj->m4 == 1) {
            sc2 = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(blkB);
            ActionPacketInitCharaPairMaybe_3e2e90(blkB, sc2, obj->mC, obj->m10, 0);
            EventFireTriggers_3e2660(blkB, 0);
        }
        h = ((s32)ActionMgrFindById_233b50(world, obj->m2));
        if (h != 0) {
            if (((unsigned char)CharaIsActionActive_215040(h)) != 0 || ((short)CharaGetActionMode_213850(h)) < 0 ||
                ((short)CharaGetActionMode_213850(h)) > 3) {
                CharaResetBattleStateMaybe_212f20(h, 0);
            }
        }
        return 1;
    }
    return 0;
}
