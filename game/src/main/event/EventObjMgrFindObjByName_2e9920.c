/* rgp:protos */
#define RGP_SELF_EventObjMgrFindObjByName_2e9920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EventObjMgrFindObjByName_2e9920(s32 pd0, s32 arg1, s32 arg2) {
    s32 node;
    s32 found;
    s32 lo;
    s32 n;
    s32 c;
    s32 t;

    if (arg1 == 0) {
        return 0;
    }
    node = ((s32)EventObjMgrGetTypeList_2e9d60(pd0, arg2));
    if (node == 0) {
        return 0;
    }
    t = DListGetHead_42ea60(node);
    lo = t;
    if (t == 0) {
        found = 0;
    } else {
        found = 0;
        n = ((unsigned short)DListGetCountPow2_42ea70(node));
        while (n > 0) {
            n >>= 1;
            node = ((s32)DListNodeAdvance_42eb00(lo, n));
            if (node != 0) {
                c = StrCmpNullSafe_42ca40(arg1, EventRecGetKey_2e5730(node + 0x10));
                if (c == 0) {
                    found = node;
                    break;
                }
                if (c > 0) {
                    lo = node;
                }
            }
        }
    }
    if (found == 0) {
        return 0;
    }
    return found + 0x10;
}
