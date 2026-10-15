#include "types.h"

/* Is the SECOND argument non-zero?  The value is read from $a1, so a first parameter exists and is unused -- the pass-through-argument shape, named in the prototype. */

u8 HandleEntryLinkNop_3f1380(void *unused, s32 x)
{
    u8 set;

    set = x != 0;
    return set;
}
