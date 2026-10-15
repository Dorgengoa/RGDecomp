#include "types.h"

/* MW C++ destructor, delete flag, empty body. */

extern void OperatorDelete_100840(void *);

void *EffectEntryDtor_2e3360(void *o, s16 flag)
{
    if (o != 0) {
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
