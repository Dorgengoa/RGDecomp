/* rgp:protos */
#define RGP_SELF_ResidentFileReadAlignedMaybe_3ee010 1
#include "port/game_protos.h"
#line 1
/* main s27m: 11 -> 1. PARK: the last word is `addu a0,v1,v0` vs retail `addu a0,v0,v1`
   (retail: compare computed FIRST, division second, division in rs). div+cmp,
   named temps in both orders and X - (-Y) / X - (0 - Y) are 1 or 11 bad. */
/* PARK: 11 bad words (was 16). Fixed dropped leading arg0 and the callee's
   hidden middle arg (ResidentFileReadLocalizedMaybe_1c2860 takes 3 args, was called with 2).
   Remaining residue is the ceil-div-by-16-then-round-to-4 block scheduled
   differently than retail (same instructions, shuffled order) -- have not
   found the source shape that reproduces retail's interleaving in 3 tries. */
#include "types.h"

/*rgp*/                  /* extern */
extern s32 D_0048012C;

s32 ResidentFileReadAlignedMaybe_3ee010(s32 arg0, s32 arg1, s32 *arg2) {
    s32 sp3C;
    s32 temp_3;
    s32 temp_3_2;
    s32 var_2;
    s32 var_2_2;
    s32 var_4;

    if (arg1 == 0) {
        return 0;
    }
    sp3C = 0;
    temp_3 = ResidentFileReadLocalizedMaybe_1c2860(D_0048012C, arg1, &sp3C) & 0xFF;
    if (arg2 != NULL) {
        *arg2 = sp3C;
    }
    var_2 = 0;
    if ((temp_3 != 0) && (sp3C > 0)) {
        var_2_2 = sp3C / 16;
        var_4 = var_2_2 - (-(s32)((sp3C % 16) > 0));
        temp_3_2 = var_4 % 4;
        if (temp_3_2 > 0) {
            var_4 += 4 - temp_3_2;
        }
        var_2 = (s32)((u8 *)arg1 + (var_4 * 0x10));
    }
    return var_2;
}
