#include "types.h"

s32 CharaGetActionMode_213850(s32);                              /* extern */
s32 AiRouteMoveStepMaybe_2bce90(u8 *, s32 *, s32, s32, f32, s32, s32); /* extern */
s32 CharaReqClimbOrFallByHeight_2bd140(u8 *, s32, s32);                   /* extern */
s8 NavEdgeAtPosIsRowLine_2bd1e0(s32, s32);                          /* extern */

void AiRouteMoveToTargetMaybe_2bcd90(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 fparg0) {
    s32 t;

    if (arg1 == 0 || (t = *arg1) == 0) {
        return;
    }
    if (CharaGetActionMode_213850(t) == 6) {
        CharaReqClimbOrFallByHeight_2bd140(arg0, t, arg2);
        return;
    }
    if (*(s8 *)(arg0 + 0x260) == 0) {
        *(s8 *)(arg0 + 0x260) = NavEdgeAtPosIsRowLine_2bd1e0(arg2, t);
    }
    AiRouteMoveStepMaybe_2bce90(arg0, arg1, arg2, arg3, fparg0, arg4, arg5);
}
