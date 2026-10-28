/* rgp:protos */
#define RGP_SELF_ActCfgTableRunNormalEvntsById_2224d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node002224d0 {
    u8 pad0[0x3E];
    s16 unk3E;
} Node002224d0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ActCfgTableRunNormalEvntsById_2224d0(s32 arg0, s32 arg1, s32 arg2)
{
    Node002224d0 *var_20;
    void *var_19;
    s32 var_18;
    Node002224d0 *temp_2;
    s32 var_18_2;
    void *var_17;
    s32 var_16;
    s32 temp_2_2;
    s32 sp[9] __attribute__((aligned(16)));

    var_19 = DListGetHead_42ea60(arg0 + 0x7C);
    if (var_19 == NULL) {
        var_20 = NULL;
    } else {
        var_20 = NULL;
        var_18 = ((unsigned short)DListGetCountPow2_42ea70(arg0 + 0x7C));
        while (var_18 > 0) {
            var_18 = var_18 >> 1;
            temp_2 = ((Node002224d0 *)DListNodeAdvance_42eb00(var_19, var_18));
            if (temp_2 != NULL) {
                temp_2_2 = IntCompare_42ca30(arg2, temp_2->unk3E);
                if (temp_2_2 == 0) {
                    var_20 = temp_2;
                    break;
                } else if (temp_2_2 > 0) {
                    var_19 = temp_2;
                }
            }
        }
    }
    if (var_20 == NULL) {
        var_17 = NULL;
    } else {
        var_17 = (u8 *) var_20 + 0x10;
    }
    if (var_17 != NULL) {
        var_18_2 = *(s32 *) ((u8 *) var_17 + 0x14);
        if (var_18_2 != 0) {
            sp[0] = arg1;
            var_16 = 0;
            sp[1] = 0;
            sp[2] = 0;
            sp[3] = 0;
            sp[4] = 0;
            sp[5] = 0;
            sp[6] = 0;
            sp[7] = 0;
            sp[8] = 0;
            while (var_16 < *(s16 *) ((u8 *) var_17 + 0x20)) {
                ScriptCallWithArgs_302770(var_18_2, sp, 0);
                var_16 += 1;
                var_18_2 += 0xC;
            }
        }
    }
}
