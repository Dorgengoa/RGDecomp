/* rgp:protos */
#define RGP_SELF_EvMapObjFindByName_2e9880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvMapObjFindByName_2e9880(s32 a0, s8 *arg1)
{
    s32 node;

    node = DListGetHead_42ea60(((s32)EventObjMgrGetTypeList_2e9d60(a0, 8)));
    while (node != 0) {
        if (*arg1 == *((s8 *)EventRecGetKey_2e5730(node + 0x10)) &&
            StrNotEqual_1f5300((s32)(((s8 *)EventRecGetKey_2e5730(node + 0x10)) + 1), arg1 + 1) == 0) {
            return node + 0x10;
        }
        node = DListGetNext_42eb30(node);
    }
    return 0;
}
