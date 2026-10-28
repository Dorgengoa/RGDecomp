/* rgp:protos */
#define RGP_SELF_AiRouteMoveToTargetMaybe_2bcd90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                              /* extern */
/*rgp*/ /* extern */
/*rgp*/                   /* extern */
/*rgp*/                          /* extern */

void AiRouteMoveToTargetMaybe_2bcd90(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 fparg0) {
    s32 t;

    if (arg1 == 0 || (t = *arg1) == 0) {
        return;
    }
    if (((short)CharaGetActionMode_213850(t)) == 6) {
        CharaReqClimbOrFallByHeight_2bd140(arg0, t, arg2);
        return;
    }
    if (*(s8 *)(arg0 + 0x260) == 0) {
        *(s8 *)(arg0 + 0x260) = NavEdgeAtPosIsRowLine_2bd1e0(arg2, t);
    }
    AiRouteMoveStepMaybe_2bce90(arg0, arg1, arg2, arg3, arg4, arg5, fparg0);
}
