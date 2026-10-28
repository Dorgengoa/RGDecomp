/* rgp:protos */
#define RGP_SELF_TransporterWarpModeUpdate_27f140 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Phase driver of the SetGameModePhase_1f59a0 family, dispatched through a JUMP TABLE
   (jtbl_00460D90, six entries; "addiu $2, $2, 1" + "sltiu $1, $2, 6", so the
   cases are -1..4).  For a table switch the case order lives in the TABLE and
   the physical block order IS the source order -- table entries 0..5 are
   -1, 0, 1, 2, 3, 4 while the blocks run .L0027F1B4(-1), .L0027F4DC(1),
   .L0027F518(0), .L0027F620(2), .L0027F684(3), .L0027F6F8(4), so the source
   order is -1, 1, 0, 2, 3, 4.  The unit's own .rodata takes the table's
   address -- config/crodata.txt, memory/levers.d/main-rodata-slot.md.

   Two compares land in $at and both are the documented shape: "slt $1,$3,$2"
   under "if (used < size)" and "slti $1, $16, 0xC" under "if (t < 0xC)" --
   a strict < consumed by a beqz is $at, see memory/at-compare-class.md.

   Every guard is written so that RETAIL'S FALL-THROUGH is the if body: that
   is the lever, not "early return" as such.  See CharaInteractModeUpdateMaybe_27ec90 in this dir. */

struct Ent {
    s16 m0;
    u8  pad2[0x12];
    s16 m14;
};

struct Actor {
    u8  pad0[0x30];
    s16 m30;
};

struct Root {
    u8  pad0[0x10];
    s32 m10;
    u8  pad14[4];
    struct Actor *m18;
    u8  pad1C[4];
    s32 m20;
};

struct World {
    u8  pad0[0x60];
    s32 m60;
};

extern char D_0045FED0[];
extern char D_004600C8[];
extern char D_00460720[];

extern f32 D_0047EA30;
extern f32 D_0047EA34;
extern f32 D_0047EA38;
extern f32 D_0047EA3C;

extern s32 D_004821E0;
extern s16 D_004821E4;
extern s16 D_004821E6;

extern u8 D_004B2570[];

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

