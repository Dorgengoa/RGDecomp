#include "types.h"

s32 SoundNextPlayHandle_1b81c0();                                 /* extern */
s32 SoundPlayScaledVolume_1b9520(s32, s32, f32, s32);                 /* extern */
u8 *ObjRecGetLiveObject_1c4a90(s32, s32);                       /* extern */
s32 GetCurrentScene_1f5be0();                                 /* extern */
s32 CharaWeaponSeIdRemap_1fd430(s32, s32);                         /* extern */
f32 ScriptArgGetFloat_302cf0(s32);                              /* extern */
s32 ScriptArgGetInt_302d70(s32);                              /* extern */

/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x0, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c, 0x50, 0x54], gap at: 0x8. */
s32 CharaCmdSePlay_22a9b0(s32 *arg0, s32 arg1, s32 arg2) {
    f32 var_f20;
    s32 temp_16;
    s32 temp_17;
    s32 temp_2;
    u8 *temp_2_2;

    if ((arg2 != 1) && (arg2 != 2)) {
        return 1;
    }
    temp_2 = GetCurrentScene_1f5be0();
    if (temp_2 == 0) {
        return 1;
    }
    temp_2_2 = ObjRecGetLiveObject_1c4a90(temp_2, *arg0);
    if (temp_2_2 == 0) {
        return 1;
    }
    temp_17 = CharaWeaponSeIdRemap_1fd430(*arg0, ScriptArgGetInt_302d70(arg1));
    if (arg2 >= 2) {
        var_f20 = ScriptArgGetFloat_302cf0(arg1 + 5);
    } else {
        var_f20 = 1.0f;
    }
    temp_16 = (*(s32 *)((u8 *)temp_2_2 + 0x4FC));
    SoundPlayScaledVolume_1b9520(temp_16, temp_17, var_f20, SoundNextPlayHandle_1b81c0());
    return 1;
}
