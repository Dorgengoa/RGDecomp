/* rgp:protos */
#define RGP_SELF_CharaTableDataCollectPrmtFlags_226710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Two OR-accumulating loops over the 0x14-stride tables at +0x1C (count
   s16 at +0x30) and +0x20 (count s16 at +0x32).  The accumulator is
   initialised BEFORE the first list pointer is read. */

/*rgp*/
/*rgp*/
/*rgp*/

long long CharaTableDataCollectPrmtFlags_226710(s32 arg0, f32 f)
{
    long long r;
    s32 p;
    s32 i;

    r = 0;
    p = *(s32 *)(arg0 + 0x1C);
    if (p != 0) {
        for (i = 0; i < *(s16 *)(arg0 + 0x30); i++, p += 0x14) {
            if (ActionEntryTimeMatch_228310(p, f) != 0) {
                r |= ActTimePrmtGetFlags_227660(p + 0xC);
            }
        }
    }
    p = *(s32 *)(arg0 + 0x20);
    if (p != 0) {
        for (i = 0; i < *(s16 *)(arg0 + 0x32); i++, p += 0x14) {
            if (ActionEntryTimeMatch_228310(p, f) != 0) {
                r |= ActDataCnctGetCmndMask_2274c0(p + 0xC);
            }
        }
    }
    return r;
}
