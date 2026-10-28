/* rgp:protos */
#define RGP_SELF_ScriptEmitCmdHandlerMaybe_3da110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem {
    u8 pad0[0x10];
    void *fn;
    u8 pad14[4];
    s64 arg;
    u8 pad20[0x10];
    s16 h30;
    u8 pad32[6];
} Elem;
typedef struct Obj { u8 pad[0xE0A]; s16 hE0A; } Obj;

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

u8 *ScriptEmitCmdHandlerMaybe_3da110(Obj *o, s32 kind, s32 unused, u8 *cmd)
{
    Elem e __attribute__((aligned(16)));
    s32 r;
    s32 c;

    if (cmd == 0) {
        return 0;
    }
    VariantInit_36ff00(&e);
    e.h30 = o->hE0A;
    c = *cmd;
    switch (kind) {
    case 3:
        switch (c) {
        case 1:
            e.arg = 0;
            e.fn = (void *)ScriptFnInvAddItem_3d9a80;
            break;
        case 2:
            e.arg = 0;
            e.fn = (void *)ScriptFnConsumeItem_3d9950;
            break;
        case 3:
            e.arg = 0;
            e.fn = (void *)ScriptFnCharaEquip_3d9680;
            break;
        case 14:
            e.arg = 0;
            e.fn = (void *)ScriptFnEncounterBindMaybe_3d9460;
            break;
        case 4:
            e.arg = 0;
            e.fn = (void *)ScriptFnRequestBattle_3d9380;
            break;
        case 12:
            e.arg = 0;
            e.fn = (void *)ScriptFnBattleEnd_3d9150;
            break;
        case 13:
            e.arg = 0;
            e.fn = (void *)ScriptFnBattleEndCode2_3d90f0;
            break;
        case 33:
            e.arg = 0;
            e.fn = (void *)ScriptFnBattleEndCode4_3d9080;
            break;
        case 15:
            e.arg = 0;
            e.fn = (void *)ScriptFnCharaSysQueueEncounter_3d92d0;
            break;
        case 16:
            e.arg = 0;
            e.fn = (void *)ScriptFnCharaSysQueueEncounterById_3d9210;
            break;
        case 5:
            e.arg = 0;
            e.fn = (void *)ScriptFnTransporterWarp_3d8e00;
            break;
        case 6:
            e.arg = 0;
            e.fn = (void *)ScriptFnProgressSetByCode_3d8d30;
            break;
        case 7:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartyAddMember_3d8c20;
            break;
        case 8:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartyRemoveMember_3d8b10;
            break;
        case 9:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartySetLeader_3d89f0;
            break;
        case 10:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartyJoin_3d8800;
            break;
        case 11:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartyMoveToReserve_3d8710;
            break;
        case 26:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartySwapByKind_3d8580;
            break;
        case 17:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartySetActiveCount_3d84d0;
            break;
        case 21:
            e.arg = 0;
            e.fn = (void *)ScriptFnCharaSetFlag234Related_3d83e0;
            break;
        case 34:
            e.arg = 0;
            e.fn = (void *)ScriptFnCharaSetPartyLockedMaybe_3d82e0;
            break;
        case 35:
            e.arg = 0;
            e.fn = (void *)ScriptFnCharaSetAltFormFlagMaybe_3d81e0;
            break;
        case 36:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartyRefreshMembersMaybe_3d8190;
            break;
        case 24:
            e.arg = 0;
            e.fn = (void *)ScriptFnSpawnObj_3d8000;
            break;
        case 23:
            e.arg = 0;
            e.fn = (void *)ScriptFnCharaUnload_3d7f00;
            break;
        case 18:
            e.arg = 0;
            e.fn = (void *)ScriptFnPlaceUnitByEncounterSlotMaybe_3d7da0;
            break;
        case 19:
            e.arg = 0;
            e.fn = (void *)ScriptFnMapWarpRequest_3d7c30;
            break;
        case 20:
            e.arg = 0;
            e.fn = (void *)ScriptFnMapCaptionLoad_3d7b10;
            break;
        case 22:
            e.arg = 0;
            e.fn = (void *)ScriptFnShopSetIdMaybe_3d7a40;
            break;
        case 25:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartyReviveAll_3d7930;
            break;
        case 27:
            e.arg = 0;
            e.fn = (void *)ScriptFnMapMarkerSetAddMaybe_3d7870;
            break;
        case 28:
            e.arg = 0;
            e.fn = (void *)ScriptFnMapMarkerSetRemoveMaybe_3d77c0;
            break;
        case 29:
            e.arg = 0;
            e.fn = (void *)ScriptFnPushLoadingMode_3d7740;
            break;
        case 31:
            e.arg = 0;
            e.fn = (void *)ScriptFnIsSysReady_3d76d0;
            break;
        case 30:
            e.arg = 0;
            e.fn = (void *)ScriptFnSysMsgExitMaybe_3d75d0;
            break;
        case 46:
            e.arg = 0;
            e.fn = (void *)ScriptFnSetStateVar79Related_3d7540;
            break;
        case 37:
            e.arg = 0;
            e.fn = (void *)ScriptFnPushInsectBattleMode_3d74c0;
            break;
        case 38:
            e.arg = 0;
            e.fn = (void *)ScriptFnSpawnChrMonographs_3d73d0;
            break;
        case 39:
            e.arg = 0;
            e.fn = (void *)ScriptFnObjSetCanDie_3d7260;
            break;
        case 40:
            e.arg = 0;
            e.fn = (void *)ScriptFnObjHpRaiseToPercent_3d7160;
            break;
        case 41:
            e.arg = 0;
            e.fn = (void *)ScriptFnPendingWarpSet_3d7050;
            break;
        case 42:
            e.arg = 0;
            e.fn = (void *)ScriptFnInvSpecialItemRestoreMaybe_3d6fd0;
            break;
        case 43:
            e.arg = 0;
            e.fn = (void *)ScriptFnStateVarIncrementMaybe_3d6f00;
            break;
        case 44:
            e.arg = 0;
            e.fn = (void *)ScriptFnObjRollClearStatusFxA_3d6e20;
            break;
        case 45:
            e.arg = 0;
            e.fn = (void *)ScriptFnBossGaugeRebuild_3d6da0;
            break;
        case 47:
            e.arg = 0;
            e.fn = (void *)ScriptFnResetRandomLayoutFlagsMaybe_3d6cf0;
            break;
        case 48:
            e.arg = 0;
            e.fn = (void *)ScriptFnMapApplySaveStateMaybe_3d6c70;
            break;
        case 49:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartyScriptFlagSetMaybe_3d6bc0;
            break;
        case 51:
            e.arg = 0;
            e.fn = (void *)ScriptFnEventTimerSet_3d6ae0;
            break;
        case 52:
            e.arg = 0;
            e.fn = (void *)ScriptFnStatusClearAllActors_3d6a50;
            break;
        case 53:
            e.arg = 0;
            e.fn = (void *)ScriptFnCharaSetCannotLeadMaybe_3d6960;
            break;
        case 54:
            e.arg = 0;
            e.fn = (void *)ScriptFnOptionsSetTacticsMode_3d68b0;
            break;
        case 55:
            e.arg = 0;
            e.fn = (void *)ScriptFnCharaSetLevel_3d6790;
            break;
        case 56:
            e.arg = 0;
            e.fn = (void *)ScriptFnPendingWarpCancel_3d6720;
            break;
        }
        break;
    case 4:
        switch (c) {
        case 1:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d6710;
            break;
        case 2:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d6700;
            break;
        case 3:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d66f0;
            break;
        case 4:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d66e0;
            break;
        case 5:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d66d0;
            break;
        case 6:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d66c0;
            break;
        case 7:
            e.arg = 0;
            e.fn = (void *)ScriptFnPartyInZoneMaybe_3d6510;
            break;
        case 8:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d6500;
            break;
        case 9:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d64f0;
            break;
        case 10:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d64e0;
            break;
        case 11:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d64d0;
            break;
        case 12:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d64c0;
            break;
        case 13:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d64b0;
            break;
        case 14:
            e.arg = 0;
            e.fn = (void *)ScriptFnNop_3d64a0;
            break;
        }
        break;
    }
    r = ((s32)VariantPoolAlloc_3da080(o, 0));
    if (r != 0) {
        VariantRecCopy_36ee10(r, &e);
    }
    return cmd + 1;
}
