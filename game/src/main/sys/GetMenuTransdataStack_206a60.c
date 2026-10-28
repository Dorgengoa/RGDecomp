/* rgp:protos */
#define RGP_SELF_GetMenuTransdataStack_206a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BBF80.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BBF80[];

void *GetMenuTransdataStack_206a60(void)
{
    return D_004BBF80;
}
