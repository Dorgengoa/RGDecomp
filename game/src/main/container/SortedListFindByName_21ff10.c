/* rgp:protos */
#define RGP_SELF_SortedListFindByName_21ff10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Skip-list binary walk, twin of the proven ActCfgTableListInsertSortedByScopeId_1fe090 shape:
   halving stride, bottom loop test with the `sra` in the bgtzl delay slot.
   Retail FALLS THROUGH into `res = node; break;` on the equal compare, so
   that is the source's `if` body; `blez` past the `node = q` makes the
   second guard `c > 0`. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 SortedListFindByName_21ff10(s32 arg0, s32 arg1)
{
    s32 node;
    s32 res;
    s32 n;
    s32 q;
    s32 c;

    /* MEASURED: the assignment must live INSIDE the condition.  As a
       separate statement mwcc compares the COPY ($19) with a branch-likely;
       inside the condition it compares the call result ($2) with a plain
       branch and schedules the copy into the delay slot. */
    if ((node = DListGetHead_42ea60(arg0)) == 0) {
        return 0;
    }
    res = 0;
    n = ((unsigned short)DListGetCountPow2_42ea70(arg0));
    while (n > 0) {
        n = n >> 1;
        q = ((s32)DListNodeAdvance_42eb00(node, n));
        if (q != 0) {
            c = StrCmpNullSafe_42ca40(arg1, *(s32 *)(q + 0x38));
            if (c == 0) {
                res = q;
                break;
            }
            if (c > 0) {
                node = q;
            }
        }
    }
    return res;
}
