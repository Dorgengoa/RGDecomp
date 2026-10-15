#include "types.h"

/* Deleting destructor, TWO inlined base bodies (cf. NavGraphNodePoolDtor_30d660 which has
   three).  Release gated on a SIGNED 16-BIT argument; the null guard reaches
   the shared tail return by `goto`. */

typedef struct Obj0030d7d0 {
    s32 m00;
    s8  m04;
    u8  pad05[3];
    s16 m08;
    s16 m0A;
    s32 m0C;
} Obj0030d7d0;

extern void OperatorDelete_100840(void *p);

Obj0030d7d0 *NavGraphStrPoolDtor_30d7d0(Obj0030d7d0 *self, s16 n)
{
    if (self == 0) {
        goto done;
    }
    self->m00 = 0;
    self->m04 = 0;
    self->m08 = 0;
    self->m0A = 0;
    self->m0C = 0;
    if (self != 0) {
        self->m00 = 0;
        self->m04 = 0;
    }
    if (n > 0) {
        OperatorDelete_100840(self);
    }
done:
    return self;
}
