/* rgp:protos */
#define RGP_SELF_ActionMgrFindRefById_233cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

u8 *ActionMgrFindRefById_233cf0(void *a, void *key)
{
    u8 *best;
    u8 *lo;
    s32 k;
    u8 *cur;
    s32 c;

    if ((lo = ((u8 *)DListGetHead_42ea60(a))) != 0) {
        goto search;
    }
    best = 0;
    goto done;
search:
    best = 0;
    k = ((unsigned short)DListGetCountPow2_42ea70(a));
    while (k > 0) {
        k >>= 1;
        cur = ((u8 *)DListNodeAdvance_42eb00(lo, k));
        if (cur == 0) {
            continue;
        }
        c = IntCompare_42ca30(key, CharaRefGetId_3121c0(cur + 0x10));
        if (c == 0) {
            best = cur;
            goto done;
        }
        if (c > 0) {
            lo = cur;
        }
    }
done:
    if (best == 0) {
        return 0;
    }
    return best + 0x10;
}
