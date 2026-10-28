/* rgp:protos */
#define RGP_SELF_GetLoadingResReady_1f69c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_004819D8. */

extern u8 D_004819D8;

u8 GetLoadingResReady_1f69c0(void)
{
    return D_004819D8;
}
