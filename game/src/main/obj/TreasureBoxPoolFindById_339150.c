/* rgp:protos */
#define RGP_SELF_TreasureBoxPoolFindById_339150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 TreasureBoxPoolFindById_339150(s32 *arr, s32 key)
{
    s32 cur;
    s32 count;

    cur = *arr;
    if (cur == 0) {
        return 0;
    }
    count = 0;
    while (count < 0x20) {
        if (key == TreasureBoxGetRecId_33b160(cur)) {
            return cur;
        }
        count++;
        cur += 0x80;
    }
    return 0;
}
