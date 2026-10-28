#include "types.h"
/* rule ret-narrow-view: a C++ POINTER view of a u8 definition (EventSysUpdate_26ac10's
   `void *ObjRecHasFlags6_1c3eb0(..)` tested == 0) */
extern "C" void *Low8Sum_4020c0(s32 *p);

extern "C" s32 NarrowPtrUser_402100(s32 *p)
{
    return Low8Sum_4020c0(p) == 0 ? 0 : 1;
}
