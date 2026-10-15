#include "types.h"
#pragma opt_dead_assignments off

f32 VariantGetFloat_311e10(s32);                              /* extern */
s32 MovCfgMoveItemInit_312750(s32, f32, f32, f32, f32, f32);       /* extern */
extern s32 D_004829A0;
extern s32 D_004829A4;

s32 MovCfgCmdMove_311bc0(s32 arg0, s32 arg1) {
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    f32 temp_f23;
    s32 temp_17;

    if (arg1 != 5) {
        return 0;
    }
    if ((D_004829A0 == 0) || (D_004829A4 >= 0x200)) return 1;
    temp_17 = D_004829A0 + (D_004829A4 * 0x14);
    temp_f23 = VariantGetFloat_311e10(arg0);
    temp_f22 = VariantGetFloat_311e10(arg0 + 8);
    temp_f21 = VariantGetFloat_311e10(arg0 + 0x10);
    temp_f20 = VariantGetFloat_311e10(arg0 + 0x18);
    MovCfgMoveItemInit_312750(temp_17, temp_f23, temp_f22, temp_f21, temp_f20, VariantGetFloat_311e10(arg0 + 0x20));
    D_004829A4 += 1;
    return 1;
    return 1;
}
