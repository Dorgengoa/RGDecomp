#include "types.h"

/* Vtable-only destructor: one pointer store, then the release gated on a
   SIGNED 16-BIT flag.  D_00471A70 is %hi/%lo => incomplete array. */

extern u8 D_00471A70[];
extern void OperatorDelete_100840(void *p);

void *SpatialMgrBaseDtor_313e20(void *self, s16 n)
{
    if (self == 0) {
        goto done;
    }
    *(u8 **)self = D_00471A70;
    if (n > 0) {
        OperatorDelete_100840(self);
    }
done:
    return self;
}
