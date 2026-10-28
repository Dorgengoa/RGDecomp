/* rgp:protos */
#define RGP_SELF_ContainerViewItemFilterCountMatches_40c1c0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARKED: 1 round trip (+1 --align look): mechanical conversion, close (47w vs retail 45w) -- minor var_16 init ordering residue, not chased further. */
#include "types.h"
#pragma opt_common_subs off

/*rgp*/

s32 ContainerViewItemFilterCountMatches_40c1c0(void *arg0)
{
    s32 temp_18;
    s32 var_16;
    s32 var_20;
    s32 var_19;
    void *temp_2;
    void *temp_2_2;

    temp_2 = *(void **)((u8 *)arg0 + 0x4);
    if (temp_2 == NULL) {
        return 0;
    }
    temp_2_2 = *(void **)((u8 *)(*(void **)((u8 *)(*(void **)((u8 *)temp_2 + 0x8)) + 0x40)) + 0x8);
    var_16 = 0;
    if (temp_2_2 == NULL) {
        return 0;
    }
    temp_18 = *(s16 *)((u8 *)temp_2_2 + 0x7C);
    var_20 = *(s32 *)((u8 *)temp_2_2 + 0x8C);
    if (var_20 == 0) {
        return 0;
    }
    var_19 = 0;
    while (var_19 < temp_18) {
        if (ContainerViewItemFilterMatch_40c280(arg0, var_20) != 0) {
            var_16 += 1;
        }
        var_19 += 1;
        var_20 += 0x34;
    }
    return var_16;
}
