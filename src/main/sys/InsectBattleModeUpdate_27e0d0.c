#include "types.h"
#pragma opt_lifetimes off

/* PARKED at 1 word short (333 of 334) -- NOT in config/cunits.txt.
   Residue: two branch-polarity tie-breaks (retail beql/beql where we get
   bne/bnel) plus the D_004D7E5x store block's scheduling.  MEASURED and
   rejected: writing the InsectBattleMatchUpdateMaybe_319800 guard in the positive form with the
   body nested is WORSE (331 words), and hoisting the compared value into a
   local changes nothing.

   Another phase driver of the FactoryModeUpdate_27db40 family: switch on the phase,
   guards spelled as early `return`s, one `return` per case.
   * Case ORDER is the compare chain backwards -- retail tests 104, 103, 102,
   101, 100, 1, 0, -1, so the source is -1, 0, 1, 100, 101, 102, 103, 104,
   with 100 FALLING THROUGH into 101 exactly as the block layout shows. */

extern const char D_004605C0[];
extern const char D_004605D8[];
extern const char D_00460D70[];
extern const char D_00460D78[];
extern const char D_00460D88[];

extern s32 D_00482270;

/* These live in .bss at 0x4D7E5x, far outside the +-32K gp window, and retail
   addresses each with its OWN %hi/%lo pair.  mwcc puts ANY <=4-byte extern in
   small data and emits %gp_rel; an INCOMPLETE array type has no size for it to
   test, so the relocation comes out %hi/%lo.  `const` -- the other documented
   switch for this -- is not available here, because these are written. */
extern s16 D_004D7E50[];
extern s32 D_004D7E58[];
extern const char *D_004D7E5C[];
extern const char *D_004D7E60[];
extern const char *D_004D7E64[];
extern const char *D_004D7E68[];
extern const char *D_004D7E6C[];

struct Ev;
struct Ev { u8 pad000[0x8]; s16 m08; s16 m0A; };
struct Sd;
struct Sd { s32 m00; s32 m04; s32 m08; };
struct Wc;
struct Wc { u8 pad000[0x1188]; struct Sd *m1188; };
struct Wo;
struct Wo { u8 pad000[0x24]; struct Wc *m24; };
struct Fl;
struct Fl { u8 pad000[0x4]; u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1; u8 b4 : 4; };

extern void OverlayLoad_1c3210(s32);
extern struct Ev *SysGetModeMsg_1c39b0(void);
extern s32  SysModeMsgIsInsMenu_1c6970(struct Ev *);
extern s32  LoaderCountQueued_1cd620(s32);
extern s32  ScreenFadeIsDone_1cf6c0(s32);
extern void ScreenFadeOutColor_1cf730(s32, s32, f32, f32, f32);
extern void ScreenFadeIn_1cf740(s32, s32);
extern void StreamMgrSetChanVolumeFade_1d63a0(s32, s32, s32, f32);
extern void StreamMgrPauseChan_1d6630(s32, s32);
extern void MapReleaseSlot3Area_1e2dc0(s32, s32);
extern void MapMgrLoadAreaSlot3_1e30c0(s32, s16 *, s32, s32);
extern s32  MapLoadIsSettledMaybe_1e4e10(s32, s32);
extern s32  MapGetAreaSlot2_1e5740(s32);
extern s32  MapDataGetState_1e7a00(s32);
extern void ClearGameReqHold_1f5880(void);
extern void SetGameReqHold_1f5890(void);
extern void SetGameModePhase_1f59a0(s32);
extern s32  GetGameModePhase_1f59b0(void);
extern s32  GetLoaderMgr_1f59d0(void);
extern void GameReqQueueRemoveById_1f5a10(s32);
extern s32  GameReqQueuePeekHead_1f5a70(s32);
extern void GameReqQueuePushFront_1f5ab0(s32, s32);
extern void GameReqQueuePushWarp_1f5af0(s16, s16, s32, s32);
extern s32  GetCurrentScene_1f5be0(void);
extern s32  GetActionMgr_1fdb50(void);
extern struct Wo *GetGameData_1fede0(void);
extern s32  GetMapMgr_201a90(void);
extern void BgmPlayTrackIfChangedMaybe_207880(s32, s32);
extern s32  GetStreamMgr_207ea0(void);
extern void TaskStatePushAll_27c220(void);
extern void TaskStatePopAll_27c250(void);
extern void TaskSetEnabled_27c2a0(s32, const char *);
extern void TaskSetupInsectBattle_2864d0(void);
extern void ClearPad2Enabled_2882a0(void);
extern void FieldModeResReleaseMaybe_2f35b0(void);
extern s32  InsectBattleMatchUpdateMaybe_319800(void);
extern void InsectBattleShutdown_31a230(void);
extern void InsectBattleInit_31a290(void);
extern struct Fl *RecordGetPayloadIfKind3D_430af0(struct Wc *, s32, s32);
/* called with 2 and 3 arguments -- UNPROTOTYPED in the source */
extern void RecordSetStateClamped_430db0();