s32 TransporterWarpModeUpdate_27f140(void)
{
    u8   mtx[0x40] __attribute__((aligned(16)));
    Vec4 v __attribute__((aligned(16)));
    struct Root *root;
    s32 scene;
    struct World *world;
    s32 mgr;
    struct Ent *ev;
    s32 id;
    s32 h;
    s32 used;
    s32 size;
    s32 obj;
    s32 pose;
    s32 i;
    s32 rec;
    s32 cnt;
    s32 t;
    s32 node;
    s32 mode;

    root = ((struct Root *)GetGameData_1fede0());
    scene = GetCurrentScene_1f5be0();
    world = ((struct World *)GetMapMgr_201a90());
    mgr = ((s32)GetActionMgr_1fdb50());
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        SetGameReqHold_1f5890();
        GameReqQueueRemoveById_1f5a10(0x11);
        GameReqQueueRemoveById_1f5a10(0x14);
        GameReqQueueRemoveById_1f5a10(0x13);
        GameReqQueueRemoveById_1f5a10(8);
        GameReqQueueRemoveById_1f5a10(9);
        StateFlagSet_3ccb70(root->m10, 0x143, 0, 1);
        TaskStatePushAll_27c220();
        TaskEnableEventSceneSetMaybe_286f40();
        TaskSetEnabled_27c2a0(1, D_00460720);
        TaskSetEnabled_27c2a0(0, D_0045FED0);
        ev = ((struct Ent *)SysGetModeMsg_1c39b0());
        if (ev != NULL && ev->m0 == 6) {
            TransporterWarpFlagSet_27a940();
        }
        if (((unsigned char)CharaSysStateField28ValidRelated_3a3920(root->m20)) != 0 && FieldViewModeGet_2f35a0() != 2) {
            FieldViewModeActivateEncounterMaybe_2f3400();
        }
        if (ev != NULL && ev->m0 == 6 && ev->m14 > 0) {
            id = RecStackPush_1c4240(scene, 0);
            h = ((s32)RecStackGetSlot_1c4330(scene, id));
            if (h != 0) {
                size = MemStackGetFree_1c6d50(h);
                used = ev->m14 << 6;
                if (used < size) {
                    MemStackAllocQw_14d950(h, size - used);
                } else {
                    RecStackPop_1c4140(scene, id);
                }
            }
        }
        StateFlagSet_3ccb70(root->m10, 0x145, 0, 1);
        StateFlagSet_3ccb70(root->m10, 0x7E2, 0, 1);
        EventPendingPacketClear_3e25e0();
        CharaSysEventLogKeysClear_3a3350(root->m20);
        SetFieldControlActive_27bd30(0);
        MapAreaScriptRun_27a9e0(scene, D_004821E0, D_004821E4);
        if (((unsigned char)GetFieldControlActive_27bd40()) != 0) {
            SetFieldControlActive_27bd30(1);
            ClearGameReqHold_1f5880();
            SetGameModePhase_1f59a0(4);
            return 1;
        }
        if (D_004821E0 == 0x321) {
            obj = MapSlotsFindActiveBlockById_1e4730(world, root->m18->m30, 0);
            if (obj != 0 && ((unsigned char)MapDataIsJasterOnly_1e7a90(obj)) != 0) {
                pose = MapGetAreaSlot1_1e5750(world);
                if (pose != 0 && ((unsigned char)MapDataIsLoaded_1e79d0(pose)) != 0) {
                    v.x = D_0047EA30;
                    v.y = D_0047EA34;
                    v.z = D_0047EA38;
                    v.w = D_0047EA3C;
                    MapDataGetMatrix_1e7670(pose, mtx);
                    MatMulPoint_1cb8e0(&v, mtx, &v);
                    cnt = PartyCountMembers_3c2010(root->m18, 1, 1);
                    cnt = (s32)(u32)cnt;
                    for (i = 0; i < cnt; i++) {
                        t = ((short)PartyGetMemberId_3c2490(root->m18, i));
                        if (t != 0 && t >= 0 && t < 0xC) {
                            rec = ((s32)ObjRecGetLiveObject_1c4a90(scene, t));
                            if (rec != 0) {
                                node = ((s32)ActionMgrFindById_233b50(mgr, t));
                                if (node != 0) {
                                    CharaSetPos_213a40(node, &v);
                                    ModelSetPos_151110(rec, &v);
                                }
                            }
                        }
                    }
                }
            }
        }
        GameSceneSetTimeScaleLockedMaybe_1ceb90(scene, 1);
        SetFieldControlActive_27bd30(0);
        SetGameModePhase_1f59a0(1);
        return 1;
    case 1:
        if (D_004821E6 <= 0) {
            world->m60 |= 8;
            SetGameModePhase_1f59a0(0);
            LoadingIconSetEnabled_2ee910(1);
            return 1;
        }
        D_004821E6 = D_004821E6 - 1;
        return 0;
    case 0:
        if (((unsigned char)GetFieldControlActive_27bd40()) == 0) {
            return 0;
        }
        TaskSetEnabled_27c2a0(0, D_004600C8);
        if (StateFlagTest_3ccd70(root->m10, 0x7F0) != 0) {
            StateFlagSet_3ccb70(root->m10, 0x7F2, 0, 1);
            StateFlagSet_3ccb70(root->m10, 0x7F0, 0, 1);
            StateFlagSet_3ccb70(root->m10, 0x7E2, 0, 1);
            SetGameModePhase_1f59a0(3);
            return 1;
        }
        if (StateFlagTest_3ccd70(root->m10, 0x7F2) != 0) {
            StateFlagSet_3ccb70(root->m10, 0x7F2, 0, 1);
            if (((unsigned char)MapLoadIsSettledMaybe_1e4e10(world, 0)) == 0) {
                ScreenFadeOutColor_1cf730(scene, 0, 0.0f, 0.0f, 0.0f);
                SetGameModePhase_1f59a0(2);
            } else {
                SetGameModePhase_1f59a0(4);
            }
        } else {
            SetGameModePhase_1f59a0(4);
        }
        return 1;
    case 2:
        if (((unsigned char)MapLoadIsSettledMaybe_1e4e10(world, 0)) == 0) {
            return 0;
        }
        if (StateFlagTest_3ccd70(root->m10, 0x7E7) != 0) {
            StateFlagSet_3ccb70(root->m10, 0x7E7, 0, 1);
        } else {
            ScreenFadeIn_1cf740(scene, 0xF);
        }
        SetGameModePhase_1f59a0(4);
        return 1;
    case 3:
        if (LoaderCountQueued_1cd620(((s32)GetLoaderMgr_1f59d0())) > 0) {
            return 0;
        }
        if (((unsigned char)MapLoadIsSettledMaybe_1e4e10(world, 0)) == 0) {
            return 0;
        }
        if (((unsigned char)ScreenFadeIsFadingOut_1cf670(scene)) != 0) {
            return 0;
        }
        ScreenFadeIn_1cf740(scene, 0xF);
        ScreenFadeSetDelay_1cf6f0(scene, 2);
        SetGameModePhase_1f59a0(4);
        return 1;
    case 4:
        mode = GameReqQueuePeekHead_1f5a70(0);
        if (mode != 0xF && mode != 2 && mode != -1) {
            ClearGameReqHold_1f5880();
            return 0;
        }
        GameReqQueuePushFront_1f5ab0(0, -1);
        GameDataResetSpotState_3eb690(root);
        FieldHudReshowMaybe_202d70();
        world->m60 &= ~8;
        GameSceneSetTimeScaleLockedMaybe_1ceb90(scene, 0);
        PadUpdateVibration_184250(D_004B2570, 0);
        PadUpdate_1843a0(D_004B2570);
        ClearGameReqHold_1f5880();
        SetFieldControlActive_27bd30(0);
        TaskStatePopAll_27c250();
        if (GetGameModeAt_1f5830(1) == 7) {
            if (GetGameModePhaseAt_1f57f0(1) == 2) {
                TaskStatePopAll_27c250();
            }
        }
        return 1;
    }
    return 0;
}
