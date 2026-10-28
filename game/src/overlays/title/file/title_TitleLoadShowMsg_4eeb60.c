/* rgp:protos */
#define RGP_SELF_title_TitleLoadShowMsg_4eeb60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EEB60 -- tail call into main with a gp-relative argument */

extern s32 D_00484174;
/*rgp*/

void title_TitleLoadShowMsg_4eeb60(s32 a)
{
    SaveMsgBoxShowSlotInfo_376b60(a, D_00484174, 0, (long long)(-1));
}
