#include "types.h"

/* Two vtable stores: the derived one, then the INLINED base destructor which
   is still guarded by its own `if (self)`.  Then the signed-16-bit release. */

extern u8 D_00471B10[];
extern u8 D_00471A70[];
extern void OperatorDelete_100840(void *p);

void *SpatialMgrDtor_313e70(void *self, s16 n)
{
    if (self == 0) {
        goto done;
    }
    *(u8 **)self = D_00471B10;
    if (self != 0) {
        *(u8 **)self = D_00471A70;
    }
    if (n > 0) {
        OperatorDelete_100840(self);
    }
done:
    return self;
}
