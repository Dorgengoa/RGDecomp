#include "types.h"

s32 MapSlotsFindIdByName_1e4520(s32, s32);                         /* extern */
s32 GetMapMgr_201a90();                                 /* extern */
s32 ScriptGetCodeAddr_249050(s32 *);                            /* extern */
f32 TaggedGetFloat_2490d0(s32 *);                            /* extern */
s32 ScriptGetInt_2490f0(s32 *);                            /* extern */
s32 GetEventObjMgr_2d1960();                                 /* extern */
s32 EvSpawnMonograph_2e90f0(s32, s32, s32, f32, f32);            /* extern */

/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x0, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c, 0x50, 0x54], gap at: 0x8. */
s32 EvCmdSpawnMonograph_242b20(s32 *arg0, s32 arg1) {
    f32 var_f20;
    s32 temp_16;
    s32 temp_17;
    s32 temp_19;
    s32 var_2;

    if ((arg1 != 3) && (arg1 != 4)) {
        return 0;
    }
    temp_16 = GetEventObjMgr_2d1960();
    var_2 = (*arg0 == 2) ? MapSlotsFindIdByName_1e4520(GetMapMgr_201a90(), ScriptGetCodeAddr_249050(arg0)) : ScriptGetInt_2490f0(arg0);
    var_f20 = 0.0f;
    if (arg1 > 3) {
        var_f20 = TaggedGetFloat_2490d0(arg0 + 6);
    }
    temp_17 = ScriptGetCodeAddr_249050(arg0 + 2);
    EvSpawnMonograph_2e90f0(temp_16, var_2, temp_17, TaggedGetFloat_2490d0(arg0 + 4), var_f20);
    return 1;
}