s32 InsectBattleModeUpdate_27e0d0(void)
{
    struct Wo *w;
    struct Wc *wc;
    struct Sd *sd;
    struct Fl *fl;
    struct Ev *ev;
    s32 scene;
    s32 world;
    s32 snd;
    s32 kind;
    s32 sub;
    s32 id;
    s32 next;
    s32 msg;
    u8 bits;

    w = GetGameData_1fede0();
    scene = GetCurrentScene_1f5be0();
    world = GetMapMgr_201a90();
    GetActionMgr_1fdb50();
    GameReqQueueRemoveById_1f5a10(0xF);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        TaskSetupInsectBattle_2864d0();
        FieldModeResReleaseMaybe_2f35b0();
        TaskSetEnabled_27c2a0(0, D_004605C0);
        TaskSetEnabled_27c2a0(0, D_004605D8);
        snd = GetStreamMgr_207ea0();
        BgmPlayTrackIfChangedMaybe_207880(0, 1);
        StreamMgrPauseChan_1d6630(snd, 1);
        StreamMgrPauseChan_1d6630(snd, 2);
        SetGameModePhase_1f59a0(0);
        return 0;
    case 0:
        if (LoaderCountQueued_1cd620(GetLoaderMgr_1f59d0()) > 0) {
            return 0;
        }
        OverlayLoad_1c3210(5);
        InsectBattleInit_31a290();
        D_004D7E50[0] = 0x7D0;
        D_004D7E58[0] = 0;
        D_004D7E5C[0] = D_00460D70;
        D_004D7E60[0] = D_00460D78;
        D_004D7E64[0] = D_00460D88;
        D_004D7E68[0] = D_00460D70;
        D_004D7E6C[0] = D_00460D70;
        MapMgrLoadAreaSlot3_1e30c0(world, D_004D7E50, 3, 0x8000);
        SetGameModePhase_1f59a0(1);
        return 0;
    case 1:
        next = MapGetAreaSlot2_1e5740(world);
        if (next != 0 && MapDataGetState_1e7a00(next) == 1) {
            return 0;
        }
        SetGameModePhase_1f59a0(0x64);
        return 0;
    case 100:
        SetGameModePhase_1f59a0(0x65);
        /* fallthrough */
    case 101:
        switch (GameReqQueuePeekHead_1f5a70(0)) {
        case 0xB:
            SetGameModePhase_1f59a0(0x64);
            ClearGameReqHold_1f5880();
            return 1;
        }
        if (InsectBattleMatchUpdateMaybe_319800() != 0) {
            SetGameModePhase_1f59a0(0x66);
            ScreenFadeOutColor_1cf730(scene, 0x1E, 0.0f, 0.0f, 0.0f);
            snd = GetStreamMgr_207ea0();
            StreamMgrSetChanVolumeFade_1d63a0(snd, 0, 0x1E, 0.0f);
            StreamMgrSetChanVolumeFade_1d63a0(snd, 1, 0x1E, 0.0f);
            StreamMgrSetChanVolumeFade_1d63a0(snd, 2, 0x1E, 0.0f);
            return 1;
        }
        return 0;
    case 102:
        if (ScreenFadeIsDone_1cf6c0(scene) == 0) {
            return 0;
        }
        MapReleaseSlot3Area_1e2dc0(world, 1);
        InsectBattleShutdown_31a230();
        snd = GetStreamMgr_207ea0();
        StreamMgrPauseChan_1d6630(snd, 0);
        StreamMgrPauseChan_1d6630(snd, 1);
        StreamMgrPauseChan_1d6630(snd, 2);
        SetGameModePhase_1f59a0(0x67);
        return 0;
    case 103:
        if (MapLoadIsSettledMaybe_1e4e10(world, 0) == 0) {
            return 0;
        }
        if (LoaderCountQueued_1cd620(GetLoaderMgr_1f59d0()) > 0) {
            return 0;
        }
        if (!(SysModeMsgIsInsMenu_1c6970(SysGetModeMsg_1c39b0()) == 0)) {
            OverlayLoad_1c3210(6);
        } else {
            OverlayLoad_1c3210(3);
        }
        ClearPad2Enabled_2882a0();
        TaskStatePopAll_27c250();
        D_00482270 = 0;
        SetGameModePhase_1f59a0(0x68);
        return 0;
    case 104:
        D_00482270 = D_00482270 + 1;
        if (D_00482270 < 0x1E) {
            return 0;
        }
        ClearGameReqHold_1f5880();
        GameReqQueuePushFront_1f5ab0(0, -1);
        ev = SysGetModeMsg_1c39b0();
        if (SysModeMsgIsInsMenu_1c6970(ev) != 0) {
            wc = w->m24;
            sd = wc->m1188;
            kind = sd->m00;
            sub = sd->m04;
            id = sd->m08;
            if (kind == 3) {
                if (id == 0x131) {
                    RecordSetStateClamped_430db0(wc, 0x132, kind);
                }
            } else if (kind == 4) {
                if (id == 0x194) {
                    RecordSetStateClamped_430db0(wc, 0x195, kind);
                }
            } else if (kind == 5) {
                if (id == 0x1F8) {
                    RecordSetStateClamped_430db0(wc, 0x1F9, kind);
                }
            } else if (kind == 6) {
                if (sub == 0x3D && id == 0x266) {
                    fl = RecordGetPayloadIfKind3D_430af0(wc, sub, kind);
                    msg = 0x263;
                    if (fl != 0) {
                        if (fl->b2) {
                            fl->b3 = 1;
                            msg = 0x267;
                        }
                    }
                    RecordSetStateClamped_430db0(w->m24, msg);
                }
            }
            GameReqQueuePushWarp_1f5af0(ev->m08, ev->m0A, 0, -1);
            return 0;
        }
        ScreenFadeIn_1cf740(scene, 0xF);
        return 0;
    }
    return 0;
}
