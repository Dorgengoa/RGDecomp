/* rgp:protos */
#define RGP_SELF_GetSceneWorkHeap_2025f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BB890.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BB890[];

void *GetSceneWorkHeap_2025f0(void)
{
    return D_004BB890;
}
