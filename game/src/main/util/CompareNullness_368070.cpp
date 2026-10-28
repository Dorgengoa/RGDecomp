#include "types.h"

extern "C" s32 CompareNullness_368070(void *self, s32 a, s32 b)
{
    s32 r;
    bool t;

    if (a == 0) {
        r = -(b != 0);
        goto end;
    }
    t = !b;
    r = t;
end:
    return r;
}
