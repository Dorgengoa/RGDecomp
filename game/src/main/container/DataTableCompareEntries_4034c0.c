/* rgp:protos */
#define RGP_SELF_DataTableCompareEntries_4034c0 1
#include "port/game_protos.h"
#line 1
/* PARKED (round 1): length 0xA0 vs retail 0xAC (0xC bytes short) even after
   adding the unused leading pointer param (dropped-parameter lever). The
   final 3-way compare block's control flow may need reshaping to match the
   bgtzl/beql branch-likely structure exactly (see the .s). */
#include "types.h"
#pragma opt_repositioncode on
#pragma opt_repositioncode off

/* Real signature has an UNUSED leading pointer param at $4; $5/$6 hold the
   two compared objects. */
typedef struct Obj {
    s16 unk0;
    u8 pad2[0x1E];
    s16 unk20;
} Obj;

/*rgp*/

s32 DataTableCompareEntries_4034c0(void *unused, Obj *arg1, Obj *arg2)
{
    s32 temp_2;
    s32 temp_3;
    s32 temp_3_2;
    s32 var_2;

    var_2 = CompareNullness_368070((void *)unused, (int)arg1, (int)arg2);
    if ((!((var_2 == 0) && (arg1 != NULL))) || (arg2 == NULL)) return var_2;
    temp_3 = arg1->unk20;
    if ((temp_3 > 0) && (arg2->unk20 <= 0)) {
        return -1;
    }
    if ((temp_3 < 1) && (arg2->unk20 > 0)) {
        return 1;
    }
    temp_3_2 = arg2->unk0;
    temp_2 = arg1->unk0;
    if (temp_2 < temp_3_2) {
        return -1;
    }
    var_2 = temp_3_2 < temp_2;
    return var_2;
    return var_2;
}
