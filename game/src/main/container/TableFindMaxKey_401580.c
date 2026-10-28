/* rgp:protos */
#define RGP_SELF_TableFindMaxKey_401580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s16 *TableFindMaxKey_401580(s32 arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    u8 sp28[8];
    s16 *temp_2;
    s16 *best;
    s32 v;

    v = arg0;
    best = NULL;
    if (arg0 != 0) {
        v += 4;
    }
    IterInit_370170(sp28, v, (int)rgp_a2, (int)rgp_a3);
    while ((temp_2 = ((s16 *)IterNext_370040(sp28))) != 0) {
        if (best == NULL ||
            (s64)((s64)*best << 0x36) >> 0x36 < (s64)((s64)*temp_2 << 0x36) >> 0x36) {
            best = temp_2;
        }
    }
    return best;
}
