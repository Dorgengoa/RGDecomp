/* rgp:protos */
#define RGP_SELF_BtlElemParamGetChainLengthMaybe_3f9440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004658BC[];

s32 BtlElemParamGetChainLengthMaybe_3f9440(s32 unused, s32 arg2) {
    if (arg2 <= 0 || arg2 > 3) {
        return -1;
    }
    return D_004658BC[arg2];
}
