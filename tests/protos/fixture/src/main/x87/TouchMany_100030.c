#include "types.h"
/* a caller that declares a float-returning callee void */
extern void VecLen_1cb3c0(void *v);

void TouchMany_100030(void *v)
{
    s32 i;

    for (i = 0; i < 24; i++) {
        VecLen_1cb3c0(v);
    }
}
