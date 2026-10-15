#include "types.h"
/* normal 0x005235D0 -- twin of normal_FUN_005219E0. */

extern s32 normal_InsectEntryRankCursorBob_523600(void *a, void *b, s32 x, s32 y);

s32 normal_InsectEntryRankCursorBobCb_5235d0(void *a, void *b)
{
    normal_InsectEntryRankCursorBob_523600(a, b, -0x1A, 6);
    return 1;
}
