/* rgp:protos */
#define RGP_SELF_ListBinSearchByKey_4079d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct ElFUN_004079d0 { u8 k; u8 pad[1]; };
struct PFUN_004079d0 { u8 pad000[0x1]; u8 n; u8 padn[2]; struct ElFUN_004079d0 *arr; };

struct ElFUN_004079d0 *ListBinSearchByKey_4079d0(struct PFUN_004079d0 *p, s32 target)
{
    s32 lo;
    s32 hi;
    s32 mid;
    struct ElFUN_004079d0 *e;

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
