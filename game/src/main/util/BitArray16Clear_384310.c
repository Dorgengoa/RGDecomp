/* rgp:protos */
#define RGP_SELF_BitArray16Clear_384310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 memset(s32, s32, s32);

s32 BitArray16Clear_384310(s32 a4)
{
    return ((s32)memset(a4, 0, 2));
}
