/* rgp:protos */
#define RGP_SELF_atoi 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* newlib lib/libc/stdlib/atoi. The dsll32/dsra32 pair in the reference is the
   s32 truncation of strtol's long return, not anything of atoi's own. */

/*rgp*/   /* strtol */

s32 atoi(const char *s)
{
    return (s32)Strtol_136360(s, 0, 10);
}
