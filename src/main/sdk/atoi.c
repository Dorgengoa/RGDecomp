#include "types.h"

/* newlib lib/libc/stdlib/atoi. The dsll32/dsra32 pair in the reference is the
   s32 truncation of strtol's long return, not anything of atoi's own. */

extern long Strtol_136360(const char *s, char **end, s32 base);   /* strtol */

s32 atoi(const char *s)
{
    return (s32)Strtol_136360(s, 0, 10);
}
