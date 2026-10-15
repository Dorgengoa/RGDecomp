#include "types.h"

s32 StrSum4_1d3600(s8 *arg0)
{
    union { s32 w; u8 b[4]; } h;
    s32 i;

    i = 0;
    h.w = 0;
    while (*arg0 != 0) {
        h.b[i % 4] += *arg0;
        i++;
        arg0++;
    }
    return h.w;
}
