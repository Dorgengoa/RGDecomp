/* rgp:protos */
#define RGP_SELF_CharaRefEvalCompByName_312090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void CharaRefEvalCompByName_312090(u8 *arg0, u8 *arg1, s8 *arg2, f32 fparg0, f32 fparg1) {
    s32 var_17;
    s32 var_16;
    s8 temp_21;

    *(s32 *)(arg1 + 0) = 0;
    *(s32 *)(arg1 + 4) = 0;
    *(s32 *)(arg1 + 8) = 0;
    *(s32 *)(arg1 + 0xC) = 0;
    var_17 = *(s32 *)(arg0 + 4);
    if (var_17 == 0 || *(s16 *)(arg0 + 8) <= 0 || arg2 == NULL) {
        return;
    }
    for (var_16 = 0; var_16 < *(s16 *)(arg0 + 8); var_16++, var_17 += 0xC) {
        temp_21 = *arg2;
        if (temp_21 == *((s8 *)NamedCompListGetName_3124b0(var_17)) && StrNotEqual_1f5300(arg2 + 1, ((s8 *)NamedCompListGetName_3124b0(var_17)) + 1) == 0) {
            NamedCompListSumVec_3123b0(var_17, arg1, fparg0, fparg1);
            return;
        }
    }
}
