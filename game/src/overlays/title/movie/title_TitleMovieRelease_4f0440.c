/* rgp:protos */
#define RGP_SELF_title_TitleMovieRelease_4f0440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F0440 -- three calls, the first feeding the second,
 * then two gp-relative stores. */

extern s32 D_004842A0;
extern s32 D_00484290;
extern s32 D_00480430;
/*rgp*/
/*rgp*/
/*rgp*/

void title_TitleMovieRelease_4f0440(void)
{
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), D_004842A0);
    CdDiskWatchSetEnabled_17fe80(1);
    D_00484290 = 0;
    D_00480430 = -1;
}
