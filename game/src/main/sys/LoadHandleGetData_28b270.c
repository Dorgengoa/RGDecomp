/* rgp:protos */
#define RGP_SELF_LoadHandleGetData_28b270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 LoadHandleGetData_28b270(s32 *a, s32 *out)
{
    void *h;

    if (out != 0) {
        *out = 0;
    }
    if (((unsigned char)LoadHandleIsReady_28b200(a)) == 0) {
        return 0;
    }
    h = GetLoaderMgr_1f59d0();
    if (h == 0) {
        return 0;
    }
    return ((s32)LoaderGetData_1cd490(h, *a, out));
}
