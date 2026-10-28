/* rgp:protos */
#define RGP_SELF_CharaSetLastSafePosMaybe_213a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 CharaSetLastSafePosMaybe_213a80(void *p4, s32 a5)
{
    return (VecCopy_1cbe30((u8 *)p4 + 0x460, a5), (s32)0);
}
