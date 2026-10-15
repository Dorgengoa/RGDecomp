/* PARK: length 0x10C vs retail 0x104 (8 over) after 1 round. Not re-tried. */
#include "types.h"
#pragma opt_common_subs off

extern s32 CharaIsGroundReadyMaybe_210850(void);
extern s32 CharaIsLandedOrLockedMaybe_2109c0(void *arg0);
extern void CharaActMoveMotion_21b180(void *arg0, s32 arg1);
extern void CharaSetActionModeMoveMotion_21bbb0(void *arg0);
extern void CharaActLoco_21cc10(void *arg0, s32 arg1);
extern void CharaResetToBaseMode_21e830(void *arg0);
extern void CharaHangLedgeInvalidate_23a2a0(void *arg0);

s32 CharaInputInterruptMaybe_21e8f0(void *arg0, s32 arg1)
{
    if (*(s32 *)((u8 *)arg0 + 0xA44) & 0x01000000) {
        return 0;
    }
    if ((*(s64*)((u8 *)arg0 + 0x570) & 0x10000) && (CharaIsGroundReadyMaybe_210850() != 0)) {
        CharaHangLedgeInvalidate_23a2a0((u8 *)arg0 + 0x350);
        *(s64 *)((u8 *)arg0 + 0x3D0) = *(s64 *)((u8 *)arg0 + 0x3D0) | ((s64) 0x04000000 << 0x20);
        CharaSetActionModeMoveMotion_21bbb0(arg0);
        *(s16*)((u8 *)arg0 + 0xA34) = 0xC8;
        CharaActMoveMotion_21b180(arg0, arg1);
        return 1;
    }
    if ((*(s64*)((u8 *)arg0 + 0x570) & 3) && (CharaIsLandedOrLockedMaybe_2109c0(arg0) != 0)) {
        CharaHangLedgeInvalidate_23a2a0((u8 *)arg0 + 0x350);
        *(s64 *)((u8 *)arg0 + 0x3D0) = *(s64 *)((u8 *)arg0 + 0x3D0) | ((s64) 0x04000000 << 0x20);
        CharaResetToBaseMode_21e830(arg0);
        CharaActLoco_21cc10(arg0, arg1);
        return 1;
    }
    return 0;
}
