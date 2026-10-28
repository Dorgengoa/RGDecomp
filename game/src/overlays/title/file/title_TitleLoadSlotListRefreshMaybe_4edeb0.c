/* rgp:protos */
#define RGP_SELF_title_TitleLoadSlotListRefreshMaybe_4edeb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EDEB0 -- tail call into main: func_3783C0(o, 1) */

/*rgp*/

void title_TitleLoadSlotListRefreshMaybe_4edeb0(s16 a)
{
    SaveSlotListRefreshDetailMaybe_3783c0(a, 1);
}
