/* rgp:protos */
#define RGP_SELF_NavMgrFindGraphById_30cae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S0030cae0 {
    u8 pad0[0xC];
    s32 *list;
    u32 n;
    u8 pad14[0x4];
    s32 cnt;
} S0030cae0;

/*rgp*/
/*rgp*/

s32 NavMgrFindGraphById_30cae0(S0030cae0 *a, s32 key)
{
    s32 found;
    s32 lo;
    s32 half;
    s32 mid;
    s32 r;

    if (a->list == NULL) {
        found = -1;
    } else {
        half = a->cnt;
        found = -1;
        lo = 0;
        while (half > 0) {
            half >>= 1;
            mid = lo + half;
            if (mid < a->n) {
                r = IntCompare_42ca30(key, NavGraphGetIdThunk_310e90(a->list[mid]));
                if (r == 0) {
                    found = mid;
                    break;
                }
                if (r > 0) lo += half;
            }
        }
    }
    if (found < 0) return 0;
    return a->list[found];
}
