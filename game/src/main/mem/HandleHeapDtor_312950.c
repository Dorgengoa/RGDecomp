/* rgp:protos */
#define RGP_SELF_HandleHeapDtor_312950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Deleting destructor: release the owned pointer at +0, then release self when
   the SIGNED 16-BIT flag is positive.  Null guard reaches the tail by goto. */

/*rgp*/

void *HandleHeapDtor_312950(void *self, s16 n)
{
    if (self == 0) {
        goto done;
    }
    OperatorDelete_100840(*(void **)self);
    if (n > 0) {
        OperatorDelete_100840(self);
    }
done:
    return self;
}
