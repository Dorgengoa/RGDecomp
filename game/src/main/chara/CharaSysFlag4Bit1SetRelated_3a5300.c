/* rgp:protos */
#define RGP_SELF_CharaSysFlag4Bit1SetRelated_3a5300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 CharaSysFlag4Bit1SetRelated_3a5300(s32 a4)
{
    return (CharaSysSetFlag4Bit1Maybe_3a5320(a4), (s32)0);
}
