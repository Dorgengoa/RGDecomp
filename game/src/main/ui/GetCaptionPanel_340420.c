/* rgp:protos */
#define RGP_SELF_GetCaptionPanel_340420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004E88B0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004E88B0[];

void *GetCaptionPanel_340420(void)
{
    return D_004E88B0;
}
