/* rgp:protos */
#define RGP_SELF_DataTableBuildSortedIndex_413eb0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: length-wrong (111w vs retail 105w, ours LONGER). */
#include "types.h"

/*rgp*/
void *memcpy(void *, const void *, s32);

s32 DataTableBuildSortedIndex_413eb0(u8 *arg0) {
    s16 *var_18;
    s32 var_8;
    s32 var_2_2;
    s16 *var_2;
    s32 var_17;
    s16 *temp_16;
    u8 *var_7;
    s32 var_6;
    s16 *var_5;
    s16 temp_2;
    s32 var_4;
    s32 sp5C;
    u16 var_5_2;
    s32 temp_5;
    s16 temp_3;
    s16 temp_2_2;

    temp_5 = *(s32 *)(arg0 + 0x10);
    if (temp_5 == 0) return 0;
    if (*(u8 **)(arg0 + 0x8C) == NULL) return 0;
    if (*(s16 *)(arg0 + 0x7C) <= 0 || *(s16*)(arg0 + 0x9C) <= 0) {
        *(s16*)(arg0 + 0x9C) = 0;
        *(u8 **)(arg0 + 0xA0) = NULL;
        return 1;
    }
    temp_2 = *(s16*)(arg0 + 0x9C);
    var_2 = ((s16 *)MemStackNew_14e0b0(temp_2 * 4, temp_5));
    *(s16 **)(arg0 + 0xA0) = var_2;
    if (var_2 == NULL) {
        return 0;
    }
    var_7 = *(u8 **)(arg0 + 0x8C);
    var_8 = 0;
    var_6 = 0;
    while (var_6 < *(s16 *)(arg0 + 0x7C)) {
        if (var_8 < *(s16*)(arg0 + 0x9C)) {
            var_5 = *(s16 **)(var_7 + 0x14);
            if (var_5 != NULL) {
                var_4 = 0;
                while (var_4 < *(s16 *)(var_7 + 0x10)) {
                    var_4 += 1;
                    var_8 += 1;
                    var_2[0] = *var_5;
                    var_5 += 1;
                    var_2[1] = var_6;
                    var_2 += 2;
                }
            }
            var_6 += 1;
            var_7 += 0x18;
            continue;
        }
        break;
    }
    do {
        var_18 = *(s16 **)(arg0 + 0xA0);
        var_5_2 = 0;
        var_17 = 1;
        while (var_17 < *(s16*)(arg0 + 0x9C)) {
            temp_2_2 = *var_18;
            temp_16 = *(s16 **)(arg0 + 0xA0) + (var_17 * 2);
            temp_3 = *temp_16;
            if (temp_2_2 == temp_3) {
                var_2_2 = 0;
            } else {
                if (temp_2_2 < temp_3) {
                    var_2_2 = -1;
                } else {
                    var_2_2 = 1;
                }
            }
            if (var_2_2 > 0) {
                memcpy(&sp5C, temp_16, 4);
                memcpy(temp_16, var_18, 4);
                memcpy(var_18, &sp5C, 4);
                var_5_2 = 1;
            }
            var_18 = temp_16;
            var_17 += 1;
        }
    } while (var_5_2);
    return 1;
}
