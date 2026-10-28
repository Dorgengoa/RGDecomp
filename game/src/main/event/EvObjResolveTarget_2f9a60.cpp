/* rgp:protos */
#line 1
#include "types.h"

extern "C" u8 TargetRefResolve_2e5ed0(void *, int);

extern "C" u32 EvObjResolveTarget_2f9a60(u8 *p, int rgp_a1)
{
    return (bool)((TargetRefResolve_2e5ed0(p + 0xA0, (int)rgp_a1) & 1) != 0);
}
