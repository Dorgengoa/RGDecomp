#include "types.h"

/* Constructor: sub-object at +0x90, its vtable stored between two of the
   member ctors (the sw sits in the jal's delay slot, so it PRECEDES the
   NavGraphNodePoolCtor_30d950 call in source order).  D_00471A50 is %hi/%lo => incomplete
   array declaration. */

extern u8 D_00471A50[];
extern void HeapBlockRefCtor_30d990(void *p);
extern void NavGraphNodePoolCtor_30d950(void *p);
extern void NavGraphEdgePoolCtor_30d910(void *p);
extern void NavGraphEdgeIdxPoolCtor_30d8e0(void *p);
extern void NavGraphStrPoolCtor_30d8b0(void *p);

void *NavGraphCtor_30d840(void *self)
{
    u8 *p;

    p = (u8 *)self + 0x90;
    HeapBlockRefCtor_30d990(p);
    *(u8 **)(p + 0xC) = D_00471A50;
    NavGraphNodePoolCtor_30d950(p + 0x10);
    NavGraphEdgePoolCtor_30d910(p + 0x20);
    NavGraphEdgeIdxPoolCtor_30d8e0(p + 0x30);
    NavGraphStrPoolCtor_30d8b0(p + 0x40);
    return self;
}
