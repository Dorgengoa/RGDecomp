/* rgp:protos */
#define RGP_SELF_MapAreaHeapAllocAndClone_1d8e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
struct Obj0 { s32 m00; };
s32 MapAreaHeapAllocAndClone_1d8e00(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;
    r0 = MapAreaHeapAlloc_1d8ef0(p0);
    if (r0 != 2) {
        return r0;
    }
    r1 = MapAreaCloneAndIndex_1dab10(p0, p0->m00);
    if (r1 != 0) {
        return 2;
    }
    return -1;
}
