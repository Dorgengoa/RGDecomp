/* rgp:protos */
#define RGP_SELF_EvMapObjNodeCopy_3673f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvMapObjNodeCopy_3673f0(u8 *o, void *a, void *b)
{
    s32 r;

    EvMapObjNodeReset_3674b0(o);
    if (a == 0 || b == 0) {
        return 0;
    }
    r = ((s32)MemStackStrDup_14cff0(EvMapObjNodeGetName_3673e0(a), b));
    *(s32 *)(o + 0x140) = r;
    return r != 0;
}
