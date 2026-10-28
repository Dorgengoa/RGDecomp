/* rgp:protos */
#define RGP_SELF_ScreenFadeCaptureFrame_1cf550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                                /* extern */
/*rgp*/                           /* extern */
/*rgp*/                           /* extern */
/*rgp*/                         /* extern */
/*rgp*/                              /* extern */
/*rgp*/                           /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                 /* extern */

void ScreenFadeCaptureFrame_1cf550(s32 arg0) {
    u8 var_18;
    s32 var_17;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_2;

    var_18 = 0;
    if ((GetGameMode_1f59c0() == 9) && (GetGameModePhase_1f59b0() == 0x64)) {
        var_17 = 0;
        temp_2 = RecStackPush_1c4240(arg0, 0);
        temp_2_2 = ((s32)RecStackGetSlot_1c4330(arg0, temp_2));
        if (temp_2_2 != 0) {
            var_17 = MemStackGetFree_1c6d50(temp_2_2);
        }
        RecStackPop_1c4140(arg0, temp_2);
        if (var_17 < 0xE140) {
            var_18 = 1;
        }
    }
    if (var_18) {
        var_2 = GetReadBuffTailPtr_2025c0();
    } else {
        var_2 = GetReadBuffCapturePtr_2025d0();
    }
    ScreenFadeSetCaptureBuf_1cf640(arg0, var_2);
    ScreenFadeBlockCaptureFrame_177ed0(arg0 + 0x5980);
}
