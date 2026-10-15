#include "types.h"

/* MW C++ destructor, delete flag, empty body. */

extern void OperatorDelete_100840(void *);

void *MinimapSlotDtor_3225c0(void *o, s16 flag)
{
    if (o != 0) {
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
