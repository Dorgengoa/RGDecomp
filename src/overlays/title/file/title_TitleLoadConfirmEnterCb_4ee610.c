#include "types.h"

/* title.bin overlay, 0x004EE610 -- clear a gp-relative word, call a sibling
 * overlay function, return 1.  The store rides in the call's delay slot.
 */

extern s32 D_0048420C;
extern void title_TitleSetNoAnalogPause_4f13b0(s32 v);

s32 title_TitleLoadConfirmEnterCb_4ee610(void)
{
    D_0048420C = 0;
    title_TitleSetNoAnalogPause_4f13b0(1);
    return 1;
}
