/* rgp:protos */
#define RGP_SELF_GetMenuGoTitleStack_206a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BBF20.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BBF20[];

void *GetMenuGoTitleStack_206a70(void)
{
    return D_004BBF20;
}
