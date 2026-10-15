#include "types.h"

extern void GsPktWriteAD_13ec80(s32, s32, s64);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);

void GsPktSetScissorFull_26fe60(s32 arg0) {
    s32 temp_17;
    s32 temp_18;
    s32 temp_2;

    if (arg0 != 0) {
        temp_2 = GetDrawCtx_15de80();
        temp_18 = DrawEnvGetWidth_1451e0(temp_2);
        temp_17 = DrawEnvGetHeight_1451d0(temp_2);
        GsPktOpenPrim_13f730(arg0, 6);
        GsPktWriteAD_13ec80(arg0, 0x40, ((s64)(temp_18 - 1) << 16) | ((s64)(temp_17 - 1) << 48));
        GsPktClose_13f5b0(arg0);
    }
}
