/* rgp:protos */
#define RGP_SELF_TextEntryNameGridTextStyleDrawCb_432a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00484104;
/*rgp*/

s32 TextEntryNameGridTextStyleDrawCb_432a70(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    if (D_00484104 != 0) TextEntryNameGridTextStyle_433380(D_00484104, a, b, c, d, e);
    return 1;
}
