/* rgp:protos */
#define RGP_SELF_CharaCmdSpPlay_22a880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                             /* extern */
/*rgp*/                        /* extern */
/*rgp*/                             /* extern */
/*rgp*/                   /* extern */
/*rgp*/                      /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */

/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x0, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40, 0x44], gap at: 0x8. */
s32 CharaCmdSpPlay_22a880(s32 pd0, s32 arg1, s32 arg2) {
    f32 var_f0;
    s32 temp_18;
    s32 temp_2;
    s32 var_2;

    if ((arg2 != 1) && (arg2 != 2) && (arg2 != 3)) {
        return 1;
    }
    if (arg2 > 1) {
        var_f0 = ScriptArgGetFloat_302cf0(arg1 + 5);
    } else {
        var_f0 = 1.0f;
    }
    if (arg2 > 2) {
        var_2 = ScriptArgGetInt_302d70(arg1 + 0xA);
    } else {
        var_2 = 0;
    }
    temp_18 = var_2 != 0;
    if (!(((signed char)ScriptArgGetTag_302df0(arg1)) != 2)) {
        temp_2 = ((s32)GetStreamMgr_207ea0());
        StreamMgrPauseChan_1d6630(temp_2, 1);
        StreamMgrStopChan_1d66b0(temp_2, 1);
        StreamMgrStartChan_1d66f0(temp_2, 1, ScriptArgGetStr_302cb0(arg1), temp_18 & 0xFF);
        StreamMgrPlayChan_1d6670(temp_2, 1, var_f0);
    } else {
        StreamPlayMwv_207340(ScriptArgGetInt_302d70(arg1), temp_18, var_f0);
    }
    return 1;
}
