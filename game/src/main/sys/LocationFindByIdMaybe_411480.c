/* rgp:protos */
#define RGP_SELF_LocationFindByIdMaybe_411480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 LocationFindByIdMaybe_411480(void *a, void *b, s32 c)
{
    s32 r;
    if ((s16)c < 0) return 0;
    r = ((s32)GroupRangeLookup_411590((void *)a, (void *)b, (short)c));
    if (r != 0) return r;
    r = ((s32)GroupRangeLookup_411500(a, b, c));
    if (r != 0) {
        return r;
    }
    return 0;
}
