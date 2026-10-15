#include "types.h"

/* Deleting-destructor shape (sibling of the known-positive StrVectorDtor_1a21a0):
   three INLINED base-class destructor bodies, each still guarded by its own
   `if (self)` (retail really does re-test $16 twice), then the release gated
   on a SIGNED 16-BIT argument.  The null guard reaches the shared tail return
   by `goto`, not by its own `return self`. */

typedef struct Obj0030d660 {
    s32 m00;
    s8  m04;
    u8  pad05[3];
    s16 m08;
    s16 m0A;
    s32 m0C;
} Obj0030d660;

extern void OperatorDelete_100840(void *p);

Obj0030d660 *NavGraphNodePoolDtor_30d660(Obj0030d660 *self, s16 n)
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
        self->m08 = 0;
        self->m0A = 0;
        self->m0C = 0;
        if (self != 0) {
            self->m00 = 0;
            self->m04 = 0;
        }
    }
    if (n > 0) {
        OperatorDelete_100840(self);
    }
done:
    return self;
}
