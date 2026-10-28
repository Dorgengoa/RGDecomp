/* rgp:protos */
#define RGP_SELF_DataTableCompareByByteKey_428b50 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK 2 bad, RIGHT LENGTH (was 49 vs 53). Two fixes banked: the three guards
   are ONE `||` chain ([[levers.d/or-guard-chain-layout]]) and the function has
   an UNUSED FIRST PARAMETER -- retail copies $a1/$a2, not $a0/$a1.
   Residue: retail's argument SETUP ORDER is a0, a2, a1, a3 (both `lh`s, then
   both `lw`s); mwcc emits source order a0, a1, a2, a3.  Same class as the
   s23/s24 nine-unit measured null -- four named locals in either order and a
   struct-member spelling are ONE OBJECT here too.  Do not re-sweep it from
   the source side. */
#include "types.h"

/*rgp*/
/*rgp*/

s32 DataTableCompareByByteKey_428b50(s32 arg0, void *arg1, void *arg2)
{
    s16 temp_2_2;
    s16 temp_3;
    s16 temp_3_2;
    s32 temp_2;
    s32 var_2;

    var_2 = CompareNullness_368070((void *)arg0, (int)arg1, (int)arg2);
    if (var_2 != 0 || arg1 == NULL || arg2 == NULL) {
        return var_2;
    }
    temp_2 = ByteKeyCompare_428a70(*(s16 *)((u8 *)arg1 + 8), *(s32 *)((u8 *)arg1 + 0x10), *(s16 *)((u8 *)arg2 + 8), *(s32 *)((u8 *)arg2 + 0x10)
);
    if (temp_2 != 0) {
        return temp_2;
    }
    temp_3 = *(s16 *)((u8 *)arg1 + 0xA);
    if ((temp_3 > 0) && (*(s16 *)((u8 *)arg2 + 0xA) <= 0)) {
        return -1;
    }
    if ((temp_3 <= 0) && (*(s16 *)((u8 *)arg2 + 0xA) > 0)) {
        return 1;
    }
    temp_3_2 = *(s16 *)((u8 *)arg2 + 0);
    temp_2_2 = *(s16 *)((u8 *)arg1 + 0);
    if (temp_2_2 < temp_3_2) {
        return -1;
    }
    var_2 = temp_3_2 < temp_2_2;
    return var_2;
}
