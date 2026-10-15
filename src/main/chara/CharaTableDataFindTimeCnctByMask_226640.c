#include "types.h"

/* Mask search over the 0x14-stride table at +0x20 (count s16 at +0x32),
   then a float hit test.  `beqz $2` branches PAST the return, so the
   fall-through is the if body. */

extern s32 ActDataCnctGetCmndMask_2274c0(s32);
extern s32 ActTimeCnctGetCnct_227540(s32);
extern s32 ActionEntryTimeMatch_228310(s32, f32);

s32 CharaTableDataFindTimeCnctByMask_226640(s32 arg0, s32 arg1, f32 f)
{
    s32 p;
    s32 i;

    p = *(s32 *)(arg0 + 0x20);
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < *(s16 *)(arg0 + 0x32); i++, p += 0x14) {
        if ((arg1 & ActDataCnctGetCmndMask_2274c0(p + 0xC)) == ActDataCnctGetCmndMask_2274c0(p + 0xC)) {
            if (ActionEntryTimeMatch_228310(p, f) != 0) {
                return ActTimeCnctGetCnct_227540(p + 0xC);
            }
        }
    }
    return 0;
}
