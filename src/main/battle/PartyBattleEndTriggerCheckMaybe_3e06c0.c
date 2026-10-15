#include "types.h"

typedef struct S00483990 { u8 pad0[0x18]; s32 unk18; } S00483990;
extern s32 StreamMgrChanGetStatus_1d65f0(s32 arg0, s32 arg1);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetStreamMgr_207ea0(void);
extern s32 PartyCountMembers_3c2010(s32 arg0, s32 arg1, s32 arg2);
extern s32 PartyGetNonLeaderChara_3c2700(s32 arg0, s32 arg1);
extern s32 PartyGetLeaderChara_3c2820(s32 arg0);
extern s32 SkillTriggerEvalMaybe_3e1200(void *arg0, s32 arg1);
extern void ActionPacketInitBattleEnd_3e3550(void *arg0, s32 arg1, s32 arg2);
extern void ActionPacketReset_3e3d00(void *arg0);
extern void SkillLockSetResetSpot_3eb6f0(void *arg0, s32 arg1);
extern S00483990 *D_00483990;
extern s32 D_004839B4;

s32 PartyBattleEndTriggerCheckMaybe_3e06c0(s32 arg0, s32 arg1)
{
    s32 arr[4];
    u8 sp40[0x30];
    s32 m;
    s32 n;
    s32 t;
    s32 r;
    u8 f;
    s32 i;

    if (D_00483990 == NULL) {
        return 0;
    }
    f = 0;
    if (arg0 != 0) {
        t = GetStreamMgr_207ea0();
        if (t != 0 && StreamMgrChanGetStatus_1d65f0(t, 1) == 1) {
            f = 1 & 0xFF;
        }
    }
    if (D_004839B4 > 0) {
        D_004839B4 -= 1;
        f = 1;
    }
    if (f) {
        return 0;
    }
    m = GetCurrentScene_1f5be0();
    ActionPacketReset_3e3d00(sp40);
    ActionPacketInitBattleEnd_3e3550(sp40, m, 1);
    n = PartyCountMembers_3c2010(D_00483990->unk18, 1, 1);
    arr[0] = PartyGetLeaderChara_3c2820(D_00483990->unk18);
    for (i = 1; i < n; i++) {
        arr[i] = PartyGetNonLeaderChara_3c2700(D_00483990->unk18, i - 1);
    }
    for (i = 0; i < n; i++) {
        if (arr[i] != 0 && (SkillTriggerEvalMaybe_3e1200(sp40, arr[i]) & 0xFF)) {
            if (arg1 != 0) {
                SkillLockSetResetSpot_3eb6f0(D_00483990, 1);
            }
            return 1;
        }
    }
    return 0;
}
