/* rgp:protos */
#define RGP_SELF_NavGraphGetXform_310e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 NavGraphGetXform_310e40(s32 a4, s32 a5)
{
    return (MtxCopy_1cbde0(a5, a4), (s32)0);
}
