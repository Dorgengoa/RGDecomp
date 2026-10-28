/* rgp:protos */
#define RGP_SELF_TextGridCellRect_208650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 TextGridCellRect_208650(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10)
{
    u8 *ctx;
    s32 f0;
    s32 f1;

    ctx = (u8 *)GetTextLayoutCtx_3133b0();
    f0 = *(s32 *)(ctx + 0x614);
    f1 = *(s32 *)(ctx + 0x618);
    if (arg0 != NULL) {
        *arg0 = ((arg4 + (f0 * arg6)) - arg10) + 1;
    }
    if (arg1 != NULL) {
        *arg1 = ((arg5 + (f1 * arg7)) - arg10) + 3;
    }
    if (arg2 != NULL) {
        *arg2 = arg10 + (arg4 + (f0 * (arg6 + arg8))) + 1;
    }
    if (arg3 != NULL) {
        *arg3 = arg10 + (arg5 + (f1 * (arg7 + arg9)));
    }
    return 1;
}
