/* rgp:protos */
#define RGP_SELF_UskStackSetName_42e3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 UskStackSetName_42e3b0(s32 a4, s32 a5)
{
    return StrCopyBounded_42cad0(a4, a5, 0x20);
}
