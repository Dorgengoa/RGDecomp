#include "types.h"

/* Two OR-accumulating loops over the 0x14-stride tables at +0x1C (count
   s16 at +0x30) and +0x20 (count s16 at +0x32).  The accumulator is
   initialised BEFORE the first list pointer is read. */

extern s32 ActionEntryTimePending_2283b0(s32, f32);
extern s32 ActTimePrmtGetFlags_227660(s32);
extern s32 ActDataCnctGetCmndMask_2274c0(s32);

s32 CharaTableDataCollectPendingPrmtFlags_2267f0(s32 arg0, f32 f)
{
    s32 r;
    s32 p;
    s32 i;

    r = 0;
    p = *(s32 *)(arg0 + 0x1C);
    if (p != 0) {
        for (i = 0; i < *(s16 *)(arg0 + 0x30); i++, p += 0x14) {
            if (ActionEntryTimePending_2283b0(p, f) != 0) {
                r |= ActTimePrmtGetFlags_227660(p + 0xC);
            }
        }
    }
    p = *(s32 *)(arg0 + 0x20);
    if (p != 0) {
        for (i = 0; i < *(s16 *)(arg0 + 0x32); i++, p += 0x14) {
            if (ActionEntryTimePending_2283b0(p, f) != 0) {
                r |= ActDataCnctGetCmndMask_2274c0(p + 0xC);
            }
        }
    }
    return r;
}
