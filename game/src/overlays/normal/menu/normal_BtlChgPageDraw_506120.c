/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageDraw_506120 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506120 -- fetch-then-use guard, twin of 0x00506160. */
/*rgp*/
/*rgp*/

s32 normal_BtlChgPageDraw_506120(void *rgp_a0)
{
    void *w = normal_UiPageGetLayout_289b60((void *)rgp_a0);
    if (w == 0) {
        return 0;
    }
    UiDrawWidgets_291910(w);
    return 1;
}
