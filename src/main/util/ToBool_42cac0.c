#include "types.h"

/* Is the argument non-zero?  The bare sltu is the u8 bool. */

u8 ToBool_42cac0(s32 x)
{
    u8 set;

    set = x != 0;
    return set;
}
