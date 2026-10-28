/* rgp:protos */
#define RGP_SELF_NavGraphEdgeIdxPoolDtor_30d760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Deleting destructor, TWO inlined base bodies (cf. NavGraphNodePoolDtor_30d660 which has
   three).  Release gated on a SIGNED 16-BIT argument; the null guard reaches
   the shared tail return by `goto`. */

typedef struct Obj0030d760 {
    s32 m00;
    s8  m04;
    u8  pad05[3];
    s16 m08;
    s16 m0A;
    s32 m0C;
} Obj0030d760;

/*rgp*/

Obj0030d760 *NavGraphEdgeIdxPoolDtor_30d760(Obj0030d760 *self, s16 n)
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
