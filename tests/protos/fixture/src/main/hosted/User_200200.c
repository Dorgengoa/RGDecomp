#include "types.h"
extern s32 Guest_200100(s32);

s32 User_200200(s32 x)
{
    return Guest_200100(x) + 1;
}
