/* rgp:protos */
#define RGP_SELF_LoaderGetData_1cd490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct R1CD490 { u8 pad000[0x90]; void *f90; s32 f94; };

/*rgp*/

void *LoaderGetData_1cd490(void *p, s32 a, s32 *out)
{
    struct R1CD490 *r;

    if (out != 0) {
        *out = 0;
    }
    r = ((struct R1CD490 *)LoaderQueueFindUnitById_1cdc70(p, a, (u8 *)p + 0x30, 0));
    if (r != 0) goto ok;
    return 0;
ok:
    if (out != 0) {
        *out = r->f94;
    }
    return r->f90;
}
