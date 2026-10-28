/* rgp:protos */
#define RGP_SELF_ActionMgrRemoveCharaRef_2340b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                           /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                         /* extern */
/*rgp*/                        /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                           /* extern */
/*rgp*/                         /* extern */

void ActionMgrRemoveCharaRef_2340b0(u8 *arg0, s32 arg1) {
    s32 var_20;
    s32 var_19;
    s32 var_18;
    s32 temp_2_2;
    s32 temp_2;
    s32 temp_17;

    var_19 = DListGetHead_42ea60((void *)arg0);
    if (var_19 == 0) {
        var_20 = 0;
    } else {
        var_20 = 0;
        var_18 = ((unsigned short)DListGetCountPow2_42ea70(arg0));
        while (var_18 > 0) {
            var_18 >>= 1;
            temp_2 = ((s32)DListNodeAdvance_42eb00(var_19, var_18));
            if (temp_2 != 0) {
                temp_2_2 = IntCompare_42ca30(arg1, ((short)CharaRefGetId_3121c0(temp_2 + 0x10)));
                if (temp_2_2 == 0) {
                    var_20 = temp_2;
                    break;
                }
                if (temp_2_2 > 0) {
                    var_19 = temp_2;
                }
            }
        }
    }
    if (var_20 != 0) {
        temp_17 = (*(s32 *)((u8 *)arg0 + 0x3C));
        if (var_20 != 0) {
            if (temp_17 != 0) {
                MemStackHeapFree_14dcb0(temp_17, CharaRefGetBlock_3121d0(var_20 + 0x10));
            }
            DListRemove_42e4e0(arg0, var_20);
        }
    }
}
