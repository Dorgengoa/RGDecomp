/* rgp:protos */
#define RGP_SELF_MinimapSlotDtor_3225c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MW C++ destructor, delete flag, empty body. */

/*rgp*/

void *MinimapSlotDtor_3225c0(void *o, s16 flag)
{
    if (o != 0) {
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
