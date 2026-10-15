#include "types.h"

/* Pass 29 -- the ONE-WORD-SHORT bucket, CHAIN template.
   Retail is a bnel CHAIN.  A `||` chain of the same terms is NOT it -- mwcc
   turns that into a shift/mask set test.  Separate `if (x == K) return 1;`
   statements with the LAST term returned as a comparison reproduce it. */

s32 UnitIsKindOf_3bf2c0(void *p, s32 x)
{
    if (x == 2000) {
        return 1;
    }
    if (x == 1) {
        return 1;
    }
    return x == 0;
}
