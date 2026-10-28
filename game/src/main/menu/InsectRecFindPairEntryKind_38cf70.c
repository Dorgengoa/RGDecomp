/* rgp:protos */
#define RGP_SELF_InsectRecFindPairEntryKind_38cf70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 InsectRecFindPairEntryKind_38cf70(s32 arg0, void *arg1) {
    s16 temp_16;
    s16 temp_3;
    s32 var_17;
    s32 var_6;
    void *temp_2;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    temp_16 = *(s16 *)((u8 *)arg1 + 4);
    var_17 = 0;
    while (var_17 < 2) {
        temp_2 = InsectRecGetPairEntry_3cf2b0(arg0, var_17);
        if (temp_2 != NULL) {
            var_6 = 0;
            while (var_6 < 2) {
                if (temp_16 == *(s16 *)((u8 *)temp_2 + (var_6 * 2))) {
                    temp_3 = *(s16 *)((u8 *)temp_2 + 4);
                    if (temp_3 == 1) {
                        return 1;
                    }
                    if (temp_3 == 2) {
                        return 2;
                    }
                }
                var_6 += 1;
            }
        }
        var_17 += 1;
    }
    return 0;
}
