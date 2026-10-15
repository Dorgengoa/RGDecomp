#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

extern void XformRecUpdateMaybe_1c5ee0(void *, s32);
extern void CharaAimCtrlSetEnabled_1d8150(void *, s32);
extern void CharaAimCtrlUpdate_1d81b0(void *, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void TargetRefClear_2e71d0(void *);

void CharaResetAim_212b90(void *arg0, s32 arg1)
{
    s32 temp_16;

    temp_16 = GetCurrentScene_1f5be0();
    TargetRefClear_2e71d0((u8 *)arg0 + 0x97C);
    *(s32 *)((u8 *)arg0 + 0x470) = 0;
    *(s32 *)((u8 *)arg0 + 0x474) = 0;
    *(s32 *)((u8 *)arg0 + 0x478) = 0;
    *(f32 *)((u8 *)arg0 + 0x47C) = 1.0f;
    *(s16 *)((u8 *)arg0 + 0x550) = 0;
    *(s16 *)((u8 *)arg0 + 0x552) = 0;
    CharaAimCtrlSetEnabled_1d8150((u8 *)arg0 + 0x4D0, 0);
    *(u32 *)((u8 *)arg0 + 0xA44) &= 0xFFFF7FFF;
    *(u64 *)((u8 *)arg0 + 0x3D0) = (*(u64 *)((u8 *)arg0 + 0x3D0) << 0x21) >> 0x21;
    if (arg1 != 0) {
        arg1 = 0;
        do {
            XformRecUpdateMaybe_1c5ee0((u8 *)arg0 + 0x500, temp_16);
            CharaAimCtrlUpdate_1d81b0((u8 *)arg0 + 0x4D0, temp_16);
            arg1 += 1;
        } while (arg1 < 0x1E);
    }
}
