/* rgp:protos */
#define RGP_SELF_title_TitleMovieStop_4f0480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F0480 -- four calls, three of them with a
 * gp-relative argument loaded in the call's own delay slot, then a store and
 * a constant return. */

extern void *D_00484290;
extern void *D_0048429C;
extern s32 D_00480430;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleMovieStop_4f0480(void)
{
    MoviePlayerShutdown_1d56c0(D_00484290);
    MovieDrawFrame_1d5870(D_00484290);
    MovieFrameQueueSendNext_1d4b20();
    MemStackReset_14d830(D_0048429C);
    D_00480430 = -1;
    return 1;
}
