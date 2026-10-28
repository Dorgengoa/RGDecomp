/* rgp:protos */
#define RGP_SELF_MapIdListRemove_1e5910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same family documented as parked in build/s0910/agent5_FINDINGS.md:
   length-exact draft, bad=6 register swap (diff/slot) that decl-order
   reordering did not fix there either. Reusing that draft shape as-is. */
/*rgp*/
/*rgp*/

void MapIdListRemove_1e5910(u8 *arr, int rgp_a1)
{
    s32 end;
    s32 i;
    u8 *e;
    s32 newCount;

    end = MapIdListFind_1e5a80((void *)arr, (int)rgp_a1);
    if (end == 0) {
        return;
    }
    i = (end - (s32)arr) / 8 + 1;
    while (i < *(s32 *)(arr + 0xA0)) {
        e = arr + i * 8;
        i++;
        *(s16 *)(e - 8) = *(s16 *)(e + 0);
        *(s16 *)(e - 6) = *(s16 *)(e + 2);
        *(s32 *)(e - 4) = *(s32 *)(e + 4);
    }
    newCount = *(s32 *)(arr + 0xA0) - 1;
    *(s32 *)(arr + 0xA0) = newCount;
    if (newCount >= 0) {
        MapIdListEntryInit_1e5fa0(arr + newCount * 8);
    }
}
