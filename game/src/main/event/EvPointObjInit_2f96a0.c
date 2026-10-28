/* rgp:protos */
#define RGP_SELF_EvPointObjInit_2f96a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN EvPointObjInit_2f96a0 -- EvObjSwitchInit_2f89f0 with EvObjResetThunk_2f9eb0 in place of
   EvObjSwitchReset_2f8b20. */

/*rgp*/
/*rgp*/

s32 EvPointObjInit_2f96a0(s32 a, s32 b, void *c, void *d, s32 e, s32 f)
{
    EvObjResetThunk_2f9eb0(a);
    if (c == 0 || d == 0) {
        return 0;
    }
    return EvObjInit_2f9cf0(a, b, c, d, e, f);
}
