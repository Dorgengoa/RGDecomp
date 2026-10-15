#include "types.h"
#pragma opt_common_subs off

extern void CharaSysOnBattleEndCode_3a1140(void *, s32);
extern void CharaMgrPoolOnBattleEndCodeAll_3a8730(s32);
extern void ObjMgrOnBattleEndCodeAll_3ba8b0(s32, s32, s32, s32, s32);
extern void InvOnBattleEndAll_3c01e0(s32, s32);

s32 GameDataBattleEnd_3e67c0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_4_3;
    u8 *temp_4_4;

    if (!(*(u8 *)(*(u8 **)((u8 *)arg0 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    temp_4 = *(s32 *)((u8 *)arg0 + 0x14);
    if (temp_4 != 0) {
        CharaMgrPoolOnBattleEndCodeAll_3a8730(temp_4);
    }
    temp_4_2 = *(s32 *)((u8 *)arg0 + 0x1C);
    if (temp_4_2 != 0) {
        ObjMgrOnBattleEndCodeAll_3ba8b0(temp_4_2, arg1, arg2, arg3, arg4);
    }
    temp_4_3 = *(s32 *)((u8 *)arg0 + 0x18);
    if (temp_4_3 != 0) {
        InvOnBattleEndAll_3c01e0(temp_4_3, arg1);
    }
    temp_4_4 = *(u8 **)((u8 *)arg0 + 0x20);
    if (temp_4_4 != NULL) {
        CharaSysOnBattleEndCode_3a1140(temp_4_4, arg1);
    }
    return 1;
}
