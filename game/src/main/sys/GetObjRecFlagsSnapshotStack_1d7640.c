/* rgp:protos */
#define RGP_SELF_GetObjRecFlagsSnapshotStack_1d7640 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004B3370.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B3370[];

void *GetObjRecFlagsSnapshotStack_1d7640(void)
{
    return D_004B3370;
}
