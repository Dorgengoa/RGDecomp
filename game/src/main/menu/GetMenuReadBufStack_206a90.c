/* rgp:protos */
#define RGP_SELF_GetMenuReadBufStack_206a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BBE60.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BBE60[];

void *GetMenuReadBufStack_206a90(void)
{
    return D_004BBE60;
}
