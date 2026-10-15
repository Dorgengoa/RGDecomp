#include "types.h"
/* normal 0x005219E0 -- twin of normal_FUN_005235D0; the same (-0x1A, 6) offset
 * pair handed to a different placement helper. */

extern s32 normal_HelpMenuListCursorBob_521a10(void *a, void *b, s32 x, s32 y);

s32 normal_HelpMenuListCursorBobCb_5219e0(void *a, void *b)
{
    normal_HelpMenuListCursorBob_521a10(a, b, -0x1A, 6);
    return 1;
}
