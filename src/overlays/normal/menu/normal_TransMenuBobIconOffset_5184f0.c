#include "types.h"
/* normal 0x005184F0 -- `(s32)(4.0f + 4.0f * func_128FD0(...))`.  The product
 * is written INLINE so the madd.s contraction survives (naming it would kill
 * it -- the mirror of [[normal-named-product-local]]). */

extern f32 normal_TransMenuBobTimerGet_518550(void);
extern f32 func_128FD0(f32 x);

s32 normal_TransMenuBobIconOffset_5184f0(void)
{
    return (s32)(4.0f + 4.0f * func_128FD0(normal_TransMenuBobTimerGet_518550()));
}
