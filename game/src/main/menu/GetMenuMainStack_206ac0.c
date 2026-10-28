/* rgp:protos */
#define RGP_SELF_GetMenuMainStack_206ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BBBC0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BBBC0[];

void *GetMenuMainStack_206ac0(void)
{
    return D_004BBBC0;
}
