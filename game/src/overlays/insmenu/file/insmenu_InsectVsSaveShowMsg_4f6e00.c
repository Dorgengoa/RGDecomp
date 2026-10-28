/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSaveShowMsg_4f6e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F6E00 -- tail call; $4 passes straight through and the other
 * two parameters shift up one slot for insmenu_D_004FA180 in $5. */
extern u8 insmenu_D_004FA180[];
/*rgp*/

void insmenu_InsectVsSaveShowMsg_4f6e00(s32 a, s32 b, s32 c)
{
    SaveMsgBoxShowSlotInfo_376b60(a, insmenu_D_004FA180, b, (long long)(c));
}
