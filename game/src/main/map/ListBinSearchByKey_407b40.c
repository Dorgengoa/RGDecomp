/* rgp:protos */
#define RGP_SELF_ListBinSearchByKey_407b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct ElFUN_00407b40 { u8 k; u8 pad[7]; };
struct PFUN_00407b40 { u8 pad000[0x2]; u8 n; u8 padn[5]; struct ElFUN_00407b40 *arr; };

struct ElFUN_00407b40 *ListBinSearchByKey_407b40(struct PFUN_00407b40 *p, s32 target)
{
    s32 lo;
    s32 hi;
    s32 mid;
    struct ElFUN_00407b40 *e;

    lo = 0;
    hi = p->n - 1;
    while (hi >= lo) {
        mid = lo + (hi - lo + 1) / 2;
        e = &p->arr[mid];
        if (e->k == target) {
            return e;
        }
        if (e->k < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return 0;
}
