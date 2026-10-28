/* rgp:protos */
#define RGP_SELF_GetNpcDataHeap_1fdd70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004B6920.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B6920[];

void *GetNpcDataHeap_1fdd70(void)
{
    return D_004B6920;
}
