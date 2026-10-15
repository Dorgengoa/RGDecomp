#include "types.h"

extern void MsgFormatParamsCtor_28aa00(s32 *);
extern void SaveMsgBoxShow_376bf0(s32, s32, s32 *);
extern s32 SaveCalcSizeKBCurrent_37b920(void);
extern u8 *D_004831D0;

void SaveMsgBoxShowSlotInfo_376b60(s32 arg0, s32 arg1, s32 arg2, s64 arg3) {
    u8 frame[0xB0];
    s32 var_2;

    MsgFormatParamsCtor_28aa00((s32 *)frame);
    *(s32 *)(frame + 0) = *(s16 *)(D_004831D0 + 0x4EC) + 1;
    var_2 = *(s16 *)(D_004831D0 + 0x4EE) + 1;
    if (arg2 != 0) {
        s16 tmp = (s16)arg3;
        var_2 = tmp + 1;
    }
    *(s32 *)(frame + 4) = var_2;
    *(s32 *)(frame + 8) = SaveCalcSizeKBCurrent_37b920();
    SaveMsgBoxShow_376bf0(arg0, arg1, (s32 *)frame);
}
