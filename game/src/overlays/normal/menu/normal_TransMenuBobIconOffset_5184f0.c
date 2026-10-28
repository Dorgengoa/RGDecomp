/* rgp:protos */
#define RGP_SELF_normal_TransMenuBobIconOffset_5184f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005184F0 -- `(s32)(4.0f + 4.0f * func_128FD0(...))`.  The product
 * is written INLINE so the madd.s contraction survives (naming it would kill
 * it -- the mirror of [[normal-named-product-local]]). */

/*rgp*/
/*rgp*/

s32 normal_TransMenuBobIconOffset_5184f0(void)
{
    return (s32)(4.0f + 4.0f * Sinf_128fd0(normal_TransMenuBobTimerGet_518550()));
}
