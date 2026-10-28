/* rgp:protos */
#define RGP_SELF_CharaKind1002IsKindOf_3b0810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- the ONE-WORD-SHORT bucket, CHAIN template.
   Retail is a bnel CHAIN.  A `||` chain of the same terms is NOT it -- mwcc
   turns that into a shift/mask set test.  Separate `if (x == K) return 1;`
   statements with the LAST term returned as a comparison reproduce it. */

s32 CharaKind1002IsKindOf_3b0810(void *p, s32 x)
{
    if (x == 1002) {
        return 1;
    }
    if (x == 1000) {
        return 1;
    }
    if (x == 1) {
        return 1;
    }
    return x == 0;
}
