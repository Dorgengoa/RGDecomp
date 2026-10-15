#include "types.h"

extern "C" u8 TargetRefResolve_2e5ed0(void *);

extern "C" bool EvObjResolveTarget_2f9a60(u8 *p)
{
    return (TargetRefResolve_2e5ed0(p + 0xA0) & 1) != 0;
}
