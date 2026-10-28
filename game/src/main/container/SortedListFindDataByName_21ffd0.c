/* rgp:protos */
#define RGP_SELF_SortedListFindDataByName_21ffd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node0021ffd0 {
    u8 pad0[0x38];
    s32 unk38;
} Node0021ffd0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void *SortedListFindDataByName_21ffd0(s32 arg0, s32 arg1) {
    Node0021ffd0 *var_19;
    Node0021ffd0 *var_18;
    s32 var_17;
    Node0021ffd0 *temp_2_2;
    Node0021ffd0 *temp_2;
    s32 temp_2_3;

    temp_2 = ((Node0021ffd0 *)DListGetHead_42ea60((void *)arg0));
    var_18 = temp_2;
    if (temp_2 == NULL) {
        var_19 = NULL;
    } else {
        var_19 = NULL;
        var_17 = ((unsigned short)DListGetCountPow2_42ea70(arg0));
        while (var_17 > 0) {
            var_17 = var_17 >> 1;
            temp_2_2 = ((Node0021ffd0 *)DListNodeAdvance_42eb00(var_18, var_17));
            if (temp_2_2 != NULL) {
                temp_2_3 = StrCmpNullSafe_42ca40(arg1, temp_2_2->unk38);
                if (temp_2_3 == 0) {
                    var_19 = temp_2_2;
                    break;
                }
                if (temp_2_3 > 0) {
                    var_18 = temp_2_2;
                }
            }
        }
    }
    if (var_19 == NULL) {
        return NULL;
    }
    return (u8 *)var_19 + 0x10;
}
