/* rgp:protos */
#define RGP_SELF_EventObjMgrFindPathRecByName_2e9c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

u8 *EventObjMgrFindPathRecByName_2e9c90(void *a, void *key)
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
        c = StrCmpNullSafe_42ca40(key, EventRecGetKey_2e5730(cur + 0x10));
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
