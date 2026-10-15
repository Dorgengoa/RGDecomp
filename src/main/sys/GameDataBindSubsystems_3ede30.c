/* MATCH (s41m). Stale pre-match note follows -- PARKED: 1 round trip: long call-chain teardown function; length 0x1D8 vs retail 0x1D4 (very close, 1 word). */
#include "types.h"

extern void PadWaitReady_1849e0(void *);
extern void EquipSlotSetGameData_3a0930(void *);
extern void CharaSysSetGameData_3a5d10(s32, void *);
extern void CharaEventLogSetGameData_3a6a20(void *);
extern void CharaEventLogFormatSetGameData_3a6c40(void *);
extern void CharaRecSetGameData_3a6e70(void *);
extern void ExecInfoSetGameData_3a7980(void *);
extern void CharaMgrPoolSetGameData_3a9290(s32, void *);
extern void UnitSetGameData_3b8ac0(void *);
extern void DataTableOwnerSetGameData_3b8be0(s32, void *);
extern void ObjMgrSetGameData_3bc2a0(s32, void *);
extern void PartySetGameData_3cb180(s32, void *);
extern void StateBlockSetup_3cd5f0(s32, s32, s32, void *);
extern void WeaponCombineSetGameData_3cddd0(void *);
extern void ShopSetGameData_3cea50(void *);
extern void ItemSetGameData_3d5130(void *);
extern void OptionsSetGameData_3d6290(s32, void *);
extern void ScriptFnSetGameData_3e01d0(void *);
extern void EventTriggerSysSetGameData_3e3c30(void *);
extern void GameDataReset_3ee0e0(void);
extern void HunterBountySetGameData_3fdcb0(void *);
extern void SavePointSetGameData_426470(void *);
extern void InsectTeamTableSetGameData_431ce0(s32, void *);
extern u8 D_004B2570[0x400];

typedef struct {
    u8 pad0[0x4];
    void *unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[0x2];
    s16 unk2E;
} T3ede30_arg0;

s32 GameDataBindSubsystems_3ede30(T3ede30_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_16;
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_4_3;
    s32 temp_4_4;
    s32 temp_4_5;
    s32 temp_4_6;
    s32 temp_4_7;
    s32 temp_4_8;
    void *temp_2;
    void *temp_3;

    if (arg1 == 0) {
        return 0;
    }
    if (arg3 == 0) {
        return 0;
    }
    if (arg0->unk4 == NULL) {
        return 0;
    }
    arg0->unk8 = arg3;
    GameDataReset_3ee0e0();
    temp_2 = arg0->unk4;
    temp_16 = *(s32 *)((u8 *)temp_2 + 0x34) - *(s32 *)((u8 *)temp_2 + 0x2C);
    SavePointSetGameData_426470(arg0);
    UnitSetGameData_3b8ac0(arg0);
    EquipSlotSetGameData_3a0930(arg0);
    ItemSetGameData_3d5130(arg0);
    ExecInfoSetGameData_3a7980(arg0);
    CharaRecSetGameData_3a6e70(arg0);
    ShopSetGameData_3cea50(arg0);
    CharaEventLogSetGameData_3a6a20(arg0);
    CharaEventLogFormatSetGameData_3a6c40(arg0);
    HunterBountySetGameData_3fdcb0(arg0);
    WeaponCombineSetGameData_3cddd0(arg0);
    temp_4 = arg0->unkC;
    if (temp_4 != 0) {
        OptionsSetGameData_3d6290(temp_4, arg0);
    }
    temp_4_2 = arg0->unk10;
    if (temp_4_2 != 0) {
        StateBlockSetup_3cd5f0(temp_4_2, arg1, arg2, arg0);
        if (arg4 != 0) {
            PadWaitReady_1849e0(&(*(u8 *)D_004B2570));
        }
    }
    temp_4_3 = arg0->unk18;
    if (temp_4_3 != 0) {
        PartySetGameData_3cb180(temp_4_3, arg0);
    }
    temp_4_4 = arg0->unk14;
    if (temp_4_4 != 0) {
        CharaMgrPoolSetGameData_3a9290(temp_4_4, arg0);
    }
    temp_4_5 = arg0->unk1C;
    if (temp_4_5 != 0) {
        ObjMgrSetGameData_3bc2a0(temp_4_5, arg0);
    }
    temp_4_6 = arg0->unk20;
    if (temp_4_6 != 0) {
        CharaSysSetGameData_3a5d10(temp_4_6, arg0);
    }
    temp_4_7 = arg0->unk24;
    if (temp_4_7 != 0) {
        InsectTeamTableSetGameData_431ce0(temp_4_7, arg0);
    }
    EventTriggerSysSetGameData_3e3c30(arg0);
    ScriptFnSetGameData_3e01d0(arg0);
    temp_4_8 = arg0->unk28;
    if (temp_4_8 != 0) {
        DataTableOwnerSetGameData_3b8be0(temp_4_8, arg0);
    }
    temp_3 = arg0->unk4;
    arg0->unk2E =
        (s16)(temp_16 - (*(s32 *)((u8 *)temp_3 + 0x34) - *(s32 *)((u8 *)temp_3 + 0x2C)));
    return 1;
}
