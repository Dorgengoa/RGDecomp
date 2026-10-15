/* main s27m: CLOSED -- temp_3 is s32 and NAMED AFTER `var_f20 = 1.0f` (vreg creation
   order); as an s16 it is 1 bad (lh), named first it permutes 7 words. */
#include "types.h"

s32 StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);                   /* extern */
s32 GetLoaderMgr_1f59d0();                                 /* extern */
f32 TaggedGetFloat_2490d0(s32 *);                            /* extern */
s32 ScriptGetInt_2490f0(s32 *);                            /* extern */
extern f32 D_0047D288;

/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x0, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40, 0x44], gap at: 0x8. */
s32 EvCmdStreamVolumeFade_244380(s32 *arg0, s32 arg1) {
    s32 *var_18;
    s32 temp_16;
    s32 temp_3;
    f32 var_f20;
    s32 *temp_4;
    s32 *temp_4_2;
    s32 temp_f0;
    s32 var_2;

    var_18 = arg0;
    if ((arg1 != 1) && (arg1 != 2)) {
        return 0;
    }
    temp_16 = GetLoaderMgr_1f59d0();
    var_f20 = 1.0f;
    temp_3 = *var_18;
    if (temp_3 == 1) {
        temp_4 = var_18;
        var_18 += 2;
        var_f20 = TaggedGetFloat_2490d0(temp_4);
    } else if (temp_3 == 0) {
        temp_4_2 = var_18;
        var_18 += 2;
        temp_f0 = (s32) TaggedGetFloat_2490d0(temp_4_2);
        if (temp_f0 == 0) {
            var_f20 = 1.0f;
        }
        if (temp_f0 == 1) {
            var_f20 = D_0047D288;
        }
    }
    var_2 = 0;
    if (arg1 >= 2) {
        var_2 = ScriptGetInt_2490f0(var_18);
    }
    StreamSetChanVolumeFade_1cd960(temp_16, 0, var_2, var_f20);
    return 1;
}
