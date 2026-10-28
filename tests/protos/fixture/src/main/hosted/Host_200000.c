#include "types.h"

static s32 Guest_200100(s32 x)
{
    return x * 3;
}

s32 Host_200000(s32 x)
{
    return Guest_200100(x);
}
