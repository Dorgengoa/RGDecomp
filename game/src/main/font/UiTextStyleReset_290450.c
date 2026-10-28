/* rgp:protos */
#define RGP_SELF_UiTextStyleReset_290450 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004DB150[];

/*rgp*/

s32 UiTextStyleReset_290450(void)
{
    return (TextStyleInitPreset_26c540(D_004DB150, 0), (s32)0);
}
