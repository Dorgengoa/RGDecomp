/* rgp:protos */
#define RGP_SELF_title_TitleLoadConfirmEnterCb_4ee610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EE610 -- clear a gp-relative word, call a sibling
 * overlay function, return 1.  The store rides in the call's delay slot.
 */

extern s32 D_0048420C;
/*rgp*/

s32 title_TitleLoadConfirmEnterCb_4ee610(void)
{
    D_0048420C = 0;
    title_TitleSetNoAnalogPause_4f13b0(1);
    return 1;
}
