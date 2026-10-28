/* rgp:protos */
#define RGP_SELF_LoadHandleRelease_1dd160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of AreaBoxInit_1e01f0 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

void LoadHandleRelease_1dd160(s32 p0)
{
    LoaderReleaseHandle_1ccb70((void *)p0);
    LoadHandleResetThunk_1ccc10(p0);
}
