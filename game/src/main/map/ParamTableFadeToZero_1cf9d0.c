/* rgp:protos */
#define RGP_SELF_ParamTableFadeToZero_1cf9d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 ParamTableFadeToZero_1cf9d0(s32 a4, s32 a5, s32 a6)
{
    return ((s32)ParamTableFadeTo_1cfa00(a4, a5, a6, 0.0f));
}
